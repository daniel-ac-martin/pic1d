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

#include "ode_solver.h"

//FIXME: Remove!!!
//#include <iostream>

//
// Constructors & Destructors
//
ODESolver::ODESolver()
{
	yold = NULL;
	Nold = 0;
}

ODESolver::~ODESolver()
{
	if(yold) delete[] yold;
}

//
// Meat
//
void ODESolver::Euler(double* yout, double* yin, int N, double h)
{
	int     i      = 0;
	double* in     = NULL;
	double  dyn[N];
	
	if(yin == yout)
	{
		in = new double[N];
		Copy(in, yin, N);
	}
	else
	{
		in = yin;
	}
	
	this->Derivatives(dyn, in, N);
	i = 0;
	while(i < N)
	{
		yout[i] = in[i] + h * dyn[i];
		//std::cout << i << ": " << in[i] << " + " << dyn[i] << " * " << h << " = " << yout[i] << std::endl;
		i++;
	}
	
//	this->Store(in, N);
	if(yin == yout)
	{
		delete[] in;
	}
}

void ODESolver::EulerEven(double* yout, double* yin, int N, double h)
{
	int     i      = 0;
	double* in     = NULL;
	double  dyn[N];
	
	if(yin == yout)
	{
		in = new double[N];
		Copy(in, yin, N);
	}
	else
	{
		in = yin;
	}
	
	this->Derivatives(dyn, in, N);
	i = 0;
	while(i < N - 1)
	{
		yout[i] = in[i] + h * dyn[i];;
		//std::cout << i << ": " << in[i] << " + " << dyn[i] << " * " << h << " = " << yout[i] << std::endl;
		i += 2;
	}
	
//	this->Store(in, N);
	if(yin == yout)
	{
		delete[] in;
	}
}

void ODESolver::EulerOdd(double* yout, double* yin, int N, double h)
{
	int     i      = 0;
	double* in     = NULL;
	double  dyn[N];
	
	if(yin == yout)
	{
		in = new double[N];
		Copy(in, yin, N);
	}
	else
	{
		in = yin;
	}
	
	this->Derivatives(dyn, in, N);
	i = 1;
	while(i < N)
	{
		yout[i] = in[i] + h * dyn[i];;
		//std::cout << i << ": " << in[i] << " + " << dyn[i] << " * " << h << " = " << yout[i] << std::endl;
		i += 2;
	}
	
//	this->Store(in, N);
	if(yin == yout)
	{
		delete[] in;
	}
}

