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

#include "interface.h"

Interface::Interface()
{
	//
	// Set initial parameters here.
	//
	playing = false;	
	//
	// Default setup.
	//
	Setup();
}

Interface::~Interface()
{
}

int Interface::Setup()
{
	int result = -1;
	
	//
	// Success!
	//
	result = 0;
	
	return result;
}

int Interface::Reset()
{
	int result = -1;
	
	result = Setup();
	
	return result;
}

int Interface::Start()
{
	int result = -1;
	
	if(playing)
	{
		//
		// We are still running a simulation, the user must stop the
		// current simulation before beginning a new one.
		//
		result = 1;
	}
	else
	{
		result = Setup();
		
		if(result == 0)
		{
			playing = true;
		}
		else
		{
			result += 1;
		}
	}
	
	return result;
}

int Interface::Restart()
{
	int result = -1;
	
	if(playing)
	{
		//
		// We are still running a simulation, the user must stop the
		// current simulation before beginning a new one.
		//
		result = 1;
	}
	else
	{
		result = Reset();
		
		if(result == 0)
		{
			playing = true;
		}
		else
		{
			result += 1;
		}
	}
	
	return result;
}

int Interface::Pause()
{
	int result = -1;
	
	if(playing)
	{
		//
		// Pause.
		//
		playing = false;
		result  = 0;
	}
	else
	{
		//
		// We're already paused.
		//
		result = 1;
	}
	
	return result;
}

int Interface::Unpause()
{
	int result = -1;
	
	if(playing)
	{
		//
		// We're aren't paused.
		//
		result = 1;
	}
	else
	{
		//
		// Unpause.
		//
		playing = true;
		result  = 0;
	}
	
	return result;
}

int Interface::Stop()
{
	int result = -1;
	
	//
	// Stop and reset to initial conditions.
	//
	playing = false;
	result = Reset();
	
	return result;
}
/*
int Interface::Simulate()
{
	int result = -1;
	
	if(playing)
	{
		//
		// Perform nessessary maths here. Typically you would alter the
		// positions of objects etc...
		//
		result = 0;
	}
	
	return result;
}
*/
/*
int Interface::Draw()
{
	int result = 0;
	
	//
	// Draw our current scene. Take into account new positions of objects.
	//
	
	return result;
}
*/
