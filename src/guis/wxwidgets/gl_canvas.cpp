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

#include "gl_canvas.h"

#if HAVE_GL_GL_H
#	include <GL/gl.h>
#endif
#if HAVE_GL_GLU_H
#	include <GL/glu.h>
#endif
//#include <GL/glut.h>
//#include <GL/glx.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Event Tables and Other Macros for wxWindows
//////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
	EVT_SIZE(GLCanvas::OnSize)
	EVT_PAINT(GLCanvas::OnPaint)
	EVT_LEFT_DOWN(GLCanvas::OnLeftMouse)
	EVT_LEFT_UP(GLCanvas::OnLeftMouseUp)	
	EVT_RIGHT_DOWN(GLCanvas::OnRightMouse)
	EVT_RIGHT_UP(GLCanvas::OnRightMouseUp)	
	EVT_MOTION(GLCanvas::OnMouseMove)	
	EVT_ERASE_BACKGROUND(GLCanvas::OnEraseBackground)
	EVT_IDLE(GLCanvas::OnIdle)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GLCanvas::GLCanvas(arguments Args,
                   wxWindow* parent, 
                   wxWindowID id, 
                   const wxPoint& pos, 
                   const wxSize& size, 
                   long style, 
                   const wxString& name,
                   int* attribList, 
                   const wxPalette& palette)
: wxGLCanvas(parent, id, pos, size, style, name, attribList, palette)
{
	this->Physics = new GLInterface(this, Args);
	InitGL();

	// Set GL Viewport
	int w, h;
	GetClientSize(&w, &h);
	if (h == 0)
	{
		h = 1;
	}
	
	if(GetContext())
	{
		SetCurrent();
		glViewport(0, 0, (GLint)w, (GLint)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	
	// Insert dodgy hack here!
	//wxMessageBox(_(""), _(""), 0, this);
	Draw();
}

GLCanvas::~GLCanvas()
{
}

//////////////////////////////////////////////////////////////////////
// Method Implementations
//////////////////////////////////////////////////////////////////////
void GLCanvas::InitGL()
{
	//Orientation.x =  15.0f;
	//Orientation.y =  65.0f;
	Location.x =  0.0f;
	Location.y =  0.0f;
	Location.z = -4.0f;
	Orientation.x =  0.0f;
	Orientation.y =  0.0f;
	Orientation.z =  0.0f;
	
	BColor.R = 0;
	BColor.G = 0;
	BColor.B = 0;
	
	//GLfloat LightAmbient[]= { 0.5f, 0.0f, 0.0f, 1.0f }; 				// Ambient Light Values
	//GLfloat LightDiffuse[]= { 1.0f, 0.0f, 0.0f, 1.0f };				 // Diffuse Light Values
	//GLfloat LightPosition[]= { -50.0f, 50.0f, 0.0f, 0.0f };				 // Light Position

	glClearDepth(1.0f);                       // Depth Buffer Setup
	//glDisable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);		           // The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);                 // Enable Depth Buffer
	//glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);                 // Enables Smooth Color Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   //Really Nice perspective calculations
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	////glEnable(GL_TEXTURE_2D);
	////glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);				// Setup The Ambient Light
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	//glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);			// Position The Light
	//glEnable(GL_LIGHT0);							// Enable Light One
	//glEnable(GL_LIGHTING);
}

void GLCanvas::Draw()
{
    //this->Refresh();  //Refresh() seems to chew up more resources??! Just do a Paint instead!
    wxClientDC dc(this);
    Paint(dc);
}

void GLCanvas::Paint(wxDC &dc)
{
	if(!GetContext())
	{
		return;
	}
	
	SetCurrent();
	
	glClearColor(BColor.R, BColor.G, BColor.B, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(Location.x, Location.y, Location.z);
	glRotatef(Orientation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(Orientation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(Orientation.z, 0.0f, 0.0f, 1.0f);
	
	//
	// Start of crap.
	//
	this->Physics->Draw();
	
	//
	//Flush the GL Pipeline
	//
	glFlush();
	
	//
	// Swap Your Buffers
	//
	SwapBuffers();	
}


//////////////////////////////////////////////////////////////////////
// Event Handler Implementations
//////////////////////////////////////////////////////////////////////

void GLCanvas::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	Paint(dc);
	event.Skip();
}

void GLCanvas::OnSize(wxSizeEvent& event)
{
	// This is necessary to update the context on some platforms
	wxGLCanvas::OnSize(event);

	// Set the GL Viewport (not called by wxGLCanvas::OnSize on all Platforms)
	int w, h;
	GetClientSize(&w, &h);
	
	if (h == 0)
	{
		h = 1;
	}
	
	if(GetContext())
	{
		SetCurrent();
		glViewport(0, 0, (GLint)w, (GLint)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

void GLCanvas::OnLeftMouse(wxMouseEvent& event)
{        
        MouseButton = 1;
        event.GetPosition(&Xcoord, &Ycoord);      
}

void GLCanvas::OnRightMouse(wxMouseEvent& event)
{        
        MouseButton = 2;
        event.GetPosition(&Dummy, &Zcoord);        
}

void GLCanvas::OnLeftMouseUp(wxMouseEvent& event)
{        
        MouseButton = 0;
}

void GLCanvas::OnRightMouseUp(wxMouseEvent& event)
{        
        MouseButton = 0;
}

void GLCanvas::OnMouseMove(wxMouseEvent& event)
{
	
    if (event.Dragging() == true)
    {
        event.GetPosition(&X, &Y);
        if (MouseButton == 1)
        {
                Orientation.x += (GLfloat)(Y - Ycoord)/2;
                Orientation.y += (GLfloat)(X - Xcoord)/2;
                Xcoord = X;
                Ycoord = Y;
        }
        if (MouseButton == 2)
        {
                Location.z -= (GLfloat)(Y-Zcoord)/5;
                Zcoord = Y;
        }
        Draw(); // Causes an event to be generated to repaint the window.

    }    
}

void GLCanvas::OnEraseBackground(wxEraseEvent& event)
{
	// Do Nothing to Avoid Flashing on MSW
}

void GLCanvas::OnIdle(wxIdleEvent& event)
{
	if(this->Physics->Simulate() == 0)
	{
		this->Refresh();
		//this->Draw();
	}
}

