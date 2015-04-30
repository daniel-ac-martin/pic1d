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

#ifdef WIN32
#	include <windows.h>
#	define sleep Sleep
#endif

#define SLEEP_LGTH 1
#define NPOINTS    50

int gnuplot_main(arguments Args)
{
    /*
    vector<double> x;
    vector<double> y;
    vector<double> z;
    int i;

    cout << "*** example of gnuplot control through C++ ***" << endl;

    Gnuplot g1 = Gnuplot("lines");
    //try {
    //    g1 = Gnuplot("lines");
    //} catch (GnuplotException ge) {
    //    cout << ge.what() << endl;
    //}

    //
    // Slopes
    // 
    cout << "*** plotting slopes" << endl;
    cout << "y = x" << endl;
    g1.plot_slope(1.0,0.0,"unity slope");
    sleep(SLEEP_LGTH);

    cout << "y = 2*x" << endl;
    g1.plot_slope(2.0,0.0,"y=2x");
    sleep(SLEEP_LGTH);

    cout << "y = -x" << endl;
    g1.plot_slope(-1.0,0.0,"y=-x");
    sleep(SLEEP_LGTH);

    //
    // Equations
    //
    g1.reset_plot();
    cout << endl << endl << "*** various equations" << endl;
    cout << "y = sin(x)" << endl;
    g1.plot_equation("sin(x)","sine");
    sleep(SLEEP_LGTH);

    cout << "y = log(x)" << endl;
    g1.plot_equation("log(x)","logarithm");
    sleep(SLEEP_LGTH);

    cout << "y = sin(x) * cos(2*x)" << endl;
    g1.plot_equation("sin(x)*cos(2*x)","sine product");
    sleep(SLEEP_LGTH);

    //
    // Styles
    //
    g1.reset_plot();
    cout << endl << endl << "*** showing styles" << endl;
    cout << "sine in points" << endl;
    g1.set_style("points");
    g1.plot_equation("sin(x)","sine");
    sleep(SLEEP_LGTH);

    cout << "sine in impulses" << endl;
    g1.set_style("impulses");
    g1.plot_equation("sin(x)","sine");
    sleep(SLEEP_LGTH);

    cout << "sine in steps" << endl;
    g1.set_style("steps");
    g1.plot_equation("sin(x)","sine");
    sleep(SLEEP_LGTH);

    //
    // User defined 1d, 2d and 3d point sets
    //
    cout << endl << endl << "*** user-defined lists of doubles" << endl;
    for (i = 0; i < NPOINTS; i++)
        x.push_back((double)i * (double)i);
    g1.reset_plot();
    g1.set_style("impulses");
    g1.plot_x(x,"user-defined doubles");
    sleep(SLEEP_LGTH);


    cout << endl << endl << "*** user-defined lists of points" << endl;
    x.clear();
    for (i = 0; i < NPOINTS; i++)
      {
        x.push_back((double)i);
        y.push_back((double)i * (double)i);
      }
    g1.reset_plot();
    g1.set_style("points");
    g1.plot_xy(x,y,"user-defined points");
    sleep(SLEEP_LGTH);


    x.clear();
    y.clear();
    for (i = 0; i < NPOINTS; i++)
      {
        x.push_back((double)i);
        y.push_back((double)i * (double)i);
	z.push_back((double)i * (double)i * (double)i);
      }
    g1.reset_plot();
    g1.set_style("points");
    g1.plot_xyz(x,y,z,"user-defined points");
    sleep(SLEEP_LGTH);


    //
    // Multiple output screens
    //
    cout << endl << endl;
    cout << "*** multiple output windows" << endl;
    g1.reset_plot();
    g1.set_style("lines");

    Gnuplot g2 = Gnuplot("lines");
    Gnuplot g3 = Gnuplot("lines");

    cout << "window 1: sin(x)" << endl;
    g1.plot_equation("sin(x)","sin(x)");
    sleep(SLEEP_LGTH);

    cout << "window 2: x*sin(x)" << endl;
    g2.plot_equation("x*sin(x)","x*sin(x)");
    sleep(SLEEP_LGTH);

    cout << "window 3: log(x)/x" << endl;
    g3.plot_equation("log(x)/x","log(x)/x");
    sleep(SLEEP_LGTH);

    //
    // Using the GnuplotException class
    //
    try {
        Gnuplot g4 = Gnuplot("lines");
        cout << "window 4: sin(x)/x" << endl;
        g4.plot_equation("sin(x)/x","sin(x)/x");
        sleep(SLEEP_LGTH);

    } catch (GnuplotException ge) {
        cout << ge.what() << endl;
    }

    cout << endl << "*** end of gnuplot example" << endl;
    */
	
	int           result = -1;
	GnuPlotMain * Main   = new GnuPlotMain(Args);
	
	result = Main->Execute();
	
	delete Main;
	return result;
}

void GnuPlotMain::GnuPlotMainCommon(arguments Args)
{
	try
	{
		g1 = new Gnuplot("lines");
	}
	catch(GnuplotException ge)
	{
		cout << ge.what() << endl;
	}
	
	playing = true;
}

GnuPlotMain::GnuPlotMain(arguments Args):
	Simulation(Args)
{
	GnuPlotMainCommon(Args);
}

GnuPlotMain::~GnuPlotMain()
{
	delete g1;
}

int GnuPlotMain::Draw(bool light)
{
    vector<double> x;
    vector<double> y;
    int            i;

    x.clear();
    y.clear();
	
	for (i = 0; i < Particles.size(); i++)
	{
		x.push_back(Particles[i].r);
		y.push_back(Particles[i].v);
	}
	
    g1->reset_plot();
    g1->set_style("points");
    g1->plot_xy(x,y,"Phase-Space");
    
    return 0;
}

int GnuPlotMain::Execute()
{
	Draw();
	
	while( (LastTime / 1000000) < FinalTime)
	{
		Simulate();
		Draw();
	}
	
	return 0;
}
