/* tinit.c -- tests the cargs_init() function

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
#include <assert.h>


int main(int argc, char **argv)
{
    cargs_init(PACKAGE ".check_printinfo", VERSION, argc, argv);

    cargs_add_author("Cade Brown", "brownce@ornl.gov");

    cargs_add_arg("-a", "--about", 1, CARGS_ARG_TYPE_STR, "about string");
    cargs_add_default("-a", "testing program");

    cargs_add_arg("-p", "--product", CARGS_NUM_ANY, CARGS_ARG_TYPE_INT, "to prod");

    cargs_add_arg(CARGS_NOSPEC, "", CARGS_NUM_ANY, CARGS_ARG_TYPE_INT, "to sum");


    cargs_parse();

    if (cargs_get_flag("")) {
        size_t i;
        int sum = 0, tt;
        printf("sum(");
        for (i = 0; i < cargs_get_len(""); ++i) {
            tt = atoi(cargs_get_idx("", i));
            sum += tt;
            printf("%d,", tt);
        }
        printf(")=%d\n", sum);
    }
    
    if (cargs_get_flag("-p")) {
        size_t i;
        int prod = 1, tt;
        printf("prod(");
        for (i = 0; i < cargs_get_len("-p"); ++i) {
            tt = atoi(cargs_get_idx("-p", i));
            prod *= tt;
            printf("%d,", tt);
        }
        printf(")=%d\n", prod);
    }
    

    printf("%s\n", cargs_get("-a"));

    return 0;

}

