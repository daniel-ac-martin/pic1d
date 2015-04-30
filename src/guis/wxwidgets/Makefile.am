noinst_LTLIBRARIES = libwxwidgetsgui.la

libwxwidgetsgui_la_CPPFLAGS = $(CPPFLAGS) -I$(top_srcdir)/gnulib/src -I$(top_builddir)/gnulib/src
libwxwidgetsgui_la_CXXFLAGS = $(CXXFLAGS) $(WX_CXXFLAGS) -ggdb3 -Wall
libwxwidgetsgui_la_CFLAGS   = $(CFLAGS) $(WX_CFLAGS) -ggdb3 -Wall
libwxwidgetsgui_la_LDFLAGS  = $(LDFLAGS) $(LTLIBINTL) $(WX_LIBS)
#libwxwidgetsgui_la_LDFLAGS  = $(WX_LIBS_STATIC) # FIXME: This should only be static for windows.
#libwxwidgetsgui_la_LDADD   = $(LIB_GLUT) $(LIB_GLU) $(LIB_GL)
#libwxwidgetsgui_la_LDADD   = -lglut -lGLU -lGL
#libwxwidgetsgui_la_LDADD   = -lglut -lglu32 -lopengl32

libwxwidgetsgui_la_SOURCES =          gl_canvas.cpp gl_interface.cpp       main.cpp main_frame.cpp
EXTRA_DIST                 = config.h gl_canvas.h   gl_interface.h   gui.h main.h   main_frame.h

SUBDIRS = images
