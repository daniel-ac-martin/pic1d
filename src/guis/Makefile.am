noinst_LTLIBRARIES = libguis.la

libguis_la_SOURCES = 
EXTRA_DIST         = config.h guis.h
libguis_la_LIBADD  = gnuplot/libgnuplotgui.la null/libnullgui.la wxwidgets/libwxwidgetsgui.la
libguis_la_LDFLAGS = $(LTLIBINTL)

SUBDIRS = gnuplot null wxwidgets
