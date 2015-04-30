noinst_LTLIBRARIES = libnullgui.la

libnullgui_la_CPPFLAGS = $(CPPFLAGS) -I$(top_srcdir)/gnulib/src -I$(top_builddir)/gnulib/src
libnullgui_la_CXXFLAGS = $(CXXFLAGS) -ggdb3 -Wall
libnullgui_la_CFLAGS   = $(CFLAGS) -ggdb3 -Wall
libnullgui_la_LDFLAGS  = $(LTLIBINTL)

libnullgui_la_SOURCES =                main.cpp
EXTRA_DIST            = config.h gui.h main.h
