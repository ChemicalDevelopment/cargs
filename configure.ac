###  configure.ac -- Autoconf configuration script
#  
#    Copyright 2016-2017 ChemicalDevelopment
#  
#    This file is part of the cargs project
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


AC_PREREQ([2.55])
AC_INIT([cargs], [0.0.1], [group@chemicaldevelopment.us])
AM_INIT_AUTOMAKE([dist-lzip dist-bzip2 dist-xz dist-zip])

AC_CONFIG_SRCDIR([src/cargs.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB


# Checks for header files.
AC_CHECK_HEADERS([stdlib.h stdio.h stdbool.h string.h math.h])

# Checks for libraries.

AC_CHECK_LIB(m, log)


AC_ARG_ENABLE([static], AS_HELP_STRING([--enable-static], [Enable static building]))

AS_IF([test "x$enable_static" = "xyes"], [
  LDFLAGS="-static $LDFLAGS"
], [
])

AC_DEFINE(CARGS_DEFAULT_HELPSTR_OFFSET, 40, [Default offset while printing usage information])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC


# todo, add tests
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_OUTPUT