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

#include "arguments.h"
#include "guis/guis.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string.h>

using std::cerr;
using std::endl;

const char * argp_program_version     = NAME_AND_VERSION;
const char * argp_program_bug_address = EMAIL;

/*
 * Set available options.
 */
argp_option Arguments::Options[] = 
{
	{"debug",       'd', 0,                  OPTION_HIDDEN,       "Debug mode"},
	{"gui",         1,   "GUI",              0,                   "Select GUI"},
	{"output",      'o', "FILE",             0,                   "Output to FILE"},
	{"conserve",    'c', "e/m",              0,                   "Set conservation scheme to energy or momentum"},
	{"length",      'l', "NUMBER",           0,                   "Set length of the system to NUMBER"},
	{"points",      'p', "INTEGER",          0,                   "Set the number of grid points to INTEGER"},
	{"species",     'S', "NAME [OPTION...]", OPTION_ARG_OPTIONAL, "Add new species with name, NAME and attributes OPTIONs"},
	{"time-step",   't', "STEP",             0,                   "Set time step to STEP"},
	{"total-steps", 'T', "INTEGER",          0,                   "Set total number of time steps to INTEGER"},
	{"weighting",   'W', "INTEGER",          0,                   "Set weighting scheme to INTEGER"},
	{"verbose",     'v', 0,                  0,                   "Produce verbose output"},
	{0}
};

/*
 * Set the description.
 */
char const * Arguments::Description = "A plasma simulator. Written by Daniel Martin, 2006.";

/*
 * Set the arguments example.
 */
char const * Arguments::ArgsExample = "-l 6.283 -p 512 -t 0.1 -T 500 -W 1";

arguments Arguments::Defaults =
{
	false,                            //debug
	GNUPLOT_GUI,                      //gui
	false,                            //gui_set
	"/dev/null",                      //output - FIXME: Fix for windows?!
	false,                            //output_set
	0,                                //energy_or_momentum
	false,                            //energy_or_momentum_set
	256,                              //points
	false,                            //points_set
	2 * M_PI,                         //length
	false,                            //length_set
	vector<species_arguments>(), //species
	0,                                //time_step
	false,                            //time_step_set
	256,                              //total_time_steps
	false,                            //total_time_steps_set
	1,                                //weighting
	false,                            //weighting_set
	false                             //verbose
};

argp_option Arguments::SpeciesOptions[] = 
{
	{"particles",   'P', "INTEGER", 0, "Set the number of particles in the species to INTEGER"},
	{"mode",        'm', "INTEGER", 0, "Set the mode to be given an initial pertubation to INTEGER"},
	{"plasma-freq", 'w', "NUMBER",  0, "Set the plasma frequency to NUMBER"},
	{"charge2mass", 'q', "NUMBER",  0, "Set the charge to mass ratio to NUMBER"},
	{"v0",          2,   "NUMBER",  0, "Set the drift velocity to NUMBER"},
	{"v1",          3,   "NUMBER",  0, "Set the amplitude velocity pertubation to NUMBER"},
	{"x1",          4,   "NUMBER",  0, "Set the amplitude position pertubation to NUMBER"},
	{"theta-x",     5,   "NUMBER",  0, "Set the position pertubation phase to NUMBER"},
	{"theta-v",     6,   "NUMBER",  0, "Set the velocity pertubation phase to NUMBER"},
	{0}
};

char const * Arguments::SpeciesArgsExample = "--species -P 2048 -m 1 -q -1 -w 1 --v0 1 --x1 0.0001 --species -P 2048 -m 1 -q -1 -w 1 --v0 -1 --x1 -0.0001";

char const * Arguments::SpeciesDescription = "A group of paricles with common properties.";

argp Arguments::SpeciesArgP = {Arguments::SpeciesOptions, Arguments::SpeciesParse, Arguments::SpeciesArgsExample, Arguments::SpeciesDescription};

species_arguments Arguments::SpeciesDefaults =
{
	NULL,  //name
	false, //name_set
	1024,  //particle_number
	false, //particle_number_set
	1,     //mode
	false, //mode_set
	1,     //plasma_freq
	false, //plasma_freq_set
	1,     //charge_to_mass
	false, //charge_to_mass_set
	0,     //v0
	false, //v0_set
	0,     //v1
	false, //v1_set
	0,     //x1
	false, //x1_set
	0,     //theta_x
	false, //theta_x_set
	0,     //theta_v
	false  //theta_v_set
};

argp_child Arguments::Children[] = 
{
	{&Arguments::SpeciesArgP, 0, "Species options:", 1},
	{0}
};

