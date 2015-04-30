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

#ifndef ODE_SOLVER_H
#define ODE_SOLVER_H

class ODESolver;

#include "config.h"

class ODESolver
{
	public:
		ODESolver();
		virtual ~ODESolver();
		
		virtual void Euler(double* yout, double* yin, int N, double h);
		virtual void EulerLeapFrog(double* yout, double* yin, int N, double h);
		virtual void RungeKutta4(double* yout, double* yin, int N, double h);
		virtual void RungeKutta4LeapFrog(double* yout, double* yin, int N, double h); // Nonsensical & Broken.
		virtual void Verlet(double* yout, double* yin, int N, double h);              // Broken?
		virtual void VerletEven(double* yout, double* yin, int N, double h);          // Broken?
		virtual void VerletLeapFrog(double* yout, double* yin, int N, double h);      // Broken?
		virtual void LeapFrogPrep(double* yout, double* yin, int N, double h);
	protected:
		double* yold;
		int     Nold;
		
		virtual void Derivatives(double* dy, double* y, int N) = 0;                   // This holds the true physics.
		virtual void Store(double* yin, int N);
		virtual void Copy(double* yout, double* yin, int N);
		virtual void EulerEven(double* yout, double* yin, int N, double h);
		virtual void EulerOdd(double* yout, double* yin, int N, double h);
		virtual void RungeKutta4Even(double* yout, double* yin, int N, double h);     // Broken.
		virtual void RungeKutta4Odd(double* yout, double* yin, int N, double h);      // Broken.
		virtual void VerletOdd(double* yout, double* yin, int N, double h);           // Broken?
	private:
};

#endif
