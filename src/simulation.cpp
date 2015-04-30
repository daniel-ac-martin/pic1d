/*
 * Copyright (C) 2007 Daniel A.C. Martin.
 * This file is part of PIC1D.
 * 
 * PIC1D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * PIC1D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with PIC1D.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "simulation.h"
#include <time.h>
#include "complex.h"

void Simulation::SimulationCommon(arguments Args)
{
	int n = 0;
	//
	// Get initial parameters.
	//
	Output        = (Args.output_set) ? Args.output : "plasma_sim";
	GridLength    = (Args.length_set) ? Args.length : 2 * pi;
	GridFinish    = 0.5 * GridLength;
	GridStart     = -GridFinish;
	GridCells     = (Args.points_set) ? Args.points : 256;
	GridIncrement = GridLength / (double)GridCells;
	TimeIncrement = (Args.time_step_set) ? Args.time_step : 0;
	LastTime      = (TimeIncrement == 0) ? clock() : 0;
	FinalTime     = ( (Args.total_time_steps_set) ? Args.total_time_steps : 1024) * TimeIncrement;
	Weighting     = (Args.weighting_set) ? Args.weighting : 1;
	InitialEnergy = 0;
	n = 0;
	Array< species<double> > Species(Args.species.Elements);
	while(n < Species.Elements)
	{
		Species[n].name             = (Args.species[n].name_set)        ? Args.species[n].name        : "";
		Species[n].particles        = (Args.species[n].particles_set)   ? Args.species[n].particles   : 8 * GridCells;
		Species[n].charge2mass      = (Args.species[n].charge2mass_set) ? Args.species[n].charge2mass : 1;
		Species[n].plasma_frequency = (Args.species[n].plasma_freq_set) ? Args.species[n].plasma_freq : 1;
		Species[n].mode             = (Args.species[n].mode_set)        ? Args.species[n].mode        : 1;
		Species[n].r1               = (Args.species[n].x1_set)          ? Args.species[n].x1          : 0;
		Species[n].v0               = (Args.species[n].v0_set)          ? Args.species[n].v0          : 0;
		Species[n].v1               = (Args.species[n].v1_set)          ? Args.species[n].v1          : 0;
		Species[n].theta_r          = (Args.species[n].theta_x_set)     ? Args.species[n].theta_x     : 0;
		Species[n].theta_v          = (Args.species[n].theta_v_set)     ? Args.species[n].theta_v     : 0;
		n++;
	}
	
	if(Args.verbose)
	{
		// Output setup.
		std::cout << "Output files:      " << Output << "*\n"
		          << "Length:            " << GridLength << "\n"
		          << "Grid points:       " << GridCells << "\n"
		          << "Time step:         " << TimeIncrement << "\n"
		          << "Final time:        " << FinalTime << "\n"
		          << "Weighting:         " << Weighting << "\n"
		          << "Number of species: " << Species.Elements << "\n"
		          << std::endl;
		n = 0;
		while(n < Species.Elements)
		{
			std::cout << "Species " << n << ":\n"
			          << "\tName:                 " << Species[n].name << "\n"
			          << "\tParticles:            " << Species[n].particles << "\n"
			          << "\tCharge to mass ratio: " << Species[n].charge2mass << "\n"
			          << "\tPlasma frequency:     " << Species[n].plasma_frequency << "\n"
			          << "\tPerturbed mode:       " << Species[n].mode << "\n"
			          << "\tPosition amplitude:   " << Species[n].r1 << "\n"
			          << "\tDrift velocity:       " << Species[n].v0 << "\n"
			          << "\tVelocity amplitude:   " << Species[n].v1 << "\n"
			          << "\tPosition phase:       " << Species[n].theta_r << "\n"
			          << "\tVelocity phase:       " << Species[n].theta_v << "\n"
			          << std::endl;
			n++;
		}
	}
	
	Array<double>  ChargeDensity(GridCells);
	Array<complex> ChargeDensityK(GridCells);
	Array<double>  ChargeDensityTest(GridCells);
	Array<double>  ESPotential(GridCells);
	Array<double>  EField(GridCells);
	n = 0;
	while(n < GridCells)
	{
		ChargeDensity[n] = 0;
		ChargeDensityK[n] = 0;
		ChargeDensityTest[n] = 0;
		ESPotential[n] = 0;
		EField[n] = 0;
		n++;
	}
	this->Species           = Species;
	this->ChargeDensity     = ChargeDensity;
	this->ChargeDensityK    = ChargeDensityK;
	this->ChargeDensityTest = ChargeDensityTest;
	this->ESPotential       = ESPotential;
	this->EField            = EField;
//	playing                 = false;
}

Simulation::Simulation(arguments Args):
	Interface(),
	ODESolver()
{
	SimulationCommon(Args);
	DefaultSetup();
}
	
Simulation::~Simulation()
{
}

void Simulation::DefaultSetup()
{
	int N = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	while(a < Species.Elements)
	{
		N += Species[a].particles;
		a++;
	}
	Array< particle<double> > Particles(N);
	double Spacing;
	double w;
	double q;
	double m;
	int    n;
	double k;
	double r0;
	double r1;
	double v0;
	double v1;
	
	a = 0;
	b = 0;
	c = 0;
	while(a < Species.Elements)
	{
		Spacing = GridLength / ((double)Species[a].particles);
		w = Species[a].plasma_frequency;
		q = w * w * Spacing * epsilon_zero / Species[a].charge2mass;
		m = q / Species[a].charge2mass;
		n = Species[a].mode;
		k = 2 * pi * (double)n / GridLength;
		r1 = Species[a].r1;
		v0 = Species[a].v0;
		v1 = Species[a].v1;
		while(c - b < Species[a].particles)
		{
			r0 = GridStart + (c - 0.5) * Spacing;
			Particles[c].group = &Species[a];
			Particles[c].q = q;
			Particles[c].m = m;
			Particles[c].r = r0 + r1 * cos(k * (r0 - GridStart));
			while(Particles[c].r < GridStart)  Particles[c].r += GridLength;
			while(Particles[c].r > GridFinish) Particles[c].r -= GridLength;
			Particles[c].v = v0 + v1 * cos(k * (r0 - GridStart));
			c++;
		}
		b = c;
		a++;
	}
	/*
	//
	// Default setup.
	//
	int N = 2 * 8 * lround((GridFinish - GridStart) / GridIncrement);
	//int N = 1;
	Array< particle<double> > Particles(N);
	double GridLength = GridFinish - GridStart;
	double Spacing    = GridLength / ((double)N/2.0);
	double n0         = 1 / Spacing;
	double q          = 1;
	double m          = 1;
	int    n          = 1;
	double k          = 2 * pi * (double)n / GridLength;
	
	PlasmaFrequency = sqrt((n0 * q * q) / (epsilon_zero * m));
	//std::cout << "Plasma frequency is: " << PlasmaFrequency << std::endl;
	
	n = 0;
	while(n < N)
	{
		//double r1 = 0.001 * Spacing;
		double r1 = 0.0001;
		Particles[n].r = GridStart + (lround(n/2 - 0.25) - 0.5) * Spacing;
		Particles[n].v = (n % 2 == 0) ? 1 : -1;
		
		Particles[n].q = -q;
		Particles[n].m = m;
		Particles[n].r += ( (n % 2 == 0) ? r1 : -r1) * cos(k * (Particles[n].r - GridStart));
		while(Particles[n].r < GridStart)  Particles[n].r += GridLength;
		while(Particles[n].r > GridFinish) Particles[n].r -= GridLength;
		//int a = (n != 0) ? n - 1 : N - 1;
		//assert( (Particles[n].r > Particles[a].r) || (GridStart + n * Spacing < Particles[a].r) );
		
		assert(GridStart <= Particles[n].r && Particles[n].r < GridFinish);
		
		n++;
	}*/
	
	/*n = 0;
	while(n < N)
	{
		int a = (n != 0) ? n - 1 : N - 1;
		std::cout << (Particles[n].r - Particles[a].r) - Spacing << std::endl;
		n++;
	}*/
	
	Setup(Particles);
}

