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

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation;

#include "config.h"
#include "arguments.h"
#include "interface.h"
#include "ode_solver.h"
#include "fourier.h"

#include <cmath>
#include <sstream>
#include <vector>

using std::string;
using std::vector;

template <class vector>
struct species
{
	string name;
	int    particles;
	double charge2mass;
	double plasma_frequency;
	int    mode;
	vector r1;
	vector v0;
	vector v1;
	vector theta_r;
	vector theta_v;
};

template <class vector>
struct particle
{
	double            q; // Charge.
	double            m; // Mass.
	vector            r; // Position vector.
	vector            v; // Velocity vector.
	vector            E; // Electric field value at the particle.
	species<vector> * group;
};

class Simulation:
	public Interface,
	public ODESolver
{
	public:
		Simulation(arguments Args);
		virtual ~Simulation();
		
		virtual int Start(vector< particle<double> > Particles);
		virtual int Restart();
		virtual int Unpause();
		virtual int Simulate();
	protected:
		double                     LastTime;
		double                     TimeIncrement;
		double                     FinalTime;
		vector< species<double> >  Species;
		vector< particle<double> > InitialParticles;
		vector< particle<double> > Particles;
		double                     InitialEnergy;
		double                     InitialMomentum;
		double                     ESEnergy;
		int                        ID;
		int                        Weighting;
		double                     GridStart;
		double                     GridFinish;
		double                     GridLength;
		double                     GridIncrement;
		int                        GridCells;
		vector<double>             ChargeDensity;
		vector<complex>            ChargeDensityK;
		vector<double>             ChargeDensityTest;
		vector<double>             ESPotential;
		vector<double>             EField;
		Fourier                    Transformer;
		string                     Output;
		
		virtual void   DefaultSetup();
		virtual int    Setup(vector< particle<double> > NewParticles);
		virtual int    Reset();
		virtual void   Derivatives(double* dy, double* y, int N);
		virtual double Energy();
		virtual double Momentum();
		virtual double ElectricField(double r);
		virtual int    BuildChargeDensity();
		virtual int    BuildElectricField();
		virtual int    InterpolateElectricField();
	private:
		void SimulationCommon(arguments Args);
};

const double pi           = M_PI;
//const double epsilon_zero = 8.85418782e-12;
const double epsilon_zero = 1;
const double e  = 1.60217646e-19; // Unit charge.
const double me = 9.10938188e-31; // Electron mass.
const double mn = 1.67262158e-27; // Nucleon mass.


#endif
