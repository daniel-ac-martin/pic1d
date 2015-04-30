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

#ifndef GUIS_WXWIDGETS_MAIN_FRAME_H
#define GUIS_WXWIDGETS_MAIN_FRAME_H

#include "config.h"
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "gl_canvas.h"

class FrameMain:
	public wxFrame
{
	public:
		FrameMain(arguments Args, wxFrame *frame, const wxString& title, const wxPoint& pos, const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);
		virtual ~FrameMain();
		
		GLCanvas* Canvas;
		
		void OnQuit(wxCommandEvent& event);
		void OnPlay(wxCommandEvent& event);
		void OnPause(wxCommandEvent& event);
		void OnStop(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		
		DECLARE_EVENT_TABLE()
	protected:
		wxMenuBar* MenuBar;
		wxMenu**   Menus;
		wxPanel*   MainPanel;
		wxPanel*   CanvasPanel;
		wxPanel*   SidePanel;
};

#endif
