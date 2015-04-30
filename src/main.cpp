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

#include "main.h"
#include "arguments.h"
#include "guis/gnuplot/gui.h"
#include "guis/null/gui.h"
#include "guis/wxwidgets/gui.h"

int main(int argc, char* argv[])
{
	int result = -1;
	
	//
	// Sort out arguments.
	//
	Arguments* ArgManager = new Arguments(argc, argv);
	arguments Args = *(ArgManager->Args);
	
	// This won't work how I want it to.
	if(Args.debug)
	{
	}
	
	//
	// Start a GUI.
	//
	if(Args.gui == GNUPLOT_GUI)
	{
		// Start the GnuPlot interface.
		result = gnuplot_main(Args);
	}
	else if(Args.gui == NULL_GUI)
	{
		// Start the null interface.
		result = null_main(Args);
	}
	else if(Args.gui == WXWIDGETS_GUI)
	{
		// Start the wxWidgets interface.
		result = wx_main(Args);
	}
	else
	{
		// No GUI.
		result = -2;
	}
	
	delete ArgManager;
	
	return result;
}
