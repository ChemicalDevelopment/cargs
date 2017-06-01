/* cargs_arr.h -- header for cargs arrays

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



#ifndef __CARGS_ARR_H__
#define __CARGS_ARR_H__

#include "cargs.h"

typedef struct cargs_arr_t {
    size_t len;
    size_t sizeeach;
    void * data;
} cargs_arr_t;

void cargs_arr_init(cargs_arr_t *arr, size_t len, size_t sizeeach);

void cargs_arr_free(cargs_arr_t *arr);

void cargs_arr_resize(cargs_arr_t *arr, size_t len);

void cargs_arr_ensure_len(cargs_arr_t *arr, size_t len);

void * cargs_arr_get(cargs_arr_t *arr, size_t i);

void cargs_arr_set(cargs_arr_t *arr, size_t i, void *x);

void cargs_arr_append(cargs_arr_t *arr, void *x);



// int specific methods

void cargs_arr_init_int(cargs_arr_t *arr, size_t len);

int cargs_arr_get_int(cargs_arr_t *arr, size_t i);

void cargs_arr_set_int(cargs_arr_t *arr, size_t i, int x);

void cargs_arr_append_int(cargs_arr_t *arr, int x);


// string specific methods

void cargs_arr_init_str(cargs_arr_t *arr, size_t len);

void cargs_arr_free_str(cargs_arr_t *arr);

char * cargs_arr_get_str(cargs_arr_t *arr, size_t i);

void cargs_arr_set_str(cargs_arr_t *arr, size_t i, char *x);

void cargs_arr_append_str(cargs_arr_t *arr, char *x);





#endif
