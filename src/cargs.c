/* cargs.c -- main commandline argument file

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
cargs_arr_t cargs_arg;

int cargs_argc;
char **cargs_argv;

void cargs_init(char *pkg_name, char *version, int argc, char **argv) {
    cargs_argc = argc;
    cargs_argv = (char **)malloc(sizeof(char *) * argc);
    size_t i;
    for (i = 0; i < argc; ++i) {
        cargs_argv[i] = (char *)malloc(sizeof(char) * strlen(argv[i]));
        strcpy(cargs_argv[i], argv[i]);
    }


    cargs_meta.exec_name = cargs_argv[0];

    cargs_meta.pkg_name = (char *)malloc(strlen(pkg_name));
    strcpy(cargs_meta.pkg_name, pkg_name);

    cargs_meta.version = (char *)malloc(strlen(version));
    strcpy(cargs_meta.version, version);

    cargs_meta.help_str_off = CARGS_DEFAULT_HELPSTR_OFFSET;

    cargs_arr_init(&cargs_meta.authors, 0, sizeof(cargs_author_t));


    cargs_arr_init(&cargs_arg, 0, sizeof(cargs_sarg_t));


    cargs_add_flag("--info", "", "show info");

    cargs_add_flag("-h", "--help", "show help / usage");

    cargs_add_flag("--authors", "", "show authors");
}


void cargs_handle_parse() {
    if (cargs_get_flag("--help")) {
        cargs_print_help();
        exit(0);
    }

    if (cargs_get_flag("--info")) {
        cargs_print_info();
        exit(0);
    }

    if (cargs_get_flag("--authors")) {
        cargs_print_authors();
        exit(0);
    }


}

#define NN(xx) (!(xx == NULL || strcmp(xx, "") == 0))

void cargs_print_info() {
    if (NN(cargs_meta.pkg_name)) {
        printf("%s", cargs_meta.pkg_name);
        if (NN(cargs_meta.version)) {
            printf(" v%s", cargs_meta.version);
        }
        printf("\n");
    }
}

void cargs_print_authors() {
    if (cargs_meta.authors.len > 0) {
        printf("Authors: \n");
        size_t i;
        cargs_author_t cauth;
        for (i = 0; i < cargs_meta.authors.len; ++i) {
            cauth = *(cargs_author_t *)cargs_arr_get(&cargs_meta.authors, i);
            if (NN(cauth.name) || NN(cauth.email)) {
                printf("  ");
                if (NN(cauth.name)) {
                    printf("%s ", cauth.name);
                }
                if (NN(cauth.email)) {
                    printf("<%s>", cauth.email);
                }
                printf("\n");
            }
        }
    }
}

void cargs_print_usage() {
    size_t i, j, t_len;
    char *tmpbuf;
    for (i = 0; i < cargs_arg.len; ++i) {
        t_len = 0;
        cargs_sarg_t csarg = *(cargs_sarg_t *)cargs_arr_get(&cargs_arg, i);
        cargs_arr_t cpkeyarg = csarg.keys.pkeys;
        for (j = 0; j < cpkeyarg.len; ++j) {
            tmpbuf = cargs_arr_get_str(&cpkeyarg, j);
            printf("%s", tmpbuf);
            t_len += strlen(tmpbuf);
            if (j != cpkeyarg.len - 1) {
                printf(", ");
                t_len += 2;
            }
        }
        if (csarg.vals.pvals.len != 0 || csarg.count.max == CARGS_NUM_ANY) {
            if (CARGS_ARG_HAS_SPEC(csarg)) {
                printf("=");
                t_len++;
            }
            if (csarg.count.max == CARGS_NUM_ANY) {
                printf("%c...", cargs_get_placeholder_type(csarg.vals.type));
                t_len+=4;
            } else {
                for (j = 0; j < csarg.vals.pvals.len; ++j) {
                    printf("%c", cargs_get_placeholder_type(csarg.vals.type));
                    t_len++;
                    if (j != csarg.vals.pvals.len - 1) {
                        printf(",");
                        t_len++;
                    }
                }
            }
        }
        if (NN(csarg.helpstr)) {
            for (j = t_len; j < cargs_meta.help_str_off; ++j) {
                printf(" ");
            }
            printf("%s", csarg.helpstr);
            
        }
        printf("\n");
    }
}

void cargs_print_help() {
    cargs_print_info();
    printf("\n");
    cargs_print_usage();
    printf("\n");
    cargs_print_authors();
}


void cargs_add_author(char *name, char *email) {
    cargs_author_t *curauth = (cargs_author_t *)malloc(sizeof(cargs_author_t));
    (*curauth).name = (char *)malloc(strlen(name) + 1);
    strcpy((*curauth).name, name);
    (*curauth).email = (char *)malloc(strlen(email) + 1);
    strcpy((*curauth).email, email);

    cargs_arr_append(&cargs_meta.authors, curauth);
}


char cargs_get_placeholder_type(unsigned int type) {
    if (type == CARGS_ARG_TYPE_STR) {
        return 'S';
    } else if (type == CARGS_ARG_TYPE_CHAR) {
        return 'c';
    } else if (type == CARGS_ARG_TYPE_INT) {
        return 'N';
    } else if (type == CARGS_ARG_TYPE_FLOAT) {
        return 'F';
    } else if (type == CARGS_ARG_TYPE_ERROR) {
        printf("cargs (cargs_get_placeholder_type): type is `error`\n");
        CARGS_FAIL
    } else if (type == CARGS_ARG_TYPE_FLAG) {
        return ' ';
    } else if (type == CARGS_ARG_TYPE_DEFAULT) {
        return 'S';
    } else if (type == CARGS_ARG_TYPE_AUTO) {
        return '*';
    } else {
        printf("cargs (cargs_get_placeholder_type): type not found\n");
        CARGS_FAIL
    }
}

size_t cargs_get_size_type(unsigned int type) {
    if (type == CARGS_ARG_TYPE_STR) {
        return sizeof(char *);
    } else if (type == CARGS_ARG_TYPE_CHAR) {
        return sizeof(char);
    } else if (type == CARGS_ARG_TYPE_INT) {
        return sizeof(int);
    } else if (type == CARGS_ARG_TYPE_FLOAT) {
        return sizeof(float);    
    } else if (type == CARGS_ARG_TYPE_ERROR) {
        printf("cargs (cargs_get_size_type): type is `error`\n");
        CARGS_FAIL
    } else if (type == CARGS_ARG_TYPE_FLAG) {
        return sizeof(void *);
    } else if (type == CARGS_ARG_TYPE_DEFAULT) {
        return sizeof(void *);
    } else if (type == CARGS_ARG_TYPE_AUTO) {
        return sizeof(void *);
    } else {
        printf("cargs (cargs_get_size_type): type not found\n");
        CARGS_FAIL
    }
}

void cargs_add_flag(char *pkey0, char *pkey1, char *helpstr) {
    cargs_add_arg(pkey0, pkey1, 0, CARGS_ARG_TYPE_FLAG, helpstr);
}

void cargs_add_arg_str(char *pkey0, char *pkey1, char *helpstr) {
    cargs_add_arg(pkey0, pkey1, 1, CARGS_ARG_TYPE_STR, helpstr);
}

void cargs_add_arg(char *pkey0, char *pkey1, int num, unsigned int type, char * helpstr) {
    cargs_sarg_t *csarg = (cargs_sarg_t *)malloc(sizeof(cargs_sarg_t));

    (*csarg).count.min = num;
    (*csarg).count.max = num;

    (*csarg).keys.fflag = 0;
    (*csarg).keys.is_found = false;
    (*csarg).helpstr = helpstr;

    if (NN(pkey1)) {
        cargs_arr_init_str(&(*csarg).keys.pkeys, 2);
        cargs_arr_set_str(&(*csarg).keys.pkeys, 0, pkey0);
        cargs_arr_set_str(&(*csarg).keys.pkeys, 1, pkey1);
    } else {
        cargs_arr_init_str(&(*csarg).keys.pkeys, 1);
        cargs_arr_set_str(&(*csarg).keys.pkeys, 0, pkey0);
    }
    

    (*csarg).vals.type = type;

    if (num == CARGS_NUM_ANY) {
        cargs_arr_init_str(&(*csarg).vals.pvals, 0);
    } else {
        cargs_arr_init_str(&(*csarg).vals.pvals, num);
    }

    cargs_arr_append(&cargs_arg, (void *)csarg);
}

char * cargs_get(char * pkey) {
    cargs_sarg_t *csarg = cargs_get_which_arg(pkey, false);
    if (csarg == NULL) {
        printf("cargs_get: unknown key '%s'\n", pkey);
        CARGS_FAIL
    }
    return cargs_arr_get_str(&(*csarg).vals.pvals, 0);
}


char * cargs_get_idx(char * pkey, size_t idx) {
    cargs_sarg_t *csarg = cargs_get_which_arg(pkey, false);
    if (csarg == NULL) {
        printf("cargs_get_idx: unknown key '%s'\n", pkey);
        CARGS_FAIL
    }
    if (idx >= (*csarg).vals.pvals.len) {
        printf("cargs_get_idx: idx >= pvals.len\n");
        CARGS_FAIL
    }
    return cargs_arr_get_str(&(*csarg).vals.pvals, idx);
}

int cargs_get_int(char * pkey) {
    cargs_sarg_t *csarg = cargs_get_which_arg(pkey, false);
    if (csarg == NULL) {
        printf("cargs_get_int: unknown key '%s'\n", pkey);
        CARGS_FAIL
    }
    char * resstr = cargs_arr_get_str(&(*csarg).vals.pvals, 0);
    if (!cargs_str_is_type(resstr, CARGS_ARG_TYPE_INT)) {
        printf("cargs_get_int: argument is not an integer '%s'\n", resstr);
        CARGS_FAIL
    }
    int resint = strtol(resstr, NULL, 10);
    return resint;
}

int cargs_get_int_idx(char * pkey, size_t idx) {
    cargs_sarg_t *csarg = cargs_get_which_arg(pkey, false);
    if (csarg == NULL) {
        printf("cargs_get_int_idx: unknown key '%s'\n", pkey);
        CARGS_FAIL
    }
    if (idx >= (*csarg).vals.pvals.len) {
        printf("cargs_get_int_idx: idx >= pvals.len\n");
        CARGS_FAIL
    }

    char * resstr = cargs_arr_get_str(&(*csarg).vals.pvals, idx);
    if (!cargs_str_is_type(resstr, CARGS_ARG_TYPE_INT)) {
        printf("cargs_get_int_idx: argument is not an integer '%s'\n", resstr);
        CARGS_FAIL
    }
    int resint = strtol(resstr, NULL, 10);
    return resint;
}

float cargs_get_float(char * pkey) {
    cargs_sarg_t *csarg = cargs_get_which_arg(pkey, false);
    if (csarg == NULL) {
        printf("cargs_get_float: unknown key '%s'\n", pkey);
        CARGS_FAIL
    }
    char * resstr = cargs_arr_get_str(&(*csarg).vals.pvals, 0);
    if (!cargs_str_is_type(resstr, CARGS_ARG_TYPE_FLOAT)) {
        printf("cargs_get_float: argument is not an integer '%s'\n", resstr);
        CARGS_FAIL
    }
    float resfloat = strtof(resstr, NULL);
    return resfloat;
}

float cargs_get_float_idx(char * pkey, size_t idx) {
    cargs_sarg_t *csarg = cargs_get_which_arg(pkey, false);
    if (csarg == NULL) {
        printf("cargs_get_float_idx: unknown key '%s'\n", pkey);
        CARGS_FAIL
    }
    if (idx >= (*csarg).vals.pvals.len) {
        printf("cargs_get_float_idx: idx >= pvals.len\n");
        CARGS_FAIL
    }
    char * resstr = cargs_arr_get_str(&(*csarg).vals.pvals, idx);
    if (!cargs_str_is_type(resstr, CARGS_ARG_TYPE_FLOAT)) {
        printf("cargs_get_float: argument is not an float '%s'\n", resstr);
        CARGS_FAIL
    }
    float resfloat = strtof(resstr, NULL);
    return resfloat;
}



bool cargs_get_flag(char * pkey) {
    cargs_sarg_t *csarg = cargs_get_which_arg(pkey, false);
    if (csarg == NULL) {
        printf("cargs_get_flag: unknown key '%s'\n", pkey);
        CARGS_FAIL
    }
    // uncomment this to only work with keys submitted with CARGS_ARG_TYPE_FLAG
    //if ((*csarg).vals.type != CARGS_ARG_TYPE_FLAG) {
    //    printf("cargs_get_flag: argument '%s' is not a flag", pkey);
    //    CARGS_FAIL
    //}
    return (*csarg).keys.is_found;
}

size_t cargs_get_len(char * pkey) {
    cargs_sarg_t *csarg = cargs_get_which_arg(pkey, false);
    if (csarg == NULL) {
        printf("cargs_get_len: unknown key '%s'\n", pkey);
        CARGS_FAIL
    }
    return (*csarg).vals.pvals.len;
}




