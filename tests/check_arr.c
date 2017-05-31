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

#define CARGS_CA_TYPE int

void arr_test_simple() {
    cargs_arr_t ca;
    cargs_arr_init(&ca, 3, sizeof (CARGS_CA_TYPE));

    CARGS_CA_TYPE ca0 = 3, ca1 = 120, ca2 = 32;

    cargs_arr_set(&ca, 0, &ca0);
    cargs_arr_set(&ca, 1, &ca1);
    cargs_arr_set(&ca, 2, &ca2);

    assert((*(CARGS_CA_TYPE *)cargs_arr_get(&ca, 0)) == (CARGS_CA_TYPE) ca0);
    assert((*(CARGS_CA_TYPE *)cargs_arr_get(&ca, 1)) == (CARGS_CA_TYPE) ca1);
    assert((*(CARGS_CA_TYPE *)cargs_arr_get(&ca, 2)) == (CARGS_CA_TYPE) ca2);

    assert((*(CARGS_CA_TYPE *)cargs_arr_get(&ca, 0)) != (CARGS_CA_TYPE) ca1);
    assert((*(CARGS_CA_TYPE *)cargs_arr_get(&ca, 2)) != (CARGS_CA_TYPE) ca1);
    assert((*(CARGS_CA_TYPE *)cargs_arr_get(&ca, 0)) != (CARGS_CA_TYPE) ca2);

    cargs_arr_free(&ca);
}

void arr_test_rep(size_t sz) {
    CARGS_CA_TYPE * darr = (CARGS_CA_TYPE *)malloc(sizeof(CARGS_CA_TYPE) * sz);
    cargs_arr_t ca;
    cargs_arr_init(&ca, sz, sizeof (CARGS_CA_TYPE));
    size_t i;
    for (i = 0; i < sz; ++i) {
        darr[i] = 5 * i * (3 - i) + i - 10;
    }
    for (i = 0; i < sz; ++i) {
        cargs_arr_set(&ca, i, &darr[i]);
    }
    for (i = 0; i < sz; ++i) {
        assert((*(CARGS_CA_TYPE *)cargs_arr_get(&ca, i)) == darr[i]);
    }

    cargs_arr_free(&ca);
    free(darr);
}

int main(int argc, char *argv[])
{
    cargs_init(PACKAGE " check_arr", VERSION, argc, argv);

    arr_test_simple();
    arr_test_rep(0);
    arr_test_rep(1);
    arr_test_rep(100);
    arr_test_rep(100000);

    return 0;

}

