/* cargs_parse.h -- header for parsing cargs

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

#ifndef __CARGS_PARSE_H__
#define __CARGS_PARSE_H__

// literal types start with 0x01
#define CARGS_ARG_TYPE_STR             (0x0101)
#define CARGS_ARG_TYPE_CHAR            (0x0102)
#define CARGS_ARG_TYPE_INT             (0x0103)

#define CARGS_ARG_TYPE_LONG            (0x0104)
#define CARGS_ARG_TYPE_LLONG           (0x0105)

#define CARGS_ARG_TYPE_FLOAT           (0x0106)
#define CARGS_ARG_TYPE_DOUBLE          (0x0107)

// other types, and common macros

// this is usually for parsing strings, but it can (WIP)
// be changed to AUTO
#define CARGS_ARG_TYPE_ERROR           (0x0000)

// this is usually for parsing strings, but it can (WIP)
// be changed to AUTO
#define CARGS_ARG_TYPE_DEFAULT         (0x0201)

// this is detecting arguments, so that it finds what the
// string is trying to represent
#define CARGS_ARG_TYPE_AUTO            (0x0202)

// flag type. This is for 0 argument 
#define CARGS_ARG_TYPE_FLAG            (0x0203)

#define STR_STARTS(a, b) ()


// tells how to count

typedef struct cargs_argcount_t {

    size_t min;

    size_t max;

} cargs_argcount_t;


// a commandline argument result struct (key)

typedef struct cargs_argk_t {
    
    // first flag, like `tar xf`, 'x' and 'f' are fflags here 
    // should be set to 0 for no fflag (default)
    char fflag;

    bool is_found;

    // a list of string inputs.
    // Used like:
    // ./a.out pkey=0
    // ./a.out pkey 0
    // should start with `-` or `--` for most things, unless you want to look for
    // plaintext
    
    cargs_arr_t pkeys;

} cargs_argk_t;


// a commandline argument result struct (val)

typedef struct cargs_argv_t {
    // type must be in CARGS_ARG_TYPE_*. Use CARGS_ARG_TYPE_STR for default parsing,
    // or use CARGS_ARG_TYPE_AUTO
    unsigned int type;

    // array of vals
    cargs_arr_t pvals;

} cargs_argv_t;


// a single argument struct

typedef struct cargs_sarg_t {

    // help string
    char *helpstr;

    // struct to tell count (1, 2, 3, variable, etc)
    cargs_argcount_t count;

    // key 
    cargs_argk_t keys;

    // vals.len == num
    // a list of cargs_argv_t
    cargs_argv_t vals;

} cargs_sarg_t;



// actually parses the commandline

bool cargs_str_starts_with(char *str, char *pre);

bool cargs_str_is_type(char * st, unsigned int type);

cargs_sarg_t * cargs_get_which_arg(char * cmd);

char * cargs_detect_type(char * st);

void cargs_add_default(char *pkey, char *dft, size_t idx);

void cargs_parse();


#endif


