#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(PIC1D, 0.8, pic1d@dacm.org)
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
#AC_CANONICAL_TARGET
AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE([-Wall])
AM_OPTIONS_WXCONFIG

if test -n "${CXXFLAGS}"; then
	user_set_cxxflags=yes
fi
if test -n "${CFLAGS}"; then
	user_set_cflags=yes
fi

# Checks for programs.
AC_PROG_CC
gl_EARLY
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_CPP
if test X$user_set_cxxflags != Xyes; then
	CXXFLAGS="-g"
fi
if test X$user_set_cflags != Xyes; then
	CFLAGS="-g"
fi
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_C_CONST #
AC_EXEEXT #
AC_LIBTOOL_DLOPEN #
AM_PROG_AR
AM_PROG_LIBTOOL #
AC_SUBST(LIBTOOL_DEPS) #
AM_MISSING_PROG(HELP2MAN, help2man)

# Checks for libraries.
AC_PATH_XTRA #
AC_CHECK_HEADERS([GL/gl.h])
AC_CHECK_LIB([GL], [glTranslated], [],
[
	AC_CHECK_LIB([opengl32], [glTranslated], [],
	[
		LDFLAGS="$LDFLAGS -lopengl32"
	])
])
AC_CHECK_HEADERS([GL/glu.h])
AC_CHECK_LIB([GLU], [gluPerspective], [],
[
	AC_CHECK_LIB([glu32], [gluPerspective], [],
	[
		LDFLAGS="$LDFLAGS -lglu32"
	])
])
AC_ARG_WITH([glut], [  --with-glut=PATH        Use the GLUT library in PATH\n  --without-glut          Do not use GLUT], [], [with_glut="yes"])
if test "$with_glut" != "no"
then
	AC_CHECK_HEADERS([GL/freeglut.h])
	AC_CHECK_LIB([freeglut], [glutSolidTeapot], [],
	[
		AC_CHECK_HEADERS([GL/openglut.h])
		AC_CHECK_LIB([openglut], [glutSolidTeapot], [],
		[
			AC_CHECK_HEADERS([GL/glut.h])
			AC_CHECK_LIB([glut], [glutSolidTeapot], [],
			[
				AC_CHECK_LIB([glut32], [glutSolidTeapot], [], [])
			])
		])
	])
fi
AC_ARG_WITH([wxwidgets], [  --without-wxwidgets    Do not build the wxWidgets interface], [], [with_wxwidgets="yes"])
if test "$with_wxwidgets" != "no"
then
	AM_OPTIONS_WXCONFIG
	AM_PATH_WXCONFIG([2.6.1], [WXFOUND=1], , [base,net,core,adv,gl] )
	if test "$WXFOUND" != 1; then
		AC_MSG_ERROR([
			Please check that wx-config is in path, the directory
			where wxWidgets libraries are installed (returned by
			'wx-config --libs' command) is in LD_LIBRARY_PATH or
			equivalent variable and wxWidgets is version 2.6.1 or above.
			Or this might also be a bug in our configure. Please try again
			with --with-wx-config=/usr/bin/wx-config
			(replace /usr/bin/wx-config with a valid path to your wx-config)
			* Note:
			Most probably, either one of the above aren't correct, you don't 
			have wxGTK installed, or are missing wxGTK-devel (or equivalent) package.
		])
	fi
fi

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_CHECK_FUNCS([sqrt strdup])

# Custom stuff
## Stripped binaries.
AC_ARG_WITH([symbols], [  --without-symbols       Strip binaries of their symbols], [], [with_symbols="yes"])
if test "$with_symbols" != "yes"
then
	LDFLAGS="$LDFLAGS -s"
fi
## Static Build
AC_ARG_ENABLE([static-build], [  --enable-static-build   Build the package statically], [LDFLAGS="$LDFLAGS -static"; CFLAGS="$CFLAGS -static"; CXXFLAGS="$CXXFLAGS -static";])

# Sorts out GNUlib.
gl_SOURCE_BASE([gnulib/src])
gl_M4_BASE([gnulib/m4])
gl_LIB([libgnu])
#gl_ARGP
#gl_XSIZE
#gl_MODULES([argp malloc memcmp realloc])
gl_MODULES([argp malloc])
#gl_MODULES([argp])
gl_INIT

AC_CONFIG_FILES([Makefile
                 gnulib/Makefile
                 gnulib/src/Makefile
                 src/Makefile
                 src/guis/Makefile
                 src/guis/gnuplot/Makefile
                 src/guis/null/Makefile
                 src/guis/wxwidgets/Makefile
                 src/guis/wxwidgets/images/Makefile
                 doc/Makefile])
AC_OUTPUT

echo
echo $PACKAGE $VERSION
echo
echo configure complete, now type \'make\'
echo
