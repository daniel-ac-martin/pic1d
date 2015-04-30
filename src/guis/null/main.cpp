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
#include "../../complex.h"
#include <time.h>

int null_main(arguments Args)
{
	int       result = -1;
	NullMain* Main   = new NullMain(Args);
	
	result = Main->Execute();
	
	delete Main;
	return result;
}

void NullMain::NullMainCommon(arguments Args)
{
	int n = 0;
	std::string filename;
	char buffer[8] = "";
	
	OutputPhaseSpace = new std::ofstream[Species.size()];
	
	while(n < Species.size())
	{
		filename  = "-PhaseSpace-";
		filename += gcvt((double)n, 3, buffer);
		filename += ".data";
		filename  = GetFileName(filename, Output);
		OutputPhaseSpace[n].open(filename.c_str(), std::ofstream::trunc);
		if(!OutputPhaseSpace[n]) std::cerr << "Error: Unable to open `" << filename << "'.";
		n++;
	}
	
	if(!OutputChargeDensity)     std::cerr << "Error: Unable to open `" << GetFileName("-ChargeDensity.data", Output) << "'.";
	if(!OutputChargeDensityK)    std::cerr << "Error: Unable to open `" << GetFileName("-ChargeDensityK.data", Output) << "'.";
	if(!OutputElectricField)     std::cerr << "Error: Unable to open `" << GetFileName("-ElectricField.data", Output) << "'.";
	if(!OutputKineticEnergy)     std::cerr << "Error: Unable to open `" << GetFileName("-KineticEnergy.data", Output) << "'.";
	if(!OutputPotentialEnergy)   std::cerr << "Error: Unable to open `" << GetFileName("-PotentialEnergy.data", Output) << "'.";
	if(!OutputTotalEnergy)       std::cerr << "Error: Unable to open `" << GetFileName("-TotalEnergy.data", Output) << "'.";
	if(!GnuPlotScript)           std::cerr << "Error: Unable to open `" << GetFileName(".plot", Output) << "'.";
	
	playing = true;
}

NullMain::NullMain(arguments Args):
	Simulation(Args),
	OutputChargeDensity( GetFileName("-ChargeDensity.data", Output).c_str(), std::ofstream::trunc),
	OutputChargeDensityK( GetFileName("-ChargeDensityK.data", Output).c_str(), std::ofstream::trunc),
	OutputElectricField( GetFileName("-ElectricField.data", Output).c_str(), std::ofstream::trunc),
	OutputKineticEnergy( GetFileName("-KineticEnergy.data", Output).c_str(), std::ofstream::trunc),
	OutputPotentialEnergy( GetFileName("-PotentialEnergy.data", Output).c_str(), std::ofstream::trunc),
	OutputTotalEnergy( GetFileName("-TotalEnergy.data", Output).c_str(), std::ofstream::trunc),
	GnuPlotScript( GetFileName(".plot", Output).c_str(), std::ofstream::trunc)
{
	NullMainCommon(Args);
}

NullMain::~NullMain()
{
	delete[] OutputPhaseSpace;
}

