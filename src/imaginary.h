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

#ifndef FILE_IMAGINARY_H
#define FILE_IMAGINARY_H

class complex;

#include <iostream>

class imaginary
{
	public:
		imaginary()
		{
			this->Value = 0;
		}
		imaginary(int value)
		{
			this->Value = value;
		}
		imaginary(double value)
		{
			this->Value = value;
		}
		imaginary(const imaginary& Number)
		{
			this->Value = Number.Value;
		}
		~imaginary()
		{
		}
		
		double Value;
		
		imaginary& operator=(const imaginary& Number);
		imaginary& operator=(double Number);
		imaginary& operator=(int Number);
		imaginary  operator+(imaginary Number)        const;
		complex    operator+(complex Number)          const;
		complex    operator+(double Number)           const;
		complex    operator+(int Number)              const;
		imaginary  operator-(imaginary Number)        const;
		complex    operator-(complex Number)          const;
		complex    operator-(double Number)           const;
		complex    operator-(int Number)              const;
		double     operator*(imaginary Number)        const;
		complex    operator*(complex Number)          const;
		imaginary  operator*(double Number)           const;
		imaginary  operator*(int Number)              const;
		double     operator/(imaginary Number)        const;
		complex    operator/(complex Number)          const;
		imaginary  operator/(double Number)           const;
		imaginary  operator/(int Number)              const;
		imaginary& operator+=(imaginary Number);
		imaginary& operator-=(imaginary Number);
		imaginary& operator*=(double Number);
		imaginary& operator*=(int Number);
		imaginary& operator/=(double Number);
		imaginary& operator/=(int Number);
		bool       operator==(imaginary Number)       const;
		bool       operator==(complex Number)         const;
		bool       operator!=(imaginary Number)       const;
		bool       operator!=(complex Number)         const;
	protected:
	private:
};

/*
 * Standard arithmetic operator overloading.
 */
complex   operator+(double lhs, imaginary rhs);
complex   operator+(int lhs, imaginary rhs);
imaginary operator-(imaginary rhs);
complex   operator-(double lhs, imaginary rhs);
complex   operator-(int lhs, imaginary rhs);
imaginary operator*(double lhs, imaginary rhs);
imaginary operator*(int lhs, imaginary rhs);
imaginary operator/(double lhs, imaginary rhs);
imaginary operator/(int lhs, imaginary rhs);

/*
 * iostream operator overloading for the imaginary class.
 */
std::ostream& operator<<(std::ostream& Stream, imaginary& Number);
std::istream& operator>>(std::istream& Stream, imaginary& Number); // Bit dodgy!

/*
 * Extention to the exp function!
 */
complex exp(imaginary Theta);

/*
 * Extention to the sqrt function!
 */
imaginary square_root(imaginary Number);

/*
 * Define `i'!!
 */
const imaginary i(1);
const imaginary iUnity(1);

#endif
