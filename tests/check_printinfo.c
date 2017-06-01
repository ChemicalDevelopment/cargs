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


    cargs_add_arg("-s", "--sum", 3, CARGS_ARG_TYPE_INT, "to sum");


    cargs_parse();

    if (cargs_get_flag("--sum")) {
        int a = strtol(cargs_get_arg_str_idx("-s", 0), NULL, 10);
        int b = strtol(cargs_get_arg_str_idx("-s", 1), NULL, 10);
        int c = strtol(cargs_get_arg_str_idx("-s", 2), NULL, 10);
        printf("sum(%d,%d,%d)=%d\n", a, b, c, a+b+c);
    }

    return 0;

}

