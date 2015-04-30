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

#include "fourier.h"
#include "complex.h"
#include <cmath>

const double pi = M_PI;

/*
 * The normal (slow) fourier transform algorithm.
 * 
 * I wrote this, it's logic is easy to follow, but it
 * really is slow!
 */

int Fourier::Normal(complex* Result, complex* Data, int N, int direction)
{
	int       result  = -1;
	int       a       =  0;
	int       b;
	imaginary subterm = (i * -2 * pi * direction) / (double)N;
	imaginary term;
	
	if( (direction == 1) || (direction == -1) )
	{
		while(a < N)
		{
			b         = 0;
			Result[a] = 0;
			term      = a * subterm;
			
			while(b < N)
			{
				Result[a] += Data[b] * exp(b * term);
				b++;
			}
			
			Result[a] /= sqrt((double)N);
			a++;
		}
		result = 0;
	}
	else
	{
		std::cerr << "Error: Unrecognised `direction' argument int call to Fourier::Normal().\n";
		result = 1;
	}
	
	return result;
}

int Fourier::Normal(complex* Result, double* Data, int N, int direction)
{
	/*
	int     result    = -1;
	int     n         =  0;
	complex Buffer[N];
	
	while(n < N)
	{
		Buffer[n] = Data[n];
		n++;
	}
	
	result = this->Normal(Result, Buffer, N, direction);
	
	return result;
	//*/
	///*
	int       result  = -1;
	int       a       =  0;
	int       b;
	imaginary subterm = (i * -2 * pi * direction) / (double)N;
	imaginary term;
	
	if( (direction == 1) || (direction == -1) )
	{
		while(a < N)
		{
			b         = 0;
			Result[a] = 0;
			term      = a * subterm;
			
			while(b < N)
			{
				Result[a] += Data[b] * exp(b * term);
				b++;
			}
			
			Result[a] /= sqrt((double)N);
			a++;
		}
		result = 0;
	}
	else
	{
		std::cerr << "Error: Unrecognised `direction' argument int call to Fourier::Normal().\n";
		result = 1;
	}
	
	return result;
	//*/
}

/*
 * The fast fourier transform algorithm.
 * 
 * I must confess that I don't really understand a lot of
 * this and much credit goes to Paul Bourke and Peter
 * Cusack.
 */
int Fourier::Fast(complex* Result, complex* Data, int N, int direction)
{
	int result = 0;
	int      i = 0;
	int      j = 0;
	int      k = 0;
	int      l = 0;
	int      m = 0;
	int      n = 0;
	double   d_power;
	int      power;
	complex  Buffer;
	complex  Voo;
	complex  Doo;
	
	if( (direction == 1) || (direction == -1) )
	{
		//
		// N = 2^power
		//
		// We need to know the value of `power'.
		//
		d_power = log(double (N))/log(double (2));
		power   = lround(d_power);
		
		if( (d_power - power < 1e-12) && (d_power - power > -1e-12) )
		{
			//
			// Prepare array.
			//
			while(i < N)
			{
				Result[i] = Data[i];
				i++;
			}
			
			//if(direction == -1) this->DodgyCorrection(Result, N);
			
			i = 0;
			j = 0;
			k = 0;
			
			//
			// Bit reversal.
			//
			while(i < N - 1)
			{
				if(i < j)
				{
					Buffer    = Result[i];
					Result[i] = Result[j];
					Result[j] = Buffer;
				}
				
				k = N / 2;
				
				while(k <= j)
				{
					j = j - k;
					k = k / 2;
				}
				
				j = j + k;
				i++;
			}
			
			i = 0;
			j = 0;
			k = 0;
			Buffer = 0;
			
			//
			// Compute.
			// 
			// Perform VooDoo.
			//
			Voo = -1;
			l = 0;
			n = 1;
			
			while(l < power)
			{
				k = 0;
				m = n;
				n = n * 2;
				Doo = 1;
				
				while(k < m)
				{
					i = k;
					
					while(i < N)
					{
						j = i + m;
						Buffer    = Doo * Result[j];
						Result[j] = Result[i] - Buffer;
						Result[i] = Result[i] + Buffer;
						i = i + n;
					}
					
					Doo *= Voo;
					k++;
				}
				
				//Voo =   squareroot((1 + Voo.Real) / 2)
				//      - i * direction * squareroot((1 - Voo.Real) / 2);
				Voo.Imag = sqrt((1 - Voo.Real) / 2);
				
				if(direction == 1)
				{
					Voo.Imag = Voo.Imag * -1;
				}
				
				Voo.Real = sqrt((1 + Voo.Real) / 2);
				l++;
			}
			
			i = 0;
			while(i < N)
			{
				Result[i] /= sqrt(N);
				i++;
			}
			
			//if(direction == 1) this->DodgyCorrection(Result, N);
		}
		else
		{
			std::cerr << "Warning: The total number of points in the call to Fourier::Fast() is not a power of 2. - Performing normal transform instead.\n";
			result = this->Normal(Result, Data, N, direction);
		}
	}
	else
	{
		std::cerr << "Error: Unrecognised `direction' int argument in call to Fourier::Fast().\n";
		result = 1;
	}

	return result;
}

