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

#ifndef FILE_FOURIER_H
#define FILE_FOURIER_H

class complex;

#include "config.h"

class Fourier
{
	public:
		virtual ~Fourier()
		{
		}
		
		virtual int Normal(complex* Result, complex* Data, int N, int direction);
		virtual int Normal(complex* Result, double* Data, int N, int direction);
		virtual int Normal(double* Result, complex* Data, int N, int direction);
		virtual int Normal(double* Result, double* Data, int N, int direction);
		virtual int Fast(complex* Result, complex* Data, int N, int direction);
		virtual int Fast(complex* Result, double* Data, int N, int direction);
		virtual int Fast(double* Result, complex* Data, int N, int direction);
		virtual int Fast(double* Result, double* Data, int N, int direction);
		virtual int DodgyCorrection(complex* Data, int N);
		virtual int DodgyCorrection(double* Data, int N);
	protected:
	private:
};

#endif
