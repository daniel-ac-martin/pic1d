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

#ifndef FILE_ARRAY_HEADER
#define FILE_ARRAY_HEADER

#include "config.h"

template <class T>
class Array
{
	public:
		// Constructors
		Array(int n = 0);
		Array(const Array<T>& Value);
		// Destructor
		virtual ~Array();
		
		int Elements;
		
		virtual int       Empty();
		virtual int       Push(T element);
		virtual T         Pop(int n = -1);
		virtual T*        c_array();
		// Operations
		Array<T>&         operator=(const Array<T>& Value);
		Array<T>&         operator=(const int special);
		virtual T&        operator[](int n);
		virtual const T&  operator[](int n) const;
	protected:
		T* Table;
	private:
};

#include "array.cpp"

#endif
