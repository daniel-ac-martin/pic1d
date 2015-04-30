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

#ifndef FILE_ARGUMENTS_HEADER
#define FILE_ARGUMENTS_HEADER

#include "config.h"
#include "guis/guis.h"
#include "array.h"

extern "C"
{
#include <argp.h>
}

struct species_arguments
{
	char *   name;
	bool     name_set;
	int      particles;
	bool     particles_set;
	int      mode;
	bool     mode_set;
	double   plasma_freq;
	bool     plasma_freq_set;
	double   charge2mass;
	bool     charge2mass_set;
	double   v0;
	bool     v0_set;
	double   v1;
	bool     v1_set;
	double   x1;
	bool     x1_set;
	double   theta_x;
	bool     theta_x_set;
	double   theta_v;
	bool     theta_v_set;
};

struct arguments
{
//	char*    args[1];
	bool                     debug;
	gui_enum                 gui;
	bool                     gui_set;
	char const *             output;
	bool                     output_set;
	int                      energy_or_momentum;
	bool                     energy_or_momentum_set;
	int                      points;
	bool                     points_set;
	double                   length;
	bool                     length_set;
	Array<species_arguments> species;
	double                   time_step;
	bool                     time_step_set;
	int                      total_time_steps;
	bool                     total_time_steps_set;
	int                      weighting;
	bool                     weighting_set;
	bool                     verbose;
};

class Arguments
{
	public:
		Arguments(int argc, char ** argv);
		arguments * Args;
	protected:
	private:
		char *                   NameAndVersion;
		char *                   Contact;
		static argp_option       Options[12];
		static error_t           Parse(int key, char* value, argp_state* state);
		static char const *      ArgsExample;
		static char const *      Description;
		static arguments         Defaults;
		static argp_child        Children[2];
		static argp              ArgP;
		static argp_option       SpeciesOptions[10];
		static error_t           SpeciesParse(int key, char* value, argp_state* state);
		static char const *      SpeciesArgsExample;
		static char const *      SpeciesDescription;
		static species_arguments SpeciesDefaults;
		static argp              SpeciesArgP;
};

#endif
