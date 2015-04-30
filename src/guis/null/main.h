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

#ifndef GUIS_NULL_MAIN_H
#define GUIS_NULL_MAIN_H

#include "config.h"
#include "gui.h"
#include "../../simulation.h"
#include "../../arguments.h"

#include <fstream>
#include <string>

class NullMain:
	public Simulation
{
	public:
		NullMain(arguments Args);
		virtual ~NullMain();
		
		virtual int Draw() {return Draw(false);}
		virtual int Draw(bool light);
		virtual int Execute();
	protected:
		std::ofstream* OutputPhaseSpace;
		std::ofstream OutputChargeDensity;
		std::ofstream OutputChargeDensityK;
		std::ofstream OutputElectricField;
		std::ofstream OutputKineticEnergy;
		std::ofstream OutputPotentialEnergy;
		std::ofstream OutputTotalEnergy;
		std::ofstream GnuPlotScript;
		
		virtual std::string GetFileName(std::string Extension, std::string FileName = "");
	private:
		void NullMainCommon(arguments Args);
};

#endif