int Simulation::Setup(Array< particle<double> > NewParticles)
{
	int result = 0;
	
	InitialParticles = NewParticles;
	Particles        = InitialParticles;
	
	result += BuildChargeDensity();
	result += BuildElectricField();
	result += InterpolateElectricField();
	
	//
	// If we are leap frogging then we must regress the velocities back by
	// half a time-step.
	//
	if(TimeIncrement != 0)
	{
		int    N       = 2 * Particles.Elements;
		int    i       = 0;
		int    j       = 0;
		double yin[N];
		double yout[N];
		
		while(i < Particles.Elements)
		{
			j = 2 * i;
			yin[j]     = Particles[i].r;
			yin[j + 1] = Particles[i].v;
			i++;
		}
		
		this->LeapFrogPrep(yout, yin, N, TimeIncrement);
		
		i = 0;
		j = 0;
		while(i < Particles.Elements)
		{
			j = 2 * i;
			Particles[i].r = yout[j];
			Particles[i].v = yout[j + 1];
			Particles[i].E = 0;
			i++;
		}
	}
	
	InitialEnergy = Energy();
	InitialMomentum = Momentum();
	
	return result;
}

int Simulation::Reset()
{
	int result = -1;
	
	result = Setup(InitialParticles);
	
	return result;
}