void ODESolver::RungeKutta4(double* yout, double* yin, int N, double h)
{
	int i = 0;
	double dyn[N];
	double k1[N];
	double k2[N];
	double k3[N];
	double k4[N];
	double yinn[N];
	
	// Find k1.
	this->Derivatives(dyn, yin, N);
	i = 0;
	while(i < N)
	{
		k1[i] = h * dyn[i];
		yinn[i] = yin[i] + 0.5 * k1[i];
		i++;
	}
	// Find k2.
	this->Derivatives(dyn, yinn, N);
	i = 0;
	while(i < N)
	{
		k2[i] = h * dyn[i];
		yinn[i] = yin[i] + 0.5 * k2[i];
		i++;
	}
	// Find k3.
	this->Derivatives(dyn, yinn, N);
	i = 0;
	while(i < N)
	{
		k3[i] = h * dyn[i];
		yinn[i] = yin[i] + k3[i];
		i++;
	}
	// Find k4 and next iteration.
	this->Derivatives(dyn, yinn, N);
	i = 0;
	while(i < N)
	{
		k4[i] = h * dyn[i];
		yout[i] = yin[i] + (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6;
		//std::cout << i << ": " << yin[i] << " -> " << yout[i] << std::endl;
		i++;
	}
	
//	this->Store(yin, N);
}

void ODESolver::RungeKutta4Even(double* yout, double* yin, int N, double h)
{
	int i = 0;
	double dyn[N];
	double k1[N];
	double k2[N];
	double k3[N];
	double k4[N];
	double yinn[N];
	
	// Find k1.
	this->Derivatives(dyn, yin, N);
	i = 0;
	while(i < N - 1)
	{
		k1[i] = h * dyn[i];
		yinn[i] = yin[i] + 0.5 * k1[i];
		i += 2;
	}
	// Find k2.
	this->Derivatives(dyn, yinn, N);
	i = 0;
	while(i < N - 1)
	{
		k2[i] = h * dyn[i];
		yinn[i] = yin[i] + 0.5 * k2[i];
		i += 2;
	}
	// Find k3.
	this->Derivatives(dyn, yinn, N);
	i = 0;
	while(i < N - 1)
	{
		k3[i] = h * dyn[i];
		yinn[i] = yin[i] + k3[i];
		i += 2;
	}
	// Find k4 and next iteration.
	this->Derivatives(dyn, yinn, N);
	i = 0;
	while(i < N - 1)
	{
		k4[i] = h * dyn[i];
		yout[i] = yin[i] + (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6;
		//std::cout << i << ": " << yin[i] << " -> " << yout[i] << std::endl;
		i += 2;
	}
	
//	this->Store(yin, N);
}

void ODESolver::RungeKutta4Odd(double* yout, double* yin, int N, double h)
{
	int i = 0;
	double dyn[N];
	double k1[N];
	double k2[N];
	double k3[N];
	double k4[N];
	double yinn[N];
	
	// Find k1.
	this->Derivatives(dyn, yin, N);
	i = 1;
	while(i < N)
	{
		k1[i] = h * dyn[i];
		yinn[i] = yin[i] + 0.5 * k1[i];
		i += 2;
	}
	// Find k2.
	this->Derivatives(dyn, yinn, N);
	i = 1;
	while(i < N)
	{
		k2[i] = h * dyn[i];
		yinn[i] = yin[i] + 0.5 * k2[i];
		i += 2;
	}
	// Find k3.
	this->Derivatives(dyn, yinn, N);
	i = 1;
	while(i < N)
	{
		k3[i] = h * dyn[i];
		yinn[i] = yin[i] + k3[i];
		i += 2;
	}
	// Find k4 and next iteration.
	this->Derivatives(dyn, yinn, N);
	i = 1;
	while(i < N)
	{
		k4[i] = h * dyn[i];
		yout[i] = yin[i] + (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6;
		//std::cout << i << ": " << yin[i] << " -> " << yout[i] << std::endl;
		i += 2;
	}
	
//	this->Store(yin, N);
}

void ODESolver::Verlet(double* yout, double* yin, int N, double h)
{
	int     i      = 0;
	double* in     = NULL;
	double  dy2n[N];
	
	if(yin == yout)
	{
		in = new double[N];
		Copy(in, yin, N);
	}
	else
	{
		in = yin;
	}
	
	if(!yold) Store(in, N);
	
	this->Derivatives(dy2n, yin, N);
	i = 0;
	while(i < N)
	{
		yout[i] = 2 * yin[i] - yold[i] + dy2n[i] * h * h;
		//std::cout << i << ": 2 * " << yin[i] << " - " << yold[i] << " + " << dy2n[i] << " * " << h << "^2 = " << yout[i] << std::endl;
		i++;
	}
	
	this->Store(in, N);
	if(yin == yout)
	{
		delete[] in;
	}
}

void ODESolver::VerletEven(double* yout, double* yin, int N, double h)
{
	int     i      = 0;
	double* in     = NULL;
	double  dyn[N];
	
	if(yin == yout)
	{
		in = new double[N];
		Copy(in, yin, N);
	}
	else
	{
		in = yin;
	}
	
	if(!yold) Store(in, N);
	
	this->Derivatives(dyn, in, N);
	i = 0;
	while(i < N - 1)
	{
		yout[i] = 2 * in[i] - yold[i] + dyn[i + 1] * h * h;
		//std::cout << i << ": 2 * " << yin[i] << " - " << yold[i] << " + " << dyn[i + 1] << " * " << h << "^2 = " << yout[i] << std::endl;
		i += 2;
	}
	
	this->Store(in, N);
	if(yin == yout)
	{
		delete[] in;
	}
}

void ODESolver::VerletOdd(double* yout, double* yin, int N, double h)
{
	int     i      = 0;
	double* in     = NULL;
	double  dyn[N];
	
	if(yin == yout)
	{
		in = new double[N];
		Copy(in, yin, N);
	}
	else
	{
		in = yin;
	}
	
	if(!yold) Store(in, N);
	
	this->Derivatives(dyn, yin, N);
	i = 1;
	while(i < N)
	{
		yout[i] = 2 * yin[i] - yold[i] + dyn[i + 1] * h * h;
		//std::cout << i << ": 2 * " << yin[i] << " - " << yold[i] << " + " << dyn[i + 1] << " * " << h << "^2 = " << yout[i] << std::endl;
		i += 2;
	}
	
	this->Store(in, N);
	if(yin == yout)
	{
		delete[] in;
	}
}

void ODESolver::LeapFrogPrep(double* yout, double* yin, int N, double h)
{
	// We need to regress odd elements back from H to H - h/2.
	this->Copy(yout, yin, N);
	this->EulerOdd(yout, yin, N, -h / 2);
}

void ODESolver::EulerLeapFrog(double* yout, double* yin, int N, double h)
{
	this->Copy(yout, yin, N);
	// Stage 1. Propagate from H - h/2 to H + h/2. 
	this->EulerOdd(yout, yin, N, h);
	
	// Stage 2. Propagate from H to H + 1. 
	this->EulerEven(yout, yout, N, h);
}

void ODESolver::RungeKutta4LeapFrog(double* yout, double* yin, int N, double h)
{
	this->Copy(yout, yin, N);
	// Stage 1. Propagate from H - h/2 to H + h/2. 
	this->RungeKutta4Odd(yout, yin, N, h);
	
	// Stage 2. Propagate from H to H + 1. 
	this->RungeKutta4Even(yout, yout, N, h);
}

void ODESolver::VerletLeapFrog(double* yout, double* yin, int N, double h)
{
	this->Copy(yout, yin, N);
	// Stage 1. Propagate from H - h/2 to H + h/2. 
	this->EulerOdd(yout, yin, N, h); // It seems standard to call Euler here, this isn't a mistake!
	
	// Stage 2. Propagate from H to H + 1. FIXME: Dodgy doubly use of yout. - UPDATE: I don't think this is dodgy anymore!
	this->VerletEven(yout, yout, N, h);
}

void ODESolver::Store(double* yin, int N)
{
	// We need to store the values (yin) as our old values (yold).
	int i = 0;
	
	// First we make sure the array is the correct size.
	if( (yold) && (N != Nold) )
	{
		delete[] yold;
		yold = new double[N];
	}
	else if(!yold)
	{
		yold = new double[N];
	}
	
	// Now we can perform the copy.
	i = 0;
	while(i < N)
	{
		yold[i] = yin[i];
		i++;
	}
}

void ODESolver::Copy(double* yout, double* yin, int N)
{
	int i = 0;
	while(i < N)
	{
		yout[i] = yin[i];
		i++;
	}
}
