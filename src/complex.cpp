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

#include "complex.h"
#include <cmath>

complex complex::Conjugate() const
{
	complex Result;
	
	Result.Real = this->Real;
	Result.Imag = -this->Imag;
	
	return Result;
}

double complex::Magnitude() const
{
	double result;
	
	result = sqrt(this->Real * this->Real + this->Imag * this->Imag);
	
	return result;
}

complex& complex::operator=(const complex& Number)
{
	if(&Number != this)
	{
		this->Real = Number.Real;
		this->Imag = Number.Imag;
	}
	
	return *this;
}

complex& complex::operator=(imaginary Number)
{
	this->Real = 0;
	this->Imag = Number.Value;
	
	return *this;
}

complex& complex::operator=(double Number)
{
	this->Real = Number;
	this->Imag = 0;
	
	return *this;
}

complex& complex::operator=(int Number)
{
	this->Real = Number;
	this->Imag = 0;
	
	return *this;
}

complex complex::operator+(complex Number) const
{
	complex Result;
	Result.Real = this->Real + Number.Real;
	Result.Imag = this->Imag + Number.Imag;
	return Result;
}

complex complex::operator+(imaginary Number) const
{
	complex Result;
	Result.Real = this->Real;
	Result.Imag = this->Imag + Number.Value;
	return Result;
}

complex complex::operator+(double Number) const
{
	complex Result;
	Result.Real = this->Real + Number;
	Result.Imag = this->Imag;
	return Result;
}

complex complex::operator+(int Number) const
{
	complex Result;
	Result.Real = this->Real + Number;
	Result.Imag = this->Imag;
	return Result;
}

complex complex::operator-(complex Number) const
{
	complex Result;
	Result.Real = this->Real - Number.Real;
	Result.Imag = this->Imag - Number.Imag;
	return Result;
}

complex complex::operator-(imaginary Number) const
{
	complex Result;
	Result.Real = this->Real;
	Result.Imag = this->Imag - Number.Value;
	return Result;
}

complex complex::operator-(double Number) const
{
	complex Result;
	Result.Real = this->Real - Number;
	Result.Imag = this->Imag;
	return Result;
}

complex complex::operator-(int Number) const
{
	complex Result;
	Result.Real = this->Real - Number;
	Result.Imag = this->Imag;
	return Result;
}

complex complex::operator*(complex Number) const
{
	complex Result;
	Result.Real =   this->Real * Number.Real
	              - this->Imag * Number.Imag;
	Result.Imag =   this->Real * Number.Imag
	              + this->Imag * Number.Real;
	return Result;
}

complex complex::operator*(imaginary Number) const
{
	complex Result;
	Result.Real = -this->Imag * Number.Value;
	Result.Imag =  this->Real * Number.Value;
	return Result;
}

complex complex::operator*(double Number) const
{
	complex Result;
	Result.Real = this->Real * Number;
	Result.Imag = this->Imag * Number;
	return Result;
}

complex complex::operator*(int Number) const
{
	complex Result;
	Result.Real = this->Real * Number;
	Result.Imag = this->Imag * Number;
	return Result;
}

complex complex::operator/(complex Number) const
{
	complex Result;
	double  subterm = Number.Real * Number.Real + Number.Imag * Number.Imag;
	Result.Real     = (this->Real * Number.Real + this->Imag * Number.Imag) / subterm;
	Result.Imag     = (this->Imag * Number.Real - this->Real * Number.Imag) / subterm;
	return Result;
}

complex complex::operator/(imaginary Number) const
{
	complex Result;
	Result.Real     =  this->Imag / Number.Value;
	Result.Imag     = -this->Real / Number.Value;
	return Result;
}

complex complex::operator/(double Number) const
{
	complex Result;
	Result.Real = this->Real / Number;
	Result.Imag = this->Imag / Number;
	return Result;
}

complex complex::operator/(int Number) const
{
	complex Result;
	Result.Real = this->Real / Number;
	Result.Imag = this->Imag / Number;
	return Result;
}

complex& complex::operator+=(complex Number)
{
	this->Real += Number.Real;
	this->Imag += Number.Imag;
	return *this;
}

complex& complex::operator+=(imaginary Number)
{
	this->Imag += Number.Value;
	return *this;
}

complex& complex::operator+=(double Number)
{
	this->Real += Number;
	return *this;
}

complex& complex::operator+=(int Number)
{
	this->Real += Number;
	return *this;
}

complex& complex::operator-=(complex Number)
{
	this->Real -= Number.Real;
	this->Imag -= Number.Imag;
	return *this;
}

complex& complex::operator-=(imaginary Number)
{
	this->Imag -= Number.Value;
	return *this;
}

complex& complex::operator-=(double Number)
{
	this->Real -= Number;
	return *this;
}

complex& complex::operator-=(int Number)
{
	this->Real -= Number;
	return *this;
}

complex& complex::operator*=(complex Number)
{
	*this = *this * Number;
	return *this;
}

complex& complex::operator*=(imaginary Number)
{
	*this = *this * Number;
	return *this;
}

complex& complex::operator*=(double Number)
{
	this->Real *= Number;
	this->Imag *= Number;
	return *this;
}

