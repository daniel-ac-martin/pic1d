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

#include "imaginary.h"
#include "complex.h"
#include <cmath>

imaginary& imaginary::operator=(const imaginary& Number)
{
	if(&Number != this)
	{
		this->Value = Number.Value;
	}
	
	return *this;
}

imaginary& imaginary::operator=(double Number)
{
	this->Value = Number;
	
	return *this;
}

imaginary& imaginary::operator=(int Number)
{
	this->Value = Number;
	
	return *this;
}

imaginary imaginary::operator+(imaginary Number) const
{
	imaginary Result;
	Result.Value = this->Value + Number.Value;
	return Result;
}

complex imaginary::operator+(complex Number) const
{
	complex Result;
	Result.Real = Number.Real;
	Result.Imag = this->Value + Number.Imag;
	return Result;
}

complex imaginary::operator+(double Number) const
{
	complex Result;
	Result.Real = Number;
	Result.Imag = this->Value;
	return Result;
}

complex imaginary::operator+(int Number) const
{
	complex Result;
	Result.Real = Number;
	Result.Imag = this->Value;
	return Result;
}

imaginary imaginary::operator-(imaginary Number) const
{
	imaginary Result;
	Result.Value = this->Value - Number.Value;
	return Result;
}

complex imaginary::operator-(complex Number) const
{
	complex Result;
	Result.Real = -Number.Real;
	Result.Imag = this->Value - Number.Imag;
	return Result;
}

complex imaginary::operator-(double Number) const
{
	complex Result;
	Result.Real = -Number;
	Result.Imag = this->Value;
	return Result;
}

complex imaginary::operator-(int Number) const
{
	complex Result;
	Result.Real = -Number;
	Result.Imag = this->Value;
	return Result;
}

double imaginary::operator*(imaginary Number) const
{
	double Result;
	Result = -this->Value * Number.Value;
	return Result;
}

complex imaginary::operator*(complex Number) const
{
	complex Result;
	Result.Real = -this->Value * Number.Imag;
	Result.Imag =  this->Value * Number.Real;
	return Result;
}

imaginary imaginary::operator*(double Number) const
{
	imaginary Result;
	Result.Value = this->Value * Number;
	return Result;
}

imaginary imaginary::operator*(int Number) const
{
	imaginary Result;
	Result.Value = this->Value * Number;
	return Result;
}

double imaginary::operator/(imaginary Number) const
{
	double Result;
	Result = this->Value / Number.Value;
	return Result;
}

complex imaginary::operator/(complex Number) const
{
	complex Result;
	double  subterm = Number.Real * Number.Real + Number.Imag * Number.Imag;
	Result.Real     = this->Value * Number.Imag / subterm;
	Result.Imag     = this->Value * Number.Real / subterm;
	return Result;
}

imaginary imaginary::operator/(double Number) const
{
	imaginary Result;
	Result.Value = this->Value / Number;
	return Result;
}

imaginary imaginary::operator/(int Number) const
{
	imaginary Result;
	Result.Value = this->Value / Number;
	return Result;
}

imaginary& imaginary::operator+=(imaginary Number)
{
	this->Value += Number.Value;
	return *this;
}

imaginary& imaginary::operator-=(imaginary Number)
{
	this->Value -= Number.Value;
	return *this;
}

imaginary& imaginary::operator*=(double Number)
{
	this->Value *= Number;
	return *this;
}

imaginary& imaginary::operator*=(int Number)
{
	this->Value *= Number;
	return *this;
}

imaginary& imaginary::operator/=(double Number)
{
	this->Value /= Number;
	return *this;
}

imaginary& imaginary::operator/=(int Number)
{
	this->Value /= Number;
	return *this;
}

bool imaginary::operator==(imaginary Number) const
{
	bool result = false;
	
	if(this->Value == Number.Value)
	{
		result = true;
	}
	
	return result;
}

bool imaginary::operator==(complex Number) const
{
	bool result = false;
	
	if( (0.0 == Number.Real) && (this->Value == Number.Imag) )
	{
		result = true;
	}
	
	return result;
}

bool imaginary::operator!=(imaginary Number) const
{
	bool result = true;
	
	if(this->Value == Number.Value)
	{
		result = false;
	}
	
	return result;
}

bool imaginary::operator!=(complex Number) const
{
	bool result = true;
	
	if( (0.0 == Number.Real) && (this->Value == Number.Imag) )
	{
		result = false;
	}
	
	return result;
}

complex operator+(double lhs, imaginary rhs)
{
	complex Result;
	Result.Real = lhs;
	Result.Imag = rhs.Value;
	return Result;
}

complex operator+(int lhs, imaginary rhs)
{
	complex Result;
	Result.Real = lhs;
	Result.Imag = rhs.Value;
	return Result;
}

imaginary operator-(imaginary rhs)
{
	imaginary Result;
	Result.Value = -rhs.Value;
	return Result;
}

complex operator-(double lhs, imaginary rhs)
{
	complex Result;
	Result.Real = lhs;
	Result.Imag = -rhs.Value;
	return Result;
}

complex operator-(int lhs, imaginary rhs)
{
	complex Result;
	Result.Real = lhs;
	Result.Imag = -rhs.Value;
	return Result;
}

imaginary operator*(double lhs, imaginary rhs)
{
	imaginary Result;
	Result.Value = lhs * rhs.Value;
	return Result;
}

imaginary operator*(int lhs, imaginary rhs)
{
	imaginary Result;
	Result.Value = lhs * rhs.Value;
	return Result;
}

imaginary operator/(double lhs, imaginary rhs)
{
	imaginary Result;
	Result.Value = -lhs / rhs.Value;
	return Result;
}

imaginary operator/(int lhs, imaginary rhs)
{
	imaginary Result;
	Result.Value = -lhs / rhs.Value;
	return Result;
}

std::ostream& operator<<(std::ostream& Stream, imaginary& Number)
{
	Stream << "i" << Number.Value;
	return Stream;
}

std::istream& operator>>(std::istream& Stream, imaginary& Number) // Bit dodgy!
{
	Stream >> Number.Value;
	return Stream;
}

complex exp(imaginary Theta)
{
	complex Result;
	
	Result.Real = cos(Theta.Value);
	Result.Imag = sin(Theta.Value);
	
	return Result;
}

imaginary square_root(imaginary Number) // CHECKME: !!
{
	imaginary Result;
	Result.Value = sqrt(Number.Value);
	return Result;
}
