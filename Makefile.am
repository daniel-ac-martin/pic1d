ACLOCAL_AMFLAGS = -I m4 -I gnulib/m4

AM_CPPFLAGS = $(CPPFLAGS) -I$(top_srcdir)/gnulib/src -I$(top_builddir)/gnulib/src
AM_CXXFLAGS = $(CXXFLAGS)-Wall -ggdb3
AM_CFLAGS = $(CFLAGS) -Wall -ggdb3

LIBADD = gnulib/src/libgnu.la

EXTRA_DIST = autogen.sh INSTALL-win.txt

BUILT_SOURCES = config.h.temp
CLEANFILES = config.h.temp

config.h.temp: config.h
	cp config.h config.h.temp

SUBDIRS = gnulib src doc