/*
 * Setup the argp structure.
 */
argp Arguments::ArgP = {Arguments::Options, Arguments::Parse, Arguments::ArgsExample, Arguments::Description, Arguments::Children};

/*
 * Constructor
 */
Arguments::Arguments(int argc, char ** argv)
{
	/*
	 * Set the name and version.
	 */
	char* buffer = new char[strlen(argp_program_version)];
	this->NameAndVersion = strcpy(buffer, argp_program_version);
	delete[] buffer; //FIXME: Why does this segfault for x.x.x?!
	
	/*
	 * Set contact e-mail address.
	 */
	buffer = new char[strlen(argp_program_bug_address)];
	this->Contact = strcpy(buffer, argp_program_bug_address);
	delete[] buffer;
	
	this->Args = new arguments;
	/*
	 * Set the defaults.
	 */
	*(this->Args) = Arguments::Defaults;
	
	/*
	 * Invoke argp.
	 */
	argp_parse(&this->ArgP, argc, argv, 0 , 0, this->Args);
}

error_t Arguments::Parse(int key, char * value, argp_state * state)
{
	state->child_inputs[0] = state->input; // Fudge?!
	arguments* Args = reinterpret_cast<arguments*>(state->input);
	char* test = NULL;
	
	switch(key)
	{
		case 'd':
			Args->debug = true;
			break;
		case 1:
			if(strcmp(value, "gnuplot") == 0)
			{
				Args->gui     = GNUPLOT_GUI;
				Args->gui_set = true;
			}
			else if(strcmp(value, "null") == 0)
			{
				Args->gui     = NULL_GUI;
				Args->gui_set = true;
			}
			else if(strcmp(value, "wxwidgets") == 0)
			{
				Args->gui     = WXWIDGETS_GUI;
				Args->gui_set = true;
			}
			else
			{
				// Inform the user of his/her options.
				cerr << "GUI must be one of; gnuplot, null, wxwidgets.\n"
				     << endl;
				argp_usage(state);
			}
			break;
		case 'o':
			Args->output     = value;
			Args->output_set = true;
			break;
		case 'c':
			if     (strcmp("m", value)) Args->energy_or_momentum = 0;
			else if(strcmp("e", value)) Args->energy_or_momentum = 1;
			else
			{
				// `value' is nonsense.
				cerr << "Choices for conservation schemes are `m' (momentum - recommended) or `e' (energy).\n"
				     << endl;
				argp_usage(state);
			}
			Args->energy_or_momentum_set = true;
			break;
		case 'l':
			test = NULL;
			Args->length = strtod(value, &test);
			if( (strcmp(test, "") != 0) || (Args->length <= 0.0) )
			{
				// `value' is nonsense.
				cerr << "LENGTH must be a positive, non-zero number.\n"
				     << endl;
				argp_usage(state);
			}
			Args->length_set = true;
			break;
		case 'p':
			Args->points = atoi(value);
			if(Args->points <= 0)
			{
				// `value' is nonsense.
				cerr << "NUMBER must be a positive, non-zero integer, and should be a power of 2.\n"
				     << endl;
				argp_usage(state);
			}
			Args->points_set = true;
			break;
		case 'S':
			Args->species.push_back(Arguments::SpeciesDefaults);
			if(value != NULL)
			{
				strcpy(Args->species[Args->species.size() - 1].name, value);
				
				Args->species[Args->species.size() - 1].name_set = true;
			}
			break;
		case 't':
			test = NULL;
			Args->time_step = strtod(value, &test);
			if( (strcmp(test, "") != 0) || (Args->time_step == 0.0) )
			{
				// `value' is nonsense.
				cerr << "STEP must be a non-zero number.\n"
				     << endl;
				argp_usage(state);
			}
			Args->time_step_set = true;
			break;
		case 'T':
			Args->total_time_steps = atoi(value);
			if(Args->total_time_steps <= 0)
			{
				// `value' is nonsense.
				cerr << "NUMBER must be a positive, non-zero integer.\n"
				     << endl;
				argp_usage(state);
			}
			Args->total_time_steps_set = true;
			break;
		case 'W':
			if     (strcmp("0", value) == 0) Args->weighting = 0;
			else if(strcmp("1", value) == 0) Args->weighting = 1;
			else
			{
				// `value' is nonsense.
				cerr << "Choices for weighting schemes are `0' (0th order - NGP) or `1' (1st order - CIC).\n"
				     << endl;
				argp_usage(state);
			}
			Args->weighting_set = true;
			break;
		case 'v':
			Args->verbose = true;
			break;
		case ARGP_KEY_ARG:
			if(state->arg_num >= 0)
			{
				argp_usage(state);
			}
			//Args->args[state->arg_num] = value;
			//Args->input = value;
			break;
		case ARGP_KEY_END:
			if(state->arg_num < 0)
			{
				argp_usage(state);
			}
			break;
		default:
			return ARGP_ERR_UNKNOWN;
			break;
	}
	
	return 0;
}

