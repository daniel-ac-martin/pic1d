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

#ifndef FILE_CONFIG_HEADER
#	define FILE_CONFIG_HEADER

#	ifdef HAVE_CONFIG_H
#		include <config.h.temp>
#		undef malloc // Dodgy Fix!
#	endif

#	ifndef APP_NAME
#		ifdef PACKAGE_NAME
#			define APP_NAME PACKAGE_NAME
#		else
#			define APP_NAME "Plasma"
#		endif
#	endif
#	ifndef PROG_NAME
#		ifdef PACKAGE_NAME
#			define PROG_NAME PACKAGE_NAME
#		else
#			define PROG_NAME "plasma"
#		endif
#	endif
#	ifndef VERSION
#		ifdef PACKAGE_VERSION
#			define VERSION PACKAGE_VERSION
#		else
#			define VERSION "0.3"
#		endif
#	endif
#	ifndef NAME_AND_VERSION
#		ifdef PACKAGE_STRING
#			define NAME_AND_VERSION PACKAGE_STRING
#		else
#			define NAME_AND_VERSION "plasma 0.3"
#		endif
#	endif
#	ifndef EMAIL
#		ifdef PACKAGE_BUGREPORT
#			define EMAIL PACKAGE_BUGREPORT
#		else
#			define EMAIL "plasma@theging.com"
#		endif
#	endif

#	if HAVE_LIBGLUT || HAVE_LIBFREEGLUT || HAVE_LIBOPENGLUT
#		define HAVE_GLUT 1
#	endif

extern "C"
{
#	include <stdlib.h>
#	include "argp.h"
}

#	define CRASH() *((int*) NULL) = 1;
#	define assert(x) if(x); else { std::cerr << __FILE__ << ":" << __LINE__ << ": Warning: Assert failed." << std::endl; }
#	define assert_fatal(x) if(x); else { std::cerr << __FILE__ << ":" << __LINE__ << ": Error: Assert failed." << std::endl; CRASH();}

#endif
