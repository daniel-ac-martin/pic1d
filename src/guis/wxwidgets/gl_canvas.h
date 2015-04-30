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

#ifndef GUIS_WXWIDGETS_GL_CANVAS_H
#define GUIS_WXWIDGETS_GL_CANVAS_H

class GLCanvas;

#include "config.h"

#define DEBUG
#define MESA_DEBUG

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/glcanvas.h>
#include <wx/gdicmn.h>

#include "gl_interface.h"

static int gl_canvas_default_attributes[] =
{
	WX_GL_RGBA,
	WX_GL_LEVEL,	0,
	WX_GL_DOUBLEBUFFER,// Use doublebuffer
	//WX_GL_STEREO,// Use stereoscopic display
	//WX_GL_AUX_BUFFERS,// Number of auxiliary buffers (not all implementation support this option)
	//WX_GL_MIN_RED,// Use red buffer with most bits (> MIN_RED bits)
	//WX_GL_MIN_GREEN,// Use green buffer with most bits (> MIN_GREEN bits)
	//WX_GL_MIN_BLUE,// Use blue buffer with most bits (> MIN_BLUE bits)
	//WX_GL_MIN_ALPHA,// Use alpha buffer with most bits (> MIN_ALPHA bits)
	//WX_GL_DEPTH_SIZE, 16,// Bits for Z-buffer (0,16,32)
	//WX_GL_STENCIL_SIZE, 16,// Bits for stencil buffer
	//WX_GL_MIN_ACCUM_RED,// Use red accum buffer with most bits (> MIN_ACCUM_RED bits)
	//WX_GL_MIN_ACCUM_GREEN,// Use green buffer with most bits (> MIN_ACCUM_GREEN bits)
	//WX_GL_MIN_ACCUM_BLUE,// Use blue buffer with most bits (> MIN_ACCUM_BLUE bits)
	//WX_GL_MIN_ACCUM_ALPHA,// Use blue buffer with most bits (> MIN_ACCUM_ALPHA bits)
	0
};

class GLCanvas:
	public wxGLCanvas  
{
	public:
		GLCanvas(arguments Args,
                     wxWindow* parent,
		         wxWindowID id = -1,
		         const wxPoint& pos = wxDefaultPosition,
		         const wxSize& size = wxDefaultSize,
		         long style=0,
		         const wxString& name = _("GLCanvas"),
		         int* attributes = gl_canvas_default_attributes,
		         const wxPalette& palette = wxNullPalette);
		virtual ~GLCanvas();
		
		GLInterface* Physics;
		struct MyColor
		{
			float R;
			float G;
			float B;
		} OColor, BColor;
		struct Cartesian
		{
			float x;
			float y;
			float z;
		} Location, Orientation;
		
		// Methods
		void InitGL();
		void Draw();
		void Paint(wxDC &dc);
		// Event Handlers (These Functions Should NOT be Virtual)
		void OnPaint(wxPaintEvent& event);
		void OnLeftMouse(wxMouseEvent& event);
		void OnLeftMouseUp(wxMouseEvent& event);
		void OnRightMouse(wxMouseEvent& event);
		void OnRightMouseUp(wxMouseEvent& event);
		void OnMouseMove(wxMouseEvent& event);
		void OnSize(wxSizeEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		void OnIdle(wxIdleEvent& event);
	protected:
		long Xcoord, Ycoord, Zcoord, Dummy, X, Y;
		int MouseButton;
	private:
		//DECLARE_CLASS(wxGLViewCanvas)
		// any class wishing to process wxWindows events must use this macro
		DECLARE_EVENT_TABLE()
};

#endif
