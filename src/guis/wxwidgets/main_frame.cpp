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

#include "main_frame.h"

#include "images/fast-forward.xpm"
#include "images/play.xpm"
#include "images/pause.xpm"
#include "images/stop.xpm"
#include "images/reverse-play.xpm"
#include "images/rewind.xpm"

int idMenuFileQuit = wxNewId();
int idMenuControlPlay = wxNewId();
int idMenuControlPause = wxNewId();
int idMenuControlStop = wxNewId();
int idMenuHelpAbout = wxNewId();
int idButtonPlay = wxNewId();
int idButtonPause = wxNewId();
int idButtonStop = wxNewId();

BEGIN_EVENT_TABLE(FrameMain, wxFrame)
	EVT_MENU(idMenuFileQuit, FrameMain::OnQuit)
	EVT_MENU(idMenuControlPlay, FrameMain::OnPlay)
	EVT_MENU(idMenuControlPause, FrameMain::OnPause)
	EVT_MENU(idMenuControlStop, FrameMain::OnStop)
	EVT_MENU(idMenuHelpAbout, FrameMain::OnAbout)
	EVT_BUTTON(idButtonPlay, FrameMain::OnPlay)
	EVT_BUTTON(idButtonPause, FrameMain::OnPause)
	EVT_BUTTON(idButtonStop, FrameMain::OnStop)
END_EVENT_TABLE()

FrameMain::FrameMain(arguments Args, wxFrame *frame, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
	wxFrame(frame, wxID_ANY, title, pos, size, style)
{
	this->Menus = new wxMenu*[3];
	this->Menus[0] = new wxMenu;
	this->Menus[0]->AppendSeparator();
	this->Menus[0]->Append(idMenuFileQuit, _("Q&uit"));
	this->Menus[1] = new wxMenu;
	this->Menus[1]->Append(idMenuControlPlay, _("Play"));
	this->Menus[1]->Append(idMenuControlPause, _("Pause"));
	this->Menus[1]->Append(idMenuControlStop, _("Stop"));
	this->Menus[2] = new wxMenu;
	this->Menus[2]->Append(idMenuHelpAbout, _("&About..."));

	this->MenuBar = new wxMenuBar;
	this->MenuBar->Append(this->Menus[0], _("&File"));
	this->MenuBar->Append(this->Menus[1], _("Control"));
	this->MenuBar->Append(this->Menus[2], _("&Help"));
	
	SetMenuBar(this->MenuBar);
	
	//CreateStatusBar();
	//SetStatusText(_("Welcome to wxWindows!"));
	
	wxBoxSizer* BaseSizer = new wxBoxSizer(wxVERTICAL);
	
	this->MainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(50, 30));
	wxBoxSizer* MainSizer = new wxBoxSizer(wxHORIZONTAL);
	
	this->CanvasPanel = new wxPanel(this->MainPanel, wxID_ANY, wxDefaultPosition, wxSize(20, 20), wxSUNKEN_BORDER);
	
	wxBoxSizer* CanvasSizer = new wxBoxSizer(wxVERTICAL);
	
	this->Canvas = new GLCanvas(Args, this->CanvasPanel, wxID_ANY, wxDefaultPosition, wxSize(300, 300), 0, _("GLCanvas"), gl_canvas_default_attributes, wxNullPalette);
	CanvasSizer->Add(this->Canvas, 1, wxEXPAND | wxALL, 0);
	
	wxBoxSizer* ControlSizer = new wxBoxSizer(wxHORIZONTAL);
	
	wxPanel* ControlPanel = new wxPanel(this->CanvasPanel, wxID_ANY, wxDefaultPosition, wxSize(20, 15), 0);
	wxBitmapButton* PlayButton = new wxBitmapButton(ControlPanel, idButtonPlay, wxBitmap(/*_("images/play.xpm")*/play_xpm), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _("Play"));
	wxBitmapButton* PauseButton = new wxBitmapButton(ControlPanel, idButtonPause, wxBitmap(/*_("images/pause.xpm")*/pause_xpm), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _("Pause"));
	wxBitmapButton* StopButton = new wxBitmapButton(ControlPanel, idButtonStop, wxBitmap(/*_("images/stop.xpm")*/stop_xpm), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _("Stop"));
	ControlSizer->Add(PlayButton, 0, 0, 0);
	ControlSizer->Add(PauseButton, 0, 0, 0);
	ControlSizer->Add(StopButton, 0, 0, 0);
	
	CanvasSizer->Add(ControlPanel, 0, wxEXPAND | wxALL, 0);
	ControlPanel->SetAutoLayout(true);
	ControlPanel->SetSizer(ControlSizer);
	ControlSizer->Fit(ControlPanel);
	ControlSizer->SetSizeHints(ControlPanel);
			
	wxBoxSizer* SideSizer = new wxBoxSizer(wxVERTICAL);
	
	this->SidePanel = new wxPanel(this->MainPanel, wxID_ANY, wxDefaultPosition, wxSize(20, 20), wxSUNKEN_BORDER);
	SideSizer->Add(new wxStaticText(this->SidePanel, wxID_ANY, _("Status:")), 0, wxEXPAND | wxALL, 0);
	
	MainSizer->Add(CanvasPanel, 1, wxEXPAND | wxALL, 1);
	CanvasPanel->SetAutoLayout(true);
	CanvasPanel->SetSizer(CanvasSizer);
	CanvasSizer->Fit(CanvasPanel);
	CanvasSizer->SetSizeHints(CanvasPanel);

	MainSizer->Add(SidePanel, 0, wxEXPAND | wxALL, 1);
	SidePanel->SetAutoLayout(true);
	SidePanel->SetSizer(SideSizer);
	SideSizer->Fit(SidePanel);
	SideSizer->SetSizeHints(SidePanel);
		
	BaseSizer->Add(this->MainPanel, 1, wxEXPAND | wxALL, 1);
	this->MainPanel->SetAutoLayout(true);
	this->MainPanel->SetSizer(MainSizer);
	MainSizer->Fit(this->MainPanel);
	MainSizer->SetSizeHints(this->MainPanel);
	
	SetAutoLayout(true);
	SetSizer(BaseSizer);
	
	BaseSizer->Fit(this);
	BaseSizer->SetSizeHints(this);
}

FrameMain::~FrameMain()
{
	delete[] this->Menus;
}

void FrameMain::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void FrameMain::OnPlay(wxCommandEvent& WXUNUSED(event))
{
	Canvas->Physics->Unpause();
}

void FrameMain::OnPause(wxCommandEvent& WXUNUSED(event))
{
	Canvas->Physics->Pause();
}

void FrameMain::OnStop(wxCommandEvent& WXUNUSED(event))
{
	Canvas->Physics->Stop();
}

void FrameMain::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(_("This is the base of my physics simulation programs."), _("About Base"), wxOK | wxICON_INFORMATION, this);
}
