###
# Man page.
###
dist_man_MANS = pic1d.1

MAINTAINERCLEANFILES = $(dist_man_MANS)

#pic1d.1: $(top_srcdir)/configure.ac $(top_srcdir)/src/arguments.cpp $(top_srcdir)/src/arguments.h
#	$(HELP2MAN) --output=$@ --name='A plasma simulator.' ../src/plasma$(EXEEXT)
pic1d.1: $(top_srcdir)/configure.ac $(top_srcdir)/src/arguments.cpp $(top_srcdir)/src/arguments.h
	$(HELP2MAN) --output=$@ --name='A plasma simulator.' `if [ -x ../src/plasma ]; then echo "../src/pic1d"; else echo "pic1d"; fi;`

###
# Proper documentation
###
AM_MAKEINFOFLAGS = --no-split

info_TEXINFOS   = pic1d.texi
plasma_TEXINFOS = fdl.texi

EXTRA_DIST = pic1d.dvi pic1d.pdf pic1d.ps
