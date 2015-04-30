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

#ifndef GUIS_WXWIDGETS_MAIN_H
#define GUIS_WXWIDGETS_MAIN_H

#include "config.h"
#include "gui.h"
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

//#include <wx/strconv.h>

/*
#define IMPLEMENT_GUI(x) \
{
	#define main wx_main
	IMPLEMENT_APP(x)
	#undef main
}
*/

#include "main_frame.h"

arguments OurArgs;

class wxMain:
	public wxApp
{
	public:
		virtual bool OnInit();
	protected:
		FrameMain*  Frame;
};

DECLARE_APP(wxMain)

#endif