int NullMain::Draw(bool light)
{
	int    result = 0;
	int    n      = -1;
	int    m      = -1;
	double t      = LastTime / 1000000;
	double r      = 0;
	double v      = 0;
	double k      = 0;
	
	//Output << (last_time / 1000000) << "\t" << Particles[0].r << "\t" << ( 100 * (Energy() - InitialEnergy) / InitialEnergy) << std::endl;
	
	if(!light)
	{
		//
		// Output particle based information.
		//
		n = 0;
		while(n < Particles.size())
		{
			r = Particles[n].r;
			v = Particles[n].v;
			m = 0;
			while( (m < Species.size()) && (Particles[n].group != &Species[m]) ) m++;
			//                     Time         Location     Quantity
			OutputPhaseSpace[m] << t << "\t" << r << "\t" << v << std::endl;
			n++;
		}
		
		//
		// Output fields.
		//
		n = 0;
		while(n < int( (GridFinish - GridStart) / GridIncrement) )
		{
			r = GridStart + n * GridIncrement;
			k = n * GridIncrement;
			//                     Time         Location     Quantity
			OutputChargeDensity << t << "\t" << r << "\t" << ChargeDensity[n] << std::endl;
			OutputChargeDensityK << t << "\t" << k << "\t" << ChargeDensityK[n].Real << std::endl;
			OutputElectricField << t << "\t" << r << "\t" << EField[n] << std::endl;
			//Output        << (last_time / 1000000) << "\t" << GridStart + i * GridIncrement << "\t" << EField[i] << std::endl;
			n++;
		}
	}
	
	//
	// Output Energies
	//
	//                       Time         Energy
	OutputKineticEnergy   << t << "\t" << (Energy() - ESEnergy) << std::endl;
	OutputPotentialEnergy << t << "\t" << ESEnergy << std::endl;
	OutputTotalEnergy     << t << "\t" << Energy() << std::endl;
	
	return result;
}

