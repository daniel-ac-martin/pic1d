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

IMPLEMENT_APP_NO_MAIN(wxMain)

int wx_main(arguments Args)
{
	OurArgs = Args;
	int      zero = 0;
	wxChar** null = NULL;
	return wxEntry(zero, null);
}

bool wxMain::OnInit()
{
	/*
	//
	// Sort out arguments.
	//
	int argc    = this->argc;
	char** argv = new char*[argc];
	
	int i = 0;
	
	while(i < argc)
	{
		argv[i] = strdup(wxConvCurrent->cWX2MB(this->argv[i]));
		i++;
	}
	
	Arguments* ArgManager = new Arguments(argc, argv);
	
	// This won't work how I want it to.
	if(ArgManager->Args->debug)
	{
	}
	*/
	
	//
	// Set up GUI.
	//
	this->Frame = new FrameMain(OurArgs, NULL, _(APP_NAME), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE);
	Frame->Show(true);
	SetTopWindow(Frame);
	
	/*
	//
	// Clean up.
	//
	i = 0;
	
	while(i < argc)
	{
		free(argv[i]);
		i++;
	}
	*/
	
	//
	// Done.
	//
	return true;
}
