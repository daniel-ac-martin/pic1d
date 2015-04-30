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

#include "gl_draw.h"
#if HAVE_GL_GL_H
#	include <GL/gl.h>
#endif
#if   HAVE_GL_GLUT_H
#	include <GL/glut.h>
#elif HAVE_GL_OPENGLUT_H
#	include <GL/openglut.h>
#elif HAVE_GL_FREEGLUT_H
#	include <GL/freeglut.h>
#endif
#include <cmath>

void GLDraw::GLDrawCommon()
{
	//
	// Set initial parameters here.
	//
//	playing        = false;
}

GLDraw::GLDraw(arguments Args):
	Simulation(Args)
{
	GLDrawCommon();
}

GLDraw::~GLDraw()
{
}

int GLDraw::Draw()
{
	int result = 0;
	int i      = 0;
	double r; // Sphere radius.
	double scaling; // Scaling factor.
	double x_scaling = 10 / (GridFinish - GridStart);
	
	//
	// Define our colours.
	//
	double negative_colour[4] =
	{
		0,
		0,
		1,
		0
	};
	double neutral_colour[4] =
	{
		0,
		1,
		0,
		0
	};
	double positive_colour[4] =
	{
		1,
		0,
		0,
		0
	};
	double charge_density_colour[4] =
	{
		1,
		1,
		0,
		0
	};
	double electric_field_colour[4] =
	{
		0,
		1,
		1,
		0
	};
	
	//
	// Draw our current scene. Take into account new positions of objects.
	//
	
	//
	// Draw particles.
	//
	///*
#ifdef HAVE_GLUT
	i = 0;
	while(i < Particles.Elements)
	{
		// Assign colour according to charge.
		if(Particles[i].q < 0)
		{
			// Negative
			glColor4d(negative_colour[0], negative_colour[1], negative_colour[2], negative_colour[3]);
		}
		else if(Particles[i].q == 0)
		{
			// Neutral
			glColor4d(neutral_colour[0], neutral_colour[1], neutral_colour[2], neutral_colour[3]);
		}
		else if(Particles[i].q > 0)
		{
			// Positive
			glColor4d(positive_colour[0], positive_colour[1], positive_colour[2], positive_colour[3]);
		}
		
		// Assign size according to mass.
		//r = 1e28 * Particles[i].m;
		//r = sqrt(3 * M_PI * 1e27 * Particles[i].m / 4);
		//r = 0.1;
		r = 0.01;
		
		// Draw sphere.
		glTranslated(x_scaling * Particles[i].r, Particles[i].v, 0);
		glutSolidSphere(r, 32, 16);
		glTranslated(x_scaling * -Particles[i].r, -Particles[i].v, 0);
		//glTranslated(x_scaling * GParticles[i].r, -0.3, 0);
		//glutSolidSphere(r, 32, 16);
		//glTranslated(x_scaling * -GParticles[i].r, 0.3, 0);
		
		i++;
	}
#endif
	//*/
	
	//
	// Draw charge density.
	//
	//scaling = 1 / ( ( /*(Particles.Elements / ChargeDensity.Elements) * e **/ 1) / GridIncrement);
	scaling = 1 / ( (Particles.Elements * 1/*e*/) / (GridFinish - GridStart) );
	glBegin(GL_LINES);
	glColor4d(charge_density_colour[0], charge_density_colour[1], charge_density_colour[2], charge_density_colour[3]);
	i = 0;
	while(i < ChargeDensity.Elements)
	{
		//std::cout << ChargeDensity[i] << "\t* " << scaling << "\t= " << ChargeDensity[i] * scaling << std::endl;
		glVertex3d(x_scaling * (GridStart + i * GridIncrement), ChargeDensity[i] * scaling, 0);
		if(i != 0)
		{
			glVertex3d(x_scaling * (GridStart + i * GridIncrement), ChargeDensity[i] * scaling, 0);
		}
		i++;
	}
	glVertex3d(x_scaling * (GridStart + i * GridIncrement), ChargeDensity[0] * scaling, 0);
	glEnd();
	
	//
	// Draw electric field.
	//
	//scaling = 1e1;
	scaling *= epsilon_zero * ((2 * 6 * pi) / (GridFinish - GridStart));
	glBegin(GL_LINES);
	glColor4d(electric_field_colour[0], electric_field_colour[1], electric_field_colour[2], electric_field_colour[3]);
	i = 0;
	while(i < EField.Elements)
	{
		glVertex3d(x_scaling * (GridStart + i * GridIncrement), EField[i] * scaling, 0);
		if(i != 0)
		{
			glVertex3d(x_scaling * (GridStart + i * GridIncrement), EField[i] * scaling, 0);
		}
		i++;
	}
	glVertex3d(x_scaling * (GridStart + i * GridIncrement), EField[0] * scaling, 0);
	glEnd();
	
	return result;
}
