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
#include "array.h"
#else
#include <iostream>

//
// Constructors
//
template <class T>
Array<T>::Array(int n)
{
	this->Table = new T[n];
	this->Elements = n;
}

template <class T>
Array<T>::Array(const Array<T>& Value)
{
	int n = 0;
	
	this->Elements = Value.Elements;
	this->Table = new T[this->Elements];
	
	while(n < this->Elements)
	{
		this->Table[n] = Value[n];
		n++;
	}
}

//
// Destructor
//
template <class T>
Array<T>::~Array()
{
	delete[] this->Table;
}

//
// Operations
//
template <class T>
Array<T>& Array<T>::operator=(const Array<T>& Value)
{
	int n = 0;
	
	if(&Value != this)
	{
		this->Elements = Value.Elements;
		delete[] this->Table;
		this->Table = new T[this->Elements];
		
		while(n < this->Elements)
		{
			this->Table[n] = Value[n];
			n++;
		}
	}
	
	return *this;
}

template <class T>
Array<T>& Array<T>::operator=(const int special)
{
	switch(special)
	{
		case 0:
			this->Empty();
			break;
		default:
			// Fail, elegantly.
			std::cerr << "Unable to understand the special integer, " << special << " in the assignment." << std::endl;
			//throw(BadSpecial);
			break;
	}
	
	return *this;
}

template <class T>
T& Array<T>::operator[](int n)
{
	if(!((0 <= n) && (n < this->Elements)))
	{
		std::cerr << "Request for array element out of bounds." << std::endl;
		CRASH()
	}
	
	return this->Table[n];
}

template <class T>
const T& Array<T>::operator[](int n) const
{
	if(!((0 <= n) && (n < this->Elements)))
	{
		std::cerr << "Request for array element out of bounds." << std::endl;
		CRASH()
	}
	
	return this->Table[n];
}

template <class T>
int Array<T>::Empty()
{
	int result = -1;
	
	delete[] this->Table;
	this->Table    = new T[0];
	this->Elements = 0;
	result         = 0;
	
	return result;
}

template <class T>
int Array<T>::Push(T element)
{
	int      result  = 0;
	int      n       = 0;
	Array<T> Buffer;
	
	Buffer = *this;
	
	delete[] this->Table;
	this->Table = new T[this->Elements + 1];
	
	while(n < this->Elements)
	{
		this->Table[n] = Buffer[n];
		n++;
	}
	this->Table[n] = element;
	
	this->Elements++;
	
	return result;
}

template <class T>
T Array<T>::Pop(int n)
{
	T result;
	int      m       = 0;
	Array<T> Buffer;
	
	if(!((0 <= n) && (n < this->Elements)))
	{
		Buffer = *this;
		
		delete[] this->Table;
		this->Table = new T[this->Elements - 1];
		
		while(m < n)
		{
			this->Table[m] = Buffer[m];
			m++;
		}
		result = Buffer[m++];
		while(m < Buffer.Elements)
		{
			this->Table[m - 1] = Buffer[m];
			m++;
		}
		
		this->Elements--;
	}
	else
	{
		std::cerr << "Request for array element out of bounds." << std::endl;
		CRASH()
	}
	
	return result;
}
template <class T>
T* Array<T>::c_array()
{
	return Table;
}

#endif