error_t Arguments::SpeciesParse(int key, char * value, argp_state * state)
{
	arguments * Args = reinterpret_cast<arguments *>(state->input);
	char * test = NULL;
	int n = Args->species.size() - 1;
	
	if(n >= 0)
	{
		switch(key)
		{
			case 'P':
				Args->species[n].particles = atoi(value);
				if(Args->species[n].particles <= 0)
				{
					// `value' is nonsense.
					argp_error(state, "The argument passed to -P/--particles, INTEGER, must be a positive, non-zero integer.");
				}
				Args->species[n].particles_set = true;
				break;
			case 'm':
				Args->species[n].mode = atoi(value);
				if(Args->species[n].mode <= 0)
				{
					// `value' is nonsense.
					argp_error(state, "The argument passed to -m/--mode, INTEGER, must be a positive, non-zero integer.");
				}
				Args->species[n].mode_set = true;
				break;
			case 'w':
				test = NULL;
				Args->species[n].plasma_freq = strtod(value, &test);
				if( (strcmp(test, "") != 0) || (Args->species[n].plasma_freq == 0.0) )
				{
					// `value' is nonsense.
					argp_error(state, "The argument passed to -w/--plasma-freq, NUMBER, must be a non-zero number.");
				}
				Args->species[n].plasma_freq_set = true;
				break;
			case 'q':
				test = NULL;
				Args->species[n].charge2mass = strtod(value, &test);
				if( (strcmp(test, "") != 0) || (Args->species[n].charge2mass == 0.0) )
				{
					// `value' is nonsense.
					argp_error(state, "The argument passed to -q/--charge2mass, NUMBER, must be a non-zero number.");
				}
				Args->species[n].charge2mass_set = true;
				break;
			case 2:
				test = NULL;
				Args->species[n].v0 = strtod(value, &test);
				if(strcmp(test, "") != 0)
				{
					// `value' is nonsense.
					argp_error(state, "The argument passed to --v0, NUMBER, must be a valid number.");
				}
				Args->species[n].v0_set = true;
				break;
			case 3:
				test = NULL;
				Args->species[n].v1 = strtod(value, &test);
				if(strcmp(test, "") != 0)
				{
					// `value' is nonsense.
					argp_error(state, "The argument passed to --v1, NUMBER, must be a valid number.");
				}
				Args->species[n].v1_set = true;
				break;
			case 4:
				test = NULL;
				Args->species[n].x1 = strtod(value, &test);
				if(strcmp(test, "") != 0)
				{
					// `value' is nonsense.
					argp_error(state, "The argument passed to --x1, NUMBER, must be a valid number.");
				}
				Args->species[n].x1_set = true;
				break;
			case 5:
				test = NULL;
				Args->species[n].theta_x = strtod(value, &test);
				if(strcmp(test, "") != 0)
				{
					// `value' is nonsense.
					argp_error(state, "The argument passed to --theta-x, NUMBER, must be a valid number.");
				}
				Args->species[n].theta_x_set = true;
				break;
			case 6:
				test = NULL;
				Args->species[n].theta_v = strtod(value, &test);
				if(strcmp(test, "") != 0)
				{
					// `value' is nonsense.
					argp_error(state, "The argument passed to --theta-v, NUMBER, must be a valid number.");
				}
				Args->species[n].theta_v_set = true;
				break;
			case ARGP_KEY_ARG:
				if(state->arg_num >= 0) argp_usage(state);
				break;
			case ARGP_KEY_END:
				if(state->arg_num < 0) argp_usage(state);
				break;
			default:
				return ARGP_ERR_UNKNOWN;
				break;
		}
	}
	else
	{
		switch(key)
		{
			case 'P':
			case 'm':
			case 'w':
			case 'q':
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				argp_error(state, "No species to assign attribute to. Try using --species first.");
				break;
			case ARGP_KEY_ARG:
				if(state->arg_num >= 0) argp_usage(state);
				break;
			case ARGP_KEY_END:
				if(state->arg_num < 0) argp_usage(state);
				break;
			default:
				return ARGP_ERR_UNKNOWN;
				break;
		}
	}
	
	return 0;
}