int Fourier::Fast(complex* Result, double* Data, int N, int direction)
{
	/*
	int result = -1;
	int n      =  0;
	complex Buffer[N];
	
	while(n < N)
	{
		Buffer[n] = Data[n];
		n++;
	}
	
	result = this->Fast(Result, Buffer, N, direction);
	
	return result;
	//*/
	///*
	int result = 0;
	int      i = 0;
	int      j = 0;
	int      k = 0;
	int      l = 0;
	int      m = 0;
	int      n = 0;
	double   d_power;
	int      power;
	complex  Buffer;
	complex  Voo;
	complex  Doo;
	
	if( (direction == 1) || (direction == -1) )
	{
		//
		// N = 2^power
		//
		// We need to know the value of `power'.
		//
		d_power = log(double (N))/log(double (2));
		power   = lround(d_power);
		
		if( (d_power - power < 1e-12) && (d_power - power > -1e-12) )
		{
			//
			// Prepare array.
			//
			while(i < N)
			{
				Result[i] = Data[i];
				i++;
			}
			
			//if(direction == -1) this->DodgyCorrection(Result, N);
			
			i = 0;
			j = 0;
			k = 0;
			
			//
			// Bit reversal.
			//
			while(i < N - 1)
			{
				if(i < j)
				{
					Buffer    = Result[i];
					Result[i] = Result[j];
					Result[j] = Buffer;
				}
				
				k = N / 2;
				
				while(k <= j)
				{
					j = j - k;
					k = k / 2;
				}
				
				j = j + k;
				i++;
			}
			
			i = 0;
			j = 0;
			k = 0;
			Buffer = 0;
			
			//
			// Compute.
			// 
			// Perform VooDoo.
			//
			Voo = -1;
			l = 0;
			n = 1;
			
			while(l < power)
			{
				k = 0;
				m = n;
				n = n * 2;
				Doo = 1;
				
				while(k < m)
				{
					i = k;
					
					while(i < N)
					{
						j = i + m;
						Buffer    = Doo * Result[j];
						Result[j] = Result[i] - Buffer;
						Result[i] = Result[i] + Buffer;
						i = i + n;
					}
					
					Doo *= Voo;
					k++;
				}
				
				//Voo =   squareroot((1 + Voo.Real) / 2)
				//      - i * direction * squareroot((1 - Voo.Real) / 2);
				Voo.Imag = sqrt((1 - Voo.Real) / 2);
				
				if(direction == 1)
				{
					Voo.Imag = Voo.Imag * -1;
				}
				
				Voo.Real = sqrt((1 + Voo.Real) / 2);
				l++;
			}
			
			i = 0;
			while(i < N)
			{
				Result[i] /= sqrt(N);
				i++;
			}
			
			//if(direction == 1) this->DodgyCorrection(Result, N);
		}
		else
		{
			std::cerr << "Warning: The total number of points in the call to Fourier::Fast() is not a power of 2. - Performing normal transform instead.\n";
			result = this->Normal(Result, Data, N, direction);
		}
	}
	else
	{
		std::cerr << "Error: Unrecognised `direction' int argument in call to Fourier::Fast().\n";
		result = 1;
	}

	return result;
	//*/
}

int Fourier::Normal(double* Result, complex* Data, int N, int direction)
{
	int     result    = 0;
	int     n         = 0;
	complex Buffer[N];
	
	this->Normal(Buffer, Data, N, -1);
	while(n < N)
	{
		Result[n] = Buffer[n].Real;
		n++;
	}
	
	return result;
}

int Fourier::Normal(double* Result, double* Data, int N, int direction)
{
	int     result    = 0;
	int     n         = 0;
	complex Buffer[N];
	
	this->Normal(Buffer, Data, N, -1);
	while(n < N)
	{
		Result[n] = Buffer[n].Real;
		n++;
	}
	
	return result;
}

int Fourier::Fast(double* Result, complex* Data, int N, int direction)
{
	int     result    = 0;
	int     n         = 0;
	complex Buffer[N];
	
	this->Fast(Buffer, Data, N, -1);
	while(n < N)
	{
		Result[n] = Buffer[n].Real;
		n++;
	}
	
	return result;
}

int Fourier::Fast(double* Result, double* Data, int N, int direction)
{
	int     result    = 0;
	int     n         = 0;
	complex Buffer[N];
	
	this->Fast(Buffer, Data, N, -1);
	while(n < N)
	{
		Result[n] = Buffer[n].Real;
		n++;
	}
	
	return result;
}

int Fourier::DodgyCorrection(complex* Data, int N)
{
	int     result = 0;
	int     a      = 0;
	int     b      = N / 2;
	int     c      = 0;
	complex Buffer = 0;
	
	while(a < b)
	{
		c = b + a;
		Buffer  = Data[a];
		Data[a] = Data[c];
		Data[c] = Buffer;
		a++;
	}
	
	return result;
}

int Fourier::DodgyCorrection(double* Data, int N)
{
	int    result = 0;
	int    a      = 0;
	int    b      = N / 2;
	int    c      = 0;
	double Buffer = 0;
	
	while(a < b)
	{
		c = b + a;
		Buffer  = Data[a];
		Data[a] = Data[c];
		Data[c] = Buffer;
		a++;
	}
	
	return result;
}

