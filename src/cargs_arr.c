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
    (*arr).data = (void *)malloc(len * sizeeach);
}

void cargs_arr_free(cargs_arr_t *arr) {
    (*arr).len = 0;
    (*arr).sizeeach = 0;
    free((*arr).data);
    (*arr).data = NULL;
}


/*

TODO:


Check realloc v malloc


*/

void cargs_arr_resize(cargs_arr_t *arr, size_t len) {
    (*arr).len = len;
    char * tmpdata = (*arr).data;
    (*arr).data = (void *)realloc(NULL, len * (*arr).sizeeach);
    size_t i;
    for (i = 0; i < strlen(tmpdata); ++i) {
        ((char *)(*arr).data)[i] = tmpdata[i];
    }
    
}

void cargs_arr_ensure_len(cargs_arr_t *arr, size_t len) {
    if ((*arr).len < len) {
        cargs_arr_resize(arr, len);
    }
}

void * cargs_arr_get(cargs_arr_t *arr, size_t i) {
    if (i >= (*arr).len) {
        printf(PACKAGE ": error in cargs_arr_get, index >= len\n");
        CARGS_FAIL
    }
    return (void *)((char *)(*arr).data + i * (*arr).sizeeach);
}

void cargs_arr_set(cargs_arr_t *arr, size_t i, void * x) {
    if (i >= (*arr).len) {
        printf(PACKAGE ": error in cargs_arr_set, index >= len\n");
        CARGS_FAIL
    }
    size_t j;
    for (j = 0; j < (*arr).sizeeach; ++j) {
        ((char *)(*arr).data)[(*arr).sizeeach * i + j] = ((char *)x)[j];
    }
}

void cargs_arr_append(cargs_arr_t *arr, void * x) {
    cargs_arr_resize(arr, (*arr).len + 1);
    cargs_arr_set(arr, (*arr).len - 1, x);
}



// int specific methods

void cargs_arr_init_int(cargs_arr_t *arr, size_t len) {
    cargs_arr_init(arr, len, sizeof(int));
}

int cargs_arr_get_int(cargs_arr_t *arr, size_t i) {
    return *(int *)cargs_arr_get(arr, i);
}

void cargs_arr_set_int(cargs_arr_t *arr, size_t i, int x) {
    int * toint = (int *)malloc(sizeof(int));
    (*toint) = x;
    cargs_arr_set(arr, i, toint);
}

void cargs_arr_append_int(cargs_arr_t *arr, int x) {
    int * toint = (int *)malloc(sizeof(int));
    (*toint) = x;
    cargs_arr_append(arr, toint);
}



// string method

void cargs_arr_init_str(cargs_arr_t *arr, size_t len) {
    (*arr).len = len;
    (*arr).sizeeach = sizeof(char *);
    (*arr).data = (void *)(char **)malloc(len * sizeof(char *));


}

void cargs_arr_free_str(cargs_arr_t *arr) {
    size_t i;
    for (i = 0; i < (*arr).len; ++i) {
        free(cargs_arr_get_str(arr, i));
    }

    (*arr).len = 0;
    (*arr).sizeeach = 0;

    free((*arr).data);
    (*arr).data = NULL;
}

void cargs_arr_set_str(cargs_arr_t *arr, size_t i, char *x) {
    if (i >= (*arr).len) {

        printf(PACKAGE ": error in cargs_arr_set_str, index >= len\n");
        CARGS_FAIL
    }
    ((char **)(*arr).data)[i] = x;
}

char * cargs_arr_get_str(cargs_arr_t *arr, size_t i) {
    return ((char **)(*arr).data)[i];
}


void cargs_arr_append_str(cargs_arr_t *arr, char *x) {
    cargs_arr_resize(arr, (*arr).len + 1);
    cargs_arr_set_str(arr, (*arr).len - 1, x);
}


