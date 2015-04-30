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

#ifndef FILE_COMPLEX_H
#define FILE_COMPLEX_H

class complex;

#include <iostream>
#include "imaginary.h"

class complex
{
	public:
		complex()
		{
			this->Real = 0;
			this->Imag = 0;
		}
		complex(double real, double imag)
		{
			this->Real = real;
			this->Imag = imag;
		}
		complex(const complex& Number)
		{
			this->Real = Number.Real;
			this->Imag = Number.Imag;
		}
		complex(imaginary Number)
		{
			this->Real = 0;
			this->Imag = Number.Value;
		}
		complex(double Number)
		{
			this->Real = Number;
			this->Imag = 0;
		}
		complex(int Number)
		{
			this->Real = Number;
			this->Imag = 0;
		}
		~complex()
		{
		}
		
		double Real;
		double Imag;
		
		complex Conjugate()                       const;
		double  Magnitude()                       const;
		complex& operator=(const complex& Number);
		complex& operator=(imaginary Number);
		complex& operator=(double Number);
		complex& operator=(int Number);
		complex  operator+(complex Number)        const;
		complex  operator+(imaginary Number)      const;
		complex  operator+(double Number)         const;
		complex  operator+(int Number)            const;
		complex  operator-(complex Number)        const;
		complex  operator-(imaginary Number)      const;
		complex  operator-(double Number)         const;
		complex  operator-(int Number)            const;
		complex  operator*(complex Number)        const;
		complex  operator*(imaginary Number)      const;
		complex  operator*(double Number)         const;
		complex  operator*(int Number)            const;
		complex  operator/(complex Number)        const;
		complex  operator/(imaginary Number)      const;
		complex  operator/(double Number)         const;
		complex  operator/(int Number)            const;
		complex& operator+=(complex Number);
		complex& operator+=(imaginary Number);
		complex& operator+=(double Number);
		complex& operator+=(int Number);
		complex& operator-=(complex Number);
		complex& operator-=(imaginary Number);
		complex& operator-=(double Number);
		complex& operator-=(int Number);
		complex& operator*=(complex Number);
		complex& operator*=(imaginary Number);
		complex& operator*=(double Number);
		complex& operator*=(int Number);
		complex& operator/=(complex Number);
		complex& operator/=(imaginary Number);
		complex& operator/=(double Number);
		complex& operator/=(int Number);
		bool     operator==(complex Number)       const;
		bool     operator==(imaginary Number)     const;
		bool     operator==(double Number)        const;
		bool     operator==(int Number)           const;
		bool     operator!=(complex Number)       const;
		bool     operator!=(imaginary Number)     const;
		bool     operator!=(double Number)        const;
		bool     operator!=(int Number)           const;
	protected:
	private:
};

/*
 * Standard arithmetic operator overloading.
 */
complex operator+(double lhs, complex rhs);
complex operator+(int lhs, complex rhs);
complex operator-(complex rhs);
complex operator-(double lhs, complex rhs);
complex operator-(int lhs, complex rhs);
complex operator*(double lhs, complex rhs);
complex operator*(int lhs, complex rhs);
complex operator/(double lhs, complex rhs);
complex operator/(int lhs, complex rhs);

/*
 * iostream operator overloading for the complex class.
 */
std::ostream& operator<<(std::ostream& Stream, complex& Number);
std::istream& operator>>(std::istream& Stream, complex& Number); // Bit dodgy!

/*
 * Extention to the exp function!
 */
complex exp(complex Theta);

/*
 * Extention to the sqrt function!
 */
complex square_root(complex Number);
complex square_root(double Number);

#endif
