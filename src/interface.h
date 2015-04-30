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

#ifndef INTERFACE_H
#define INTERFACE_H

class Interface;

#include "config.h"

class Interface
{
	public:
		Interface();
		virtual ~Interface();
		
		virtual int Start();
		virtual int Restart();
		virtual int Pause();
		virtual int Unpause();
		virtual int Stop();
		virtual int Simulate() = 0;
		virtual int Draw() = 0;
	protected:
		bool playing;
		
		virtual int Setup();
		virtual int Reset();
	private:
};

#endif
