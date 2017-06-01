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
#include "cargs_parse.h"

#define CARGS_FAIL exit(33);
#define CARGS_NUM_ANY (-1)

// author info

typedef struct cargs_author_t {
    char * name;
    char * email;

} cargs_author_t;


// meta info

typedef struct cargs_meta_t {
    char * pkg_name;

    char * exec_name;
    char * version;

    size_t help_str_off;

    cargs_arr_t authors;

} cargs_meta_t;



int cargs_argc;
char **cargs_argv;

cargs_meta_t cargs_meta;
cargs_arr_t cargs_arg;

void cargs_init(char *pkg_name, char *version, int argc, char **argv);

void cargs_handle_parse();


void cargs_print_info();

void cargs_print_authors();

void cargs_print_usage();

void cargs_print_help();


void cargs_add_author(char *name, char *email);


char cargs_get_placeholder_type(unsigned int type);

size_t cargs_get_size_type(unsigned int type);


void cargs_add_flag(char *pkey0, char *pkey1, char *helpstr);

void cargs_add_arg_sin_str(char *pkey0, char *pkey1, char *helpstr);

void cargs_add_arg(char *pkey0, char *pkey1, int num, unsigned int type, char * helpstr);


char * cargs_get_arg_str_idx(char * pkey, size_t idx);

char * cargs_get_arg_str(char * pkey);

bool cargs_get_flag(char * pkey);

#endif
