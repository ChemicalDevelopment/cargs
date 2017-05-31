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



#include "cargs.h"

cargs_meta_t cargs_meta;

int cargs_argc;
char **cargs_argv;

void cargs_init(char *exec_name, char *version, int argc, char **argv) {
    cargs_argc = argc;
    cargs_argv = (char **)malloc(sizeof(char *) * argc);
    size_t i;
    for (i = 0; i < argc; ++i) {
        cargs_argv[i] = (char *)malloc(sizeof(char) * strlen(argv[i]));
        strcpy(cargs_argv[i], argv[i]);
    }

    cargs_meta.exec_name = (char *)malloc(strlen(exec_name));
    strcpy(cargs_meta.exec_name, exec_name);

    cargs_meta.version = (char *)malloc(strlen(version));
    strcpy(cargs_meta.version, version);

    cargs_arr_init(&cargs_meta.authors, 0, sizeof(cargs_author_t));
}

void cargs_add_author(char *name, char *email) {
    cargs_arr_resize(&cargs_meta.authors, cargs_meta.authors.len + 1);
    
}
