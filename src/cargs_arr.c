/* cargs_arr.c -- array implementation

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


#include "cargs.h"

void cargs_arr_init(cargs_arr_t *arr, size_t len, size_t sizeeach) {
    (*arr).len = len;
    (*arr).sizeeach = sizeeach;
    cargs_arr_resize(arr, len);
}

void cargs_arr_free(cargs_arr_t *arr) {
    (*arr).len = 0;
    (*arr).sizeeach = 0;
    free((*arr).data);
    (*arr).data = NULL;
}

void cargs_arr_resize(cargs_arr_t *arr, size_t len) {
    (*arr).len = len;
    (*arr).data = (void *)malloc(len * (*arr).sizeeach);
}

void * cargs_arr_get(cargs_arr_t *arr, size_t i) {
    if (i >= (*arr).len) {
        printf(PACKAGE ": error in cargs_arr_get, index >= len");
        CARGS_FAIL
    }
    return (void *)((char *)(*arr).data + i * (*arr).sizeeach);
}

void cargs_arr_set(cargs_arr_t *arr, size_t i, void * x) {
    if (i >= (*arr).len) {
        printf(PACKAGE ": error in cargs_arr_set, index >= len");
        CARGS_FAIL
    }
    size_t j;
    for (j = 0; j < (*arr).sizeeach; ++j) {
        ((char *)(*arr).data)[(*arr).sizeeach * i + j] = ((char *)x)[j];
    }
}