int Simulation::Start(Array< particle<double> > Particles)
{
	int result = -1;
	
	if(playing)
	{
		//
		// We are still running a simulation, the user must stop the
		// current simulation before beginning a new one.
		//
		result = 1;
	}
	else
	{
		result = Setup(Particles);
		
		if(result == 0)
		{
			playing   = true;
			LastTime = (TimeIncrement == 0) ? clock() : 0;
		}
		else
		{
			result += 1;
		}
	}
	
	return result;
}

int Simulation::Restart()
{
	int result = -1;
	
	if(playing)
	{
		//
		// We are still running a simulation, the user must stop the
		// current simulation before beginning a new one.
		//
		result = 1;
	}
	else
	{
		result = Reset();
		
		if(result == 0)
		{
			playing = true;
			LastTime = (TimeIncrement == 0) ? clock() : 0;
		}
		else
		{
			result += 1;
		}
	}
	
	return result;
}

int Simulation::Unpause()
{
	int result = -1;
	
	if(playing)
	{
		//
		// We're aren't paused.
		//
		result = 1;
	}
	else
	{
		//
		// Unpause.
		//
		playing = true;
		if(TimeIncrement == 0)
		{
			LastTime = clock();
		}
		result  = 0;
	}
	
	return result;
}

int Simulation::Simulate()
{
	int    result    =  0;
	int    reps      =  1; // This is ignored when we have a set time-step.
	int    N         =  2 * Particles.Elements;
	//int    n         =  0;
	int    i         =  0;
	int    j         =  0;
	double ThisTime =  0;
	double dt        =  0;
	double test_dt   =  0;
	double yin[N];
	double yout[N];
	
	if(playing)
	{
		if(TimeIncrement == 0)
		{
			ThisTime = clock();
			test_dt = (ThisTime - LastTime) / (1000000 * reps); // Note the conversion to seconds.
			dt = (test_dt >= 0.0) ? test_dt : 0.0;                // The result of clock() loops so we do this to protect ourselves from the bug (NANs for angles) that result.
		}
		else
		{
			ThisTime = LastTime + TimeIncrement * 1000000;     // Note the conversion to micro-seconds.
			dt = TimeIncrement;
		}
		
		//
		// Perform nessessary maths here. Typically you would alter the
		// positions of objects etc...
		//
		
		//
		// Move particles.
		//
		int n;
		i = 0;
		j = 0;
		while(i < Particles.Elements)
		{
			j = 2 * i;
			yin[j]     = Particles[i].r;
			yin[j + 1] = Particles[i].v;
			i++;
		}
		
		for(n = 0; n < reps; n++)
		{
			if(TimeIncrement == 0)
			{
				// We can't handle a variable step size in the
				// leap-frog scheme, so we use a runge-kutta.
				this->RungeKutta4(yout, yin, N, dt);
			}
			else
			{
				this->EulerLeapFrog(yout, yin, N, dt);
				//this->RungeKutta4(yout, yin, N, dt);
			}
			if(n < reps - 1)
			{
				i = 0;
				while(i < N)
				{
					yin[i] = yout[i];
					i++;
				}
			}
		}
		
		i = 0;
		j = 0;
		double GridLength = GridFinish - GridStart;
		while(i < Particles.Elements)
		{
			j = 2 * i;
			while(yout[j] < GridStart) yout[j] += GridLength;
			while(yout[j] >= GridFinish) yout[j] -= GridLength;
			Particles[i].r = yout[j];
			Particles[i].v = yout[j + 1];
			//assert(!isinf(Particles[i].r));
			//assert(!isinf(Particles[i].v));
			//assert(!isnan(Particles[i].r));
			//assert(!isnan(Particles[i].v));
			i++;
		}
		
		//
		// Build charge distribution.
		//
		result += BuildChargeDensity();
		
		//
		// Calculate electric field.
		//
		result += BuildElectricField();
		
		//
		// Interpolate electric field.
		//
		result += InterpolateElectricField();
		
		//
		// All done.
		//
		LastTime = ThisTime;
		
		//
		// Checks.
		//
		/*
		if( (Energy() - InitialEnergy) / InitialEnergy > 0.1)
		{
			std::cerr << "Warning: Lack of energy conservation. (" << 100 * (Energy() - InitialEnergy) / InitialEnergy << "%)" << std::endl;
		}
		//*/
		/*
		if( (InitialMomentum != 0) && ( (Momentum() - InitialMomentum) / InitialMomentum > 0.1) )
		{
			std::cerr << "Warning: Lack of momentum conservation. (" << 100 * (Momentum() - InitialMomentum) / InitialMomentum << "%)" << std::endl;
		}
		//*/
	}
	
	return result;
}