complex& complex::operator*=(int Number)
{
	this->Real *= Number;
	this->Imag *= Number;
	return *this;
}

complex& complex::operator/=(complex Number)
{
	*this = *this / Number;
	return *this;
}

complex& complex::operator/=(imaginary Number)
{
	*this = *this / Number;
	return *this;
}

complex& complex::operator/=(double Number)
{
	this->Real /= Number;
	this->Imag /= Number;
	return *this;
}

complex& complex::operator/=(int Number)
{
	this->Real /= Number;
	this->Imag /= Number;
	return *this;
}

bool complex::operator==(complex Number) const
{
	bool result = false;
	
	if( (this->Real == Number.Real) && (this->Imag == Number.Imag) )
	{
		result = true;
	}
	
	return result;
}

bool complex::operator==(imaginary Number) const
{
	bool result = false;
	
	if( (this->Real == 0.0) && (this->Imag == Number.Value) )
	{
		result = true;
	}
	
	return result;
}

bool complex::operator==(double Number) const
{
	bool result = false;
	
	if( (this->Real == Number) && (this->Imag == 0.0) )
	{
		result = true;
	}
	
	return result;
}

bool complex::operator==(int Number) const
{
	bool result = false;
	
	if( (this->Real == Number) && (this->Imag == 0) )
	{
		result = true;
	}
	
	return result;
}

bool complex::operator!=(complex Number) const
{
	bool result = true;
	
	if( (this->Real == Number.Real) && (this->Imag == Number.Imag) )
	{
		result = false;
	}
	
	return result;
}

bool complex::operator!=(imaginary Number) const
{
	bool result = true;
	
	if( (this->Real == 0.0) && (this->Imag == Number.Value) )
	{
		result = false;
	}
	
	return result;
}

bool complex::operator!=(double Number) const
{
	bool result = true;
	
	if( (this->Real == Number) && (this->Imag == 0.0) )
	{
		result = false;
	}
	
	return result;
}

bool complex::operator!=(int Number) const
{
	bool result = true;
	
	if( (this->Real == Number) && (this->Imag == 0) )
	{
		result = false;
	}
	
	return result;
}

complex operator+(double lhs, complex rhs)
{
	complex Result;
	Result.Real = lhs + rhs.Real;
	Result.Imag = rhs.Imag;
	return Result;
}

complex operator+(int lhs, complex rhs)
{
	complex Result;
	Result.Real = lhs + rhs.Real;
	Result.Imag = rhs.Imag;
	return Result;
}

complex operator-(complex rhs)
{
	complex Result;
	Result.Real = -rhs.Real;
	Result.Imag = -rhs.Imag;
	return Result;
}

complex operator-(double lhs, complex rhs)
{
	complex Result;
	Result.Real = lhs - rhs.Real;
	Result.Imag = -rhs.Imag;
	return Result;
}

complex operator-(int lhs, complex rhs)
{
	complex Result;
	Result.Real = lhs - rhs.Real;
	Result.Imag = -rhs.Imag;
	return Result;
}

complex operator*(double lhs, complex rhs)
{
	complex Result;
	Result.Real = lhs * rhs.Real;
	Result.Imag = lhs * rhs.Imag;
	return Result;
}

complex operator*(int lhs, complex rhs)
{
	complex Result;
	Result.Real = lhs * rhs.Real;
	Result.Imag = lhs * rhs.Imag;
	return Result;
}

complex operator/(double lhs, complex rhs)
{
	complex Result;
	double  subterm = rhs.Real * rhs.Real + rhs.Imag * rhs.Imag;
	
	Result.Real =  lhs * rhs.Real / subterm;
	Result.Imag = -lhs * rhs.Imag / subterm;
	return Result;
}

complex operator/(int lhs, complex rhs)
{
	complex Result;
	double  subterm = rhs.Real * rhs.Real + rhs.Imag * rhs.Imag;
	Result.Real     =  lhs * rhs.Real / subterm;
	Result.Imag     = -lhs * rhs.Imag / subterm;
	return Result;
}

std::ostream& operator<<(std::ostream& Stream, complex& Number)
{
	Stream << "(" << Number.Real << " + i" << Number.Imag << ")";
	return Stream;
}

std::istream& operator>>(std::istream& Stream, complex& Number) // Bit dodgy!
{
	Stream >> Number.Real;
	Stream >> Number.Imag;
	return Stream;
}

complex exp(complex Theta)
{
	complex Result;
	
	Result.Real = cos(Theta.Imag);
	Result.Imag = sin(Theta.Imag);
	
	Result = Result * exp(Theta.Real);
	
	return Result;
}

complex square_root(complex Number)
{
	complex Result;
	double  r;
	double  theta;

	r     = pow(Number.Real * Number.Real + Number.Imag * Number.Imag, 0.25);
	theta = atan2(Number.Imag, Number.Real) / 2;

	Result.Real = r * cos(theta);
	Result.Imag = r * sin(theta);

	return Result;
}

complex square_root(double Number)
{
	complex Result;
	
	if(Number < 0.0)
	{
		Result.Real = 0;
		Result.Imag = sqrt(-Number);
	}
	else
	{
		Result.Real = sqrt(Number);
		Result.Imag = 0;
	}
	
	return Result;
}
