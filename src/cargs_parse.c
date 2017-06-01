/* cargs_parse.c -- parsing library for cargs

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

#define CSTR_ST(a, b) (cargs_str_starts_with(a, b))


bool cargs_str_starts_with(char *str, char *pre) {
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

cargs_sarg_t * cargs_get_which_arg(char * cmd) {
    size_t i, j;
    cargs_sarg_t *fallback_dft = NULL;
    for (i = 0; i < cargs_arg.len; ++i) {
        cargs_sarg_t *csarg = (cargs_sarg_t *)cargs_arr_get(&cargs_arg, i);
        for (j = 0; j < (*csarg).keys.pkeys.len; ++j) {
            char * cmt = cargs_arr_get_str(&(*csarg).keys.pkeys, j);
            if (strcmp(cmt, "") == 0) {
                fallback_dft = csarg;
            }
            if ((strcmp(cmd, cmt) == 0) || (CSTR_ST(cmd, cmt) && strlen(cmd) > strlen(cmt) && cmd[strlen(cmt)] == '=')) {
                return csarg;
            }
        }
    }
    return fallback_dft;
}


char * cargs_get_name_type(unsigned int type) {
    if (type == CARGS_ARG_TYPE_STR) {
        return "string";
    } else if (type == CARGS_ARG_TYPE_CHAR) {
        return "char";
    } else if (type == CARGS_ARG_TYPE_INT) {
        return "int";
    } else if (type == CARGS_ARG_TYPE_LONG) {
        return "long";
    } else if (type == CARGS_ARG_TYPE_LLONG) {
        return "long long";   
    } else if (type == CARGS_ARG_TYPE_FLOAT) {
        return "float";  
    } else if (type == CARGS_ARG_TYPE_DOUBLE) {
        return "double";   
    } else if (type == CARGS_ARG_TYPE_ERROR) {
        printf("cargs (cargs_get_size_type): type is `error`\n");
        CARGS_FAIL
        return "error";
    } else if (type == CARGS_ARG_TYPE_DEFAULT) {
        return "default";
    } else if (type == CARGS_ARG_TYPE_AUTO) {
        return "auto";
    } else {
        printf("cargs (cargs_get_size_type): type not found\n");
        CARGS_FAIL
        return "unknown";
    }
}

#define CARGS_IS_DIGIT(c) (c - '0' <= 9 && c - '0' >= 0)

bool cargs_str_is_type(char * st, unsigned int type) {
    if (type == CARGS_ARG_TYPE_STR) {
        return true;
    } else if (type == CARGS_ARG_TYPE_CHAR) {
        return strlen(st) == 1;
    } else if (type == CARGS_ARG_TYPE_INT || type == CARGS_ARG_TYPE_LONG || type == CARGS_ARG_TYPE_LLONG) {
        size_t i;
        for (i = 0; i < strlen(st); ++i) {
            if (!(CARGS_IS_DIGIT(st[i]) || st[i] == '-')) {
                return false;
            }
        }
        return true;
    } else if (type == CARGS_ARG_TYPE_FLOAT || type == CARGS_ARG_TYPE_DOUBLE) {
        size_t i;
        for (i = 0; i < strlen(st); ++i) {
            if (!(CARGS_IS_DIGIT(st[i]) || st[i] == '-' || st[i] == '.')) {
                return false;
            }
        }
        return true;
    } else if (type == CARGS_ARG_TYPE_ERROR) {
        printf("cargs (cargs_str_is_type): type is `error`\n");
        CARGS_FAIL
    } else if (type == CARGS_ARG_TYPE_DEFAULT) {
        return true;
    } else if (type == CARGS_ARG_TYPE_AUTO) {
        return true;
    } else {
        printf("cargs (cargs_str_is_type): type not found\n");
        CARGS_FAIL
    }
}
char * cargs_detect_type(char * st) {
    bool has_nondigit = false, has_point = false;
    size_t i;
    for (i = 0; i < strlen(st); ++i) {
        if (!(CARGS_IS_DIGIT(st[i]) || st[i] == '-')) {
            has_nondigit = true;
        }
        if (st[i] == '.') {
            has_point = true;
        }
    }
    if (!has_nondigit) {
        if (has_point) {
            return "float";
        } else {
            return "int";
        }
    } else if (strlen(st) == 1) {
        return "char";
    } else if (strlen(st) > 1) {
        return "string";
    } else {
        printf("cargs_detect_type: can't figure out the type for: '%s'\n", st);
        CARGS_FAIL
        return "error";
    }
}

void cargs_add_default(char *pkey, char *dft, size_t idx) {
    cargs_sarg_t *csarg = cargs_get_which_arg(pkey);
    if (idx >= (*csarg).vals.pvals.len) {
        cargs_arr_resize(&(*csarg).vals.pvals, idx+1);
    }

    cargs_arr_set_str(&(*csarg).vals.pvals, idx, dft);
}


void cargs_parse() {
    size_t i, j;
    char * cstr;

    cargs_sarg_t *csarg;
    for (i = 1; i < cargs_argc; ) {
        cstr = cargs_argv[i];

        csarg = cargs_get_which_arg(cstr);
        
        if (csarg == NULL) {
            printf("Unknown argument: '%s'\n", cstr);
            CARGS_FAIL
        }

        if ((*csarg).keys.is_found) {
            printf("Argument '%s' already specified\n", cstr);
            CARGS_FAIL
        }

        (*csarg).keys.is_found = true;
        
        if (CARGS_ARG_HAS_SPEC(*csarg)) {
            if (strchr(cstr, '=') != NULL) {
                char * argpos = strchr(cstr, '=') + 1;
                char * carg_e;
                size_t k;
                for (j = 0; j < (*csarg).count.max || (*csarg).count.max == CARGS_NUM_ANY; ++j) {
                    if (strlen(argpos) < 1) {
                        printf("Expecting more arguments at the end\n");
                        CARGS_FAIL
                    }
                    carg_e = (char *)malloc(strlen(argpos) + 1);
                    
                    for (k = 0; k < strlen(argpos) && argpos[k] != ','; ++k) {
                        carg_e[k] = argpos[k];
                    }
                    carg_e[k] = 0;
                    argpos = argpos + k + 1;
                    if (!cargs_str_is_type(carg_e, (*csarg).vals.type)) {
                        printf("Argument '%s' for '%s' is not the correct type (should be '%s', you gave '%s')\n", carg_e, cstr, cargs_get_name_type((*csarg).vals.type), cargs_detect_type(carg_e));
                        CARGS_FAIL
                    }

                    cargs_arr_set_str(&(*csarg).vals.pvals, j, carg_e);
                }
                if (strlen(argpos) >= 1) {
                    printf("Unused arguments: '%s'\n", argpos);
                    CARGS_FAIL
                }
                i++;
            } else {
                for (j = 0; j < (*csarg).count.max || (*csarg).count.max == CARGS_NUM_ANY; ++j) {
                    if (i >= cargs_argc) {
                        printf("Expecting more arguments for '%s'\n", cstr);
                        CARGS_FAIL
                    }
                    if (!cargs_str_is_type(cargs_argv[i], (*csarg).vals.type)) {
                        printf("Argument '%s' for '%s' is not the correct type (should be '%s', you gave '%s')\n", cargs_argv[i], cstr, cargs_get_name_type((*csarg).vals.type), cargs_detect_type(cargs_argv[i]));
                        CARGS_FAIL
                    }
                    cargs_arr_set_str(&(*csarg).vals.pvals, j, cargs_argv[i]);
                    i++;
                }
            }
        } else {
            for (j = 0; i < cargs_argc && (j < (*csarg).count.max || (*csarg).count.max == CARGS_NUM_ANY); ++j) {

                if (i >= cargs_argc) {
                    if ((*csarg).count.max != CARGS_NUM_ANY) {
                        printf("Expecting more arguments after '%s'\n", cstr);
                        CARGS_FAIL
                    }
                }


                if (!(csarg == cargs_get_which_arg(cargs_argv[i]))) {
                    break;
                }


                /*if (!cargs_str_is_type(cargs_argv[i], (*csarg).vals.type)) {
                    printf("Argument '%s' for '%s' is not the correct type (should be '%s', you gave '%s')\n", cargs_argv[i], cstr, cargs_get_name_type((*csarg).vals.type), cargs_detect_type(cargs_argv[i]));
                    CARGS_FAIL
                }*/
                printf("%d\n", j);
                cargs_arr_ensure_len(&(*csarg).vals.pvals, j+1);
                cargs_arr_set_str(&(*csarg).vals.pvals, j, cargs_argv[i]);

                i++;
            }
            if (i < cargs_argc && (!CARGS_ARG_HAS_SPEC(*cargs_get_which_arg(cargs_argv[i])))) {
                printf("Extra argument '%s'\n", cargs_argv[i]);
                CARGS_FAIL
            }
        }
        i++;
    }


        
    // run some cargs options handling (like -h, -i, etc)

    cargs_handle_parse();

}

