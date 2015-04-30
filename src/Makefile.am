bin_PROGRAMS = pic1d

pic1d_CPPFLAGS = $(CPPFLAGS) -I$(top_srcdir)/gnulib/src -I$(top_builddir)/gnulib/src
pic1d_CXXFLAGS = $(CXXFLAGS) -ggdb3 -Wall
pic1d_CFLAGS   = $(CFLAGS) -ggdb3 -Wall
pic1d_LDADD    = guis/libguis.la ../gnulib/src/libgnu.la $(LTLIBINTL)

pic1d_SOURCES  = arguments.cpp complex.cpp          fourier.cpp gl_draw.cpp interface.cpp imaginary.cpp main.cpp ode_solver.cpp simulation.cpp
EXTRA_DIST     = arguments.h   complex.h   config.h fourier.h   gl_draw.h   interface.h   imaginary.h   main.h   ode_solver.h   simulation.h

SUBDIRS = guis
