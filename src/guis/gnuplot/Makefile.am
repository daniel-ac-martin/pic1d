noinst_LTLIBRARIES = libgnuplotgui.la

libgnuplotgui_la_CPPFLAGS = $(CPPFLAGS) -I$(top_srcdir)/gnulib/src -I$(top_builddir)/gnulib/src
libgnuplotgui_la_CXXFLAGS = $(CXXFLAGS) -ggdb3 -Wall
libgnuplotgui_la_CFLAGS   = $(CFLAGS) -ggdb3 -Wall
libgnuplotgui_la_LDFLAGS  = $(LTLIBINTL)

libgnuplotgui_la_SOURCES =          gnuplot_i.cpp       main.cpp
EXTRA_DIST               = config.h gnuplot_i.h   gui.h main.h