void Simulation::Derivatives(double* dy, double* y, int N)
{
	particle<double> target;
	double q;
	double m;
	int i = 0;
	//double E = 1e-13;
	//double E = 0.2;
	double E;
	
	while(i < N - 1)
	{
		target = Particles[int (i / 2)];
		q = target.q;
		m = target.m;
		E = target.E;
		
		dy[i]     = y[i + 1];                         // Position <- Velocity
		//dy[i + 1] = -E * y[i]; // Velocity <- Lorentz Acceleration
		dy[i + 1] = (q / m) * (E /*+ v x B*/); // Velocity <- Lorentz Acceleration
		i += 2;
	}
}

double Simulation::Energy()
{
	//
	// We need to find the energy of the system.
	//
	double result  = 0;
	int    i       = 0;
	double v       = 0;
	double r;
	int    N       = 2 * Particles.Elements;
	double yin[N];
	double yout[N];
	
	if(TimeIncrement != 0)
	{
		int i = 0;
		int j = 0;
		
		while(i < Particles.Elements)
		{
			j = 2 * i;
			yin[j]     = Particles[i].r;
			yin[j + 1] = Particles[i].v;
			i++;
		}
		
		this->LeapFrogPrep(yout, yin, N, -TimeIncrement);
	}
	
	while(i < Particles.Elements)
	{
		r = Particles[i].r;
		if(TimeIncrement == 0)
		{
			v = Particles[i].v;
		}
		else
		{
			v = yout[2 * i + 1];
		}
		
		result += Particles[i].m * v * v / 2; // Kinetic Energy = mv^2/2
		i++;
	}
	
	result += ESEnergy; // Potential Energy
	
	return result;
}

double Simulation::Momentum()
{
	//
	// We need to find the net momentum of the system.
	//
	double result  = 0;
	int    i       = 0;
	double v       = 0;
	double r;
	int    N       = 2 * Particles.Elements;
	double yin[N];
	double yout[N];
	
	if(TimeIncrement != 0)
	{
		int i = 0;
		int j = 0;
		
		while(i < Particles.Elements)
		{
			j = 2 * i;
			yin[j]     = Particles[i].r;
			yin[j + 1] = Particles[i].v;
			i++;
		}
		
		this->LeapFrogPrep(yout, yin, N, -TimeIncrement);
	}
	
	while(i < Particles.Elements)
	{
		r = Particles[i].r;
		if(TimeIncrement == 0)
		{
			v = Particles[i].v;
		}
		else
		{
			v = yout[2 * i + 1];
		}
		
		result += Particles[i].m * v;
		i++;
	}
	
	return result;
}