int NullMain::Execute()
{
	int         result       = 0;
	int         n            = 0;
	int         m            = 0;
	int         plots        = 100;
	double      snap_step    = FinalTime / plots;
	bool        light        = false;
	char        buffer[8]    = "";
	std::string ext          = ".png";
	std::string filename     = "";
	std::string size         = "0.5";
	std::string pointsize    = "0.5";
	std::string ppointsize   = "0.25";
#ifdef HAVE_WINDOWS_H
	std::string gui_terminal = "windows";
#else
	std::string gui_terminal = "X11 #persist";
#endif
	gui_terminal = "png";
	
	GnuPlotScript << "#! /usr/bin/gnuplot\n"
	              << "\n";
	// Phase-space
	GnuPlotScript << "set terminal " << gui_terminal << "\n"
	              << "set xrange [" << GridStart<< ":" << GridFinish << "]\n"
	              << "set yrange [-3:3]\n"
	              << "set title \"Phase-Space\"\n"
	              << "set xlabel \"Position\"\n"
	              << "set ylabel \"Time\"\n"
	              << "set zlabel \"Velocity\"\n"
	              << "splot ";
	n = 0;
	while(n < Species.size())
	{
		filename  = "-PhaseSpace-";
		filename += gcvt((double)n, 3, buffer);
		filename  = GetFileName(filename + ".data", Output);
		GnuPlotScript << "\"" << filename << "\" using 2:1:3 title \"" << Species[n].name << "\"";
		n++;
		if(n < Species.size())
		{
			GnuPlotScript << ", \\\n      ";
		}
	}
	GnuPlotScript << "\n"
	              << "set terminal png\n"
	              << "set output \"" << GetFileName("-PhaseSpace.png", Output) << "\"\n"
	              << "set size " << size << "\n"
	              << "set pointsize " << ppointsize << "\n"
	              << "replot\n"
	              << "set output\n"
	              << "reset\n"
	              << "\n";
	n = 0;
	while(n < plots)
	{
		ext  = "-PhaseSpace-";
		ext += gcvt(n * snap_step, 5, buffer);
		GnuPlotScript << "set terminal " << gui_terminal << "\n"
		              << "set xrange [" << GridStart<< ":" << GridFinish << "]\n"
		              << "set yrange [-3:3]\n"
		              << "set parametric\n"
		              << "set title \"Phase-Space - t = " << n * snap_step << "\"\n"
		              << "set xlabel \"Position\"\n"
		              << "set ylabel \"Velocity\"\n"
		              << "plot ";
		m = 0;
		while(m < Species.size())
		{
			filename  = "-PhaseSpace-";
			filename += gcvt((double)m, 3, buffer);
			filename  = GetFileName(filename + ".data", Output);
			GnuPlotScript << "\"" << filename << "\" using 2:3 every ::" << n * Species[m].particles << "::" << (n + 1) * Species[m].particles - 1 << " title \"" << Species[m].name << "\"";
			m++;
			if(m < Species.size())
			{
				GnuPlotScript << ", \\\n     ";
			}
		}
		/*
		double x = GridStart + GridIncrement / 2;
		while(x < GridFinish)
		{
			GnuPlotScript << ", \\\n"
			              << "     " << x << ",t notitle";
			x += GridIncrement;
		}
		//*/
		GnuPlotScript << "\n"
		              << "set terminal png\n"
		              << "set output \"" << GetFileName(ext + ".png", Output) << "\"\n"
		              << "set size " << size << "\n"
		              << "set pointsize " << ppointsize << "\n"
		              << "replot\n"
		              << "set output\n"
		              << "reset\n"
		              << "\n";
		n++;
	}
	// Charge density
	GnuPlotScript << "set terminal " << gui_terminal << "\n"
	              << "set xrange [" << GridStart<< ":" << GridFinish << "]\n"
	              << "set title \"Charge Density\"\n"
	              << "set xlabel \"Position\"\n"
	              << "set ylabel \"Time\"\n"
	              << "set zlabel \"Charge Density\"\n"
	              << "splot "/* << -1 * Particles.size() / (GridFinish - GridStart) + 0.001 * 4 * pi / (GridFinish - GridStart) << " notitle, \\\n"
	              << "      " << -1 * Particles.size() / (GridFinish - GridStart) - 0.001 * 4 * pi / (GridFinish - GridStart) << " notitle, \\\n"*/
	              << "      \"" << GetFileName("-ChargeDensity.data", Output) << "\" using 2:1:3 notitle\n"
	              << "set terminal png\n"
	              << "set output \"" << GetFileName("-ChargeDensity.png", Output) << "\"\n"
	              << "set size " << size << "\n"
	              << "set pointsize " << pointsize << "\n"
	              << "replot\n"
	              << "set output\n"
	              << "reset\n"
	              << "\n";
	n = 0;
	while(n < plots)
	{
		ext  = "-ChargeDensity-";
		ext += gcvt(n * snap_step, 5, buffer);
		GnuPlotScript << "set terminal " << gui_terminal << "\n"
		              << "set xrange [" << GridStart<< ":" << GridFinish << "]\n"
	      	        << "set title \"Charge Density - t = " << n * snap_step << "\"\n"
	      	        << "set xlabel \"Position\"\n"
	      	        << "set ylabel \"Charge Density\"\n"
	      	        << "plot "/* << -1 * Particles.size() / (GridFinish - GridStart) << "-" << 0.001 * (2 * pi * 1.0 / (GridFinish - GridStart)) / ((GridFinish - GridStart)/Particles.size()) << "*sin(" << 2 * pi * 1.0 / (GridFinish - GridStart) << "*(x-" << GridStart << ")) notitle, \\\n"*/
	      	        << "     \"" << GetFileName("-ChargeDensity.data", Output) << "\" using 2:3 every ::" << n * ChargeDensity.size() << "::" << (n + 1) * ChargeDensity.size() - 1 << " notitle\n"
	      	        << "set terminal png\n"
	      	        << "set output \"" << GetFileName(ext + ".png", Output) << "\"\n"
	      	        << "set size " << size << "\n"
		              << "set pointsize " << pointsize << "\n"
	      	        << "replot\n"
	      	        << "set output\n"
	      	        << "reset\n"
	      	        << "\n";
		n++;
	}
	// Charge density K
	GnuPlotScript << "set terminal " << gui_terminal << "\n"
	              << "set title \"Charge Density K\"\n"
	              << "set xlabel \"Wavenumber\"\n"
	              << "set ylabel \"Time\"\n"
	              << "set zlabel \"Charge Density K\"\n"
	              << "splot " << -1 * Particles.size() / (GridFinish - GridStart) + 0.001 * (GridFinish - GridStart) / Particles.size() << " notitle, \\\n"
	              << "      " << -1 * Particles.size() / (GridFinish - GridStart) - 0.001 * (GridFinish - GridStart) / Particles.size() << " notitle, \\\n"
	              << "      \"" << GetFileName("-ChargeDensityK.data", Output) << "\" using 2:1:3 title \"\"\n"
	              << "set terminal png\n"
	              << "set output \"" << GetFileName("-ChargeDensityK.png", Output) << "\"\n"
	              << "set size " << size << "\n"
	              << "set pointsize " << pointsize << "\n"
	              << "replot\n"
	              << "set output\n"
	              << "reset\n"
	              << "\n";
	n = 0;
	while(n < plots)
	{
		ext  = "-ChargeDensityK-";
		ext += gcvt(n * snap_step, 5, buffer);
		GnuPlotScript << "set terminal " << gui_terminal << "\n"
		              << "set title \"Charge Density K - t = " << n * snap_step << "\"\n"
		              << "set xlabel \"Wavenumber\"\n"
		              << "set ylabel \"Charge Density K\"\n"
		              << "plot \"" << GetFileName("-ChargeDensityK.data", Output) << "\" using 2:3 every ::" << n * ChargeDensityK.size() << "::" << (n + 1) * ChargeDensityK.size() - 1 << " notitle\n"
		              << "set terminal png\n"
		              << "set output \"" << GetFileName(ext + ".png", Output) << "\"\n"
		              << "set size " << size << "\n"
		              << "set pointsize " << pointsize << "\n"
		              << "replot\n"
		              << "set output\n"
		              << "reset\n"
		              << "\n";
		n++;
	}
	// Electric field
	GnuPlotScript << "set terminal " << gui_terminal << "\n"
	              << "set xrange [" << GridStart<< ":" << GridFinish << "]\n"
	              << "set title \"Electric Field\"\n"
	              << "set xlabel \"Position\"\n"
	              << "set ylabel \"Time\"\n"
	              << "set zlabel \"Electric Field\"\n"
	              << "splot " /*<< 0.001 * (GridFinish - GridStart) * (GridFinish - GridStart) / (Particles.size() * 2 * 2 * pi) << " notitle, \\\n"
	              << "      " << -0.001 * (GridFinish - GridStart) * (GridFinish - GridStart) / (Particles.size() * 2 * 2 * pi) << " notitle, \\\n"*/
	              << "      \"" << GetFileName("-ElectricField.data", Output) << "\" using 2:1:3 title \"\"\n"
	              << "set terminal png\n"
	              << "set output \"" << GetFileName("-ElectricField.png", Output) << "\"\n"
	              << "set size " << size << "\n"
	              << "set pointsize " << pointsize << "\n"
	              << "replot\n"
	              << "set output\n"
	              << "reset\n"
	              << "\n";
	n = 0;
	while(n < plots)
	{
		ext  = "-ElectricField-";
		ext += gcvt(n * snap_step, 5, buffer);
		GnuPlotScript << "set terminal " << gui_terminal << "\n"
		              << "set xrange [" << GridStart<< ":" << GridFinish << "]\n"
		              << "set title \"Electric Field - t = " << n * snap_step << "\"\n"
		              << "set xlabel \"Position\"\n"
		              << "set ylabel \"Electric Field\"\n"
		              << "plot "/* << 0.001 * (GridFinish - GridStart) * (GridFinish - GridStart) / (Particles.size() * 2 * 2 * pi) << " notitle, \\\n"
		              << "     " << -0.001 * (GridFinish - GridStart) * (GridFinish - GridStart) / (Particles.size() * 2 * 2 * pi) << " notitle, \\\n"*/
		              << "     \"" << GetFileName("-ElectricField.data", Output) << "\" using 2:3 every ::" << n * EField.size() << "::" << (n + 1) * EField.size() - 1 << " notitle\n"
		              << "set terminal png\n"
		              << "set output \"" << GetFileName(ext + ".png", Output) << "\"\n"
		              << "set size " << size << "\n"
		              << "set pointsize " << pointsize << "\n"
		              << "replot\n"
		              << "set output\n"
		              << "reset\n"
		              << "\n";
		n++;
	}
	// Kinetic energy
	GnuPlotScript << "set terminal " << gui_terminal << "\n"
	              << "set title \"Kinetic Energy\"\n"
	              << "set xlabel \"Time\"\n"
	              << "set ylabel \"Kinetic Energy\"\n"
	              //<< "f(x) = A*sin(w*x)*sin(w*x);\n"
	              //<< "A = 3;\n"
	              //<< "w = 1;\n"
	              //<< "fit [1:*] f(x) \"" << GetFileName("-KineticEnergy.data", Output) << "\" using 1:2 via A, w;\n"
	              << "plot \"" << GetFileName("-KineticEnergy.data", Output) << "\" using 1:2 title \"\"\n"
	              //<< "     f(x) title \"Asin^2(wx)\";\n"
	              << "set terminal png\n"
	              << "set output \"" << GetFileName("-KineticEnergy.png", Output) << "\"\n"
	              << "set size " << size << "\n"
	              << "set pointsize " << pointsize << "\n"
	              << "replot\n"
	              << "set output\n"
	              << "reset\n"
	              << "\n"
	// Potential energy
	              << "set terminal " << gui_terminal << "\n"
	              << "set title \"Potential Energy\"\n"
	              << "set xlabel \"Time\"\n"
	              << "set ylabel \"Potential Energy\"\n"
	              << "plot \"" << GetFileName("-PotentialEnergy.data", Output) << "\" using 1:2 title \"\"\n"
	              << "set terminal png\n"
	              << "set output \"" << GetFileName("-PotentialEnergy.png", Output) << "\"\n"
	              << "set size " << size << "\n"
	              << "set pointsize " << pointsize << "\n"
	              << "replot\n"
	              << "set output\n"
	              << "reset\n"
	              << "\n"
	// Total energy
	              << "set terminal " << gui_terminal << "\n"
	              << "set title \"Energy\"\n"
	              << "set xlabel \"Time\"\n"
	              << "set ylabel \"Energy\"\n"
	              << "plot \"" << GetFileName("-TotalEnergy.data", Output) << "\" using 1:2 title \"Total\", \\\n"
	              << "     \"" << GetFileName("-KineticEnergy.data", Output) << "\" using 1:2 title \"Kinetic\", \\\n"
	              << "     \"" << GetFileName("-PotentialEnergy.data", Output) << "\" using 1:2 title \"Potential\"\n"
	              << "set terminal png\n"
	              << "set output \"" << GetFileName("-Energy.png", Output) << "\"\n"
	              << "set size " << size << "\n"
	              << "set pointsize " << pointsize << "\n"
	              << "replot\n"
	              << "set output\n"
	              << "reset\n"
	              << "\n"
	// All done!
	              << std::endl;
	
	n = 1;
	Draw(light);
	while( (LastTime / 1000000) < FinalTime)
	{
		light = true;
		Simulate();
		if( LastTime >= (n * snap_step * 1000000) )
		{
			light = false;
			n++;
		}
		Draw(light);
			
	}
	
	return result;
}

std::string NullMain::GetFileName(std::string Extension, std::string FileName)
{
	if(FileName == "")
	{
		FileName = Output;
	}
	
	std::string  result    = "/dev/null";
	unsigned int erase_loc;
	
	erase_loc = FileName.find_last_of(".");
	if(erase_loc != std::string::npos)
	{
		FileName.erase(erase_loc);
	}
	result = (FileName + Extension);
	
	return result;
}
