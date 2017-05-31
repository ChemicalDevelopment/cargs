/* cargs.h -- header for cargs library

    Copyright 2016-2017 ChemicalDevelopment

    This file is part of the cargs project.

    cargs source code, as well as any other resources in this project are 
free software; you are free to redistribute it and/or modify them under 
the terms of the GNU General Public License; either version 3 of the 
license, or any later version.

    These programs are hopefully useful and reliable, but it is understood 
that these are provided WITHOUT ANY WARRANTY, or MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GPLv3 or email at 
<info@chemicaldevelopment.us> for more info on this.

    Here is a copy of the GPL v3, which this software is licensed under. You 
can also find a copy at http://www.gnu.org/licenses/.

*/



#ifndef __CARGS_H__
#define __CARGS_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "cargs_arr.h"

#define CARGS_FAIL exit(33);


typedef struct cargs_author_t {
    char * name;
    char * email;

} cargs_author_t;


typedef struct cargs_meta_t {
    char * exec_name;
    char * version;

    cargs_arr_t authors;

} cargs_meta_t;


int cargs_argc;
char **cargs_argv;

cargs_meta_t cargs_meta;


void cargs_init(char *exec_name, char *version, int argc, char **argv);

void cargs_add_author(char *name, char *email);


#endif