double Simulation::ElectricField(double r)
{
	int a;                          // The grid point to the left.
	int b;                          // The grid point to the right.
	double result;                  // The interpolated electric field at r.
	double dr      = GridIncrement; // The space between grid points.
	double subterm;                 // Just used to speed this function up.
	
	// Shouldn't need this test
	if( (GridStart > r) || (r >= GridFinish) )
	{
		result = 0;
		std::cerr << "BUG: Refusing to extrapolate electric field. (Position out of bounds, we only want to interpolate.)" << std::endl;
		CRASH();
	}
	
	// Find nearest grid point to the left of our position, r.
	switch(Weighting)
	{
		case 0:
			a = lround((r - GridStart) / dr); if(a >= EField.Elements) a -= EField.Elements;
			result = EField[a];
			break;
		case 1:
			a = lround((r - GridStart) / dr);
			if(GridStart + a * dr > r)
			{
				a--;
			}
			b = (a < EField.Elements - 1) ? a + 1 : a + 1 - EField.Elements;
			subterm = (r - GridStart) / dr - a;
			result = (1 - subterm) * EField[a] + subterm * EField[b];
			
			// Sanity checks.
			if( (GridStart + a * dr > r) || (r > GridStart + (a + 1) * dr) )
			{
				std::cerr << "BUG: Electric Field interpolation failed.\n"
				          << "Grid point locations are incorrect.\n"
				          << r << " -> " << GridStart + a * dr << " & " << GridStart + b * dr << std::endl;
				CRASH();
			}
			if( ( (!(EField[a] == EField[b]) && (EField[a] == result)) ) && ( ( (EField[a] < EField[b]) && ( (EField[a] > result) || (result > EField[b]) ) ) || ( (EField[a] > EField[b]) && ( (EField[a] < result) || (result < EField[b]) ) ) ))
			{
				std::cerr << "BUG: Electric Field interpolation failed.\n"
				          << "\n"
				          << result << " -> " << EField[a] << " & " << EField[b] << "\n"
				          << subterm << " = " << a << " + (" << GridStart << " - " << r  << ") / " << dr << "\n"
				          << result << " = " << (1 + subterm) * EField[a] << " - " << subterm * EField[b] << std::endl;
				CRASH();
			}
			break;
		case 2:
			CRASH();
			break;
		default:
			CRASH();
			break;
	}
	
	return result;
}

//
// Builds the ChargeDensity array using the particles data (positions & charges).
//
int Simulation::BuildChargeDensity()
{
	int    result = -1;                     // Return value of function, returns 0 on success.
	int    a;                               // Grid point to the left of the particle.
	int    b;                               // Grid point to the right of the particle.
	int    n      = 0;                      // Space index.
	int    N      = ChargeDensity.Elements; // Number of grid points.
	double dr     = GridIncrement;          // Space between grid points.
	double r;                               // Position of particle.
	double rho;                             // Charge of particle / grid spacing.
	double rhob;                            // Charge density contribution from particle to point a.
	double rhoa;                            // Charge density contribution from particle to point b.
	double TotalCharge = 0;
	double NeutralisingBackground = 0;
	
	// Get Total Charge
	n = 0;
	while(n < Particles.Elements)
	{
		TotalCharge += Particles[n++].q;
	}
	NeutralisingBackground = -TotalCharge / (GridFinish - GridStart);
	
	// Wipe charge density clean.
	n = 0;
	while(n < N)
	{
		ChargeDensity[n++] = NeutralisingBackground;
	}
	
	// Iterate over all particles.
	n = 0;
	while(n < Particles.Elements)
	{
		r = Particles[n].r;
		rho = Particles[n].q / dr;
		assert(GridStart <= r && r < GridFinish);
		
		switch(Weighting)
		{
			case 0:
				a = lround((r - GridStart) / dr);
				if( (r > GridStart + (a + 1) * dr) || (r < GridStart + (a - 1) * dr) )
				{
					std::cerr << "BUG: Charge density weighting failed.\n"
					          << "Grid point locations are incorrect.\n"
					          << r << " -> " << GridStart + a * dr << std::endl;
					CRASH();
				}
				if(a >= N) a-= N;
				ChargeDensity[a] += rho;
				break;
			case 1:
				// Find grid points.
				a = (int) lround((r - GridStart) / dr);
				if(GridStart + a * dr > r)
				{
					a--;
				}
				b = (a < N - 1) ? a + 1 : a + 1 - N; // Next point along, (minor complication at the end of the grid).
				//std::cout << r << " -> " << GridStart + a * dr << " & " << GridStart + b * dr << std::endl;
				
				// Calculate charge contributions.
				//rhob = rho * (r - (GridStart + a * dr) ) / dr; // 1st Order. - Can be derived from Langdon & Birdsall p20.
				rhob = rho * ((r - GridStart) / dr - a); // 1st Order. - Can be derived from Langdon & Birdsall p20.
				rhoa = rho - rhob;
				
				// Sanity checks.
				if( (GridStart + a * dr > r) || (r > GridStart + (a + 1) * dr) )
				{
					std::cerr << "BUG: Charge density weighting failed.\n"
					          << "Grid point locations are incorrect.\n"
					          << r << " -> " << GridStart + a * dr << " & " << GridStart + b * dr << std::endl;
					CRASH();
				}
				if( ( (rho > 0.0) && ( (rhoa > rho) || (rhob > rho) ) ) || (rho < 0.0) && ( (rhoa < rho) || (rhob < rho) ) )
				{
					std::cerr << "BUG: Charge density weighting failed.\n"
					          << "\n"
					          << rho << " -> " << rhoa << " & " << rhob << std::endl;
					CRASH();
				}
				//assert_fatal(!(isnan(rhoa) || isnan(rhob))); // FIXME: How can this be done on windows?!
				
				// Assign density to grid points.
				ChargeDensity[a] += rhoa;
				ChargeDensity[b] += rhob;
				break;
			case 2:
				CRASH();
				break;
			default:
				CRASH();
				break;
			}
		n++;
	}
	/*n = 0;
	while(n < N)
	{
		//ChargeDensity[n] = 3e-1 * sin((n * GridIncrement * 2 * 6 * pi) / (GridFinish - GridStart)) * (Particles.Elements * e) / (GridFinish - GridStart);
		ChargeDensity[n] = sin((n * GridIncrement * 2 * 6 * pi) / (GridFinish - GridStart));
		//ChargeDensity[n] = epsilon_zero;
		n++;
	}*/
	
	result = 0;
	
	return result;
}

