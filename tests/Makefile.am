###  tests/Makefile.am -- Makefile for automake compiling test executables
#  
#    Copyright 2016-2017 ChemicalDevelopment
#  
#    This file is part of the STEMprime project
#  
#    cargs source code, as well as any other resources in this project are 
#  free software; you are free to redistribute it and/or modify them under 
#  the terms of the GNU General Public License; either version 3 of the 
#  license, or any later version.
#  
#    These programs are hopefully useful and reliable, but it is understood 
#  that these are provided WITHOUT ANY WARRANTY, or MERCHANTABILITY or FITNESS
#  FOR A PARTICULAR PURPOSE. See the GPLv3 or email at 
#  <info@chemicaldevelopment.us> for more info on this.
#  
#    Here is a copy of the GPL v3, which this software is licensed under. You 
#  can also find a copy at http://www.gnu.org/licenses/.
###  

TESTS = check_init check_arr check_printinfo check_argtypes check_info
check_PROGRAMS = check_init check_arr check_printinfo check_argtypes check_info

check_init_SOURCES = $(top_builddir)/src/cargs.h check_init.c 
check_init_CFLAGS = -I$(top_builddir)/src
check_init_LDADD = $(top_builddir)/src/libcargs.a

check_info_SOURCES = $(top_builddir)/src/cargs.h check_info.c 
check_info_CFLAGS = -I$(top_builddir)/src
check_info_LDADD = $(top_builddir)/src/libcargs.a

check_arr_SOURCES = $(top_builddir)/src/cargs.h check_arr.c 
check_arr_CFLAGS = -I$(top_builddir)/src
check_arr_LDADD = $(top_builddir)/src/libcargs.a

check_printinfo_SOURCES = $(top_builddir)/src/cargs.h check_printinfo.c 
check_printinfo_CFLAGS = -I$(top_builddir)/src
check_printinfo_LDADD = $(top_builddir)/src/libcargs.a

check_argtypes_SOURCES = $(top_builddir)/src/cargs.h check_argtypes.c 
check_argtypes_CFLAGS = -I$(top_builddir)/src
check_argtypes_LDADD = $(top_builddir)/src/libcargs.a