int Simulation::BuildElectricField()
{
	int            result    = -1;
	int            n;                                                    // Standard space index
	int            m;                                                    // Fourier space index
	int            N         = ChargeDensity.Elements;                   // Number of grid points
	double         dr        = GridIncrement;
	double         k;                                                    // Wavenumber
	double         k_subterm = (2 * pi) / (N * dr);
	//double         kappa;
	double         K;
	double         m_correct = -N / 2;
	Array<complex> ESPotentialK(N);
	//Array<complex> EFieldK(N);
	Array<complex> Buffer(N);
	
	ESEnergy = 0;
	Transformer.Fast(ChargeDensityK.c_array(), ChargeDensity.c_array(), N, 1);
	//Transformer.Normal(ChargeDensityK.c_array(), ChargeDensity.c_array(), N, 1);
	Transformer.DodgyCorrection(ChargeDensityK.c_array(), N);
	m = 0;
	while(m < N)
	{
		k = (m + m_correct) * k_subterm;
		//kappa = sin(k * dr) / dr;
		K = 2 * sin(k * dr / 2) / dr;
		ESPotentialK[m] = (K != 0.0) ? ChargeDensityK[m] / (K * K * epsilon_zero) : 0;
		//EFieldK[m] = ESPotentialK[m] * -i * kappa;
		ESEnergy += (0.5 * ChargeDensityK[m] * ESPotentialK[m].Conjugate()).Real;
		m++;
	}
	//ESEnergy /= 82;
	Transformer.DodgyCorrection(ChargeDensityK.c_array(), N);
	Transformer.Fast(ChargeDensityTest.c_array(), ChargeDensityK.c_array(), N, -1);
	//Transformer.Normal(ChargeDensityTest.c_array(), ChargeDensityK.c_array(), N, -1);
	Transformer.DodgyCorrection(ESPotentialK.c_array(), N);
	Transformer.Fast(ESPotential.c_array(), ESPotentialK.c_array(), N, -1);
	//Transformer.Normal(ESPotential.c_array(), ESPotentialK.c_array(), N, -1);
	//Transformer.DodgyCorrection(EFieldK.c_array(), N);
	//Transformer.Fast(EField.c_array(), EFieldK.c_array(), N, -1);
	//Transformer.Normal(EField.c_array(), EFieldK.c_array(), N, -1);
	n = 0;
	while(n < N)
	{
		int a = (n == 0) ? N - 1 : n - 1;
		int b = (n == N - 1) ? 0 : n + 1;
		EField[n] = (ESPotential[a] - ESPotential[b]) / (2 * dr);
		n++;
	}
	
	result = 0;
	
	return result;
}

int Simulation::InterpolateElectricField()
{
	int result = 1;
	int i      = 0;
	
	while(i < Particles.Elements)
	{
		Particles[i].E = ElectricField(Particles[i].r);
		i++;
	}
	
	result = 0;
	
	return result;
}
