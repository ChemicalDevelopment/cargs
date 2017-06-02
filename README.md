# cargs

## What is cargs?

cargs is a C library for argument parsing, as a more robust alternative to getopt and other antiquated frameworks.

# Building

## Release

Download the source, and run `./configure && make && make check && make install`

## Source

You need autotools, and possibly [libcheck](https://libcheck.github.io/check/web/install.html)

Now, run `autoreconf -i && ./configure && make`


## Tutorial


For a lot of examples, see the `tests/` folder for test cases.

# Hello World example

``` c
// greet.c


#include <stdio.h>
#include "cargs.h"

int main(int argc, char **argv)
{
    // this should be the first call that is made.
    cargs_init("Your Project Name", "1.2.3", argc, argv);

    // name, email  this is used for --authors
    cargs_add_author("Cade Brown", "cade@chemicaldevelopment.us");

    // add two possible keys (the last can be NULL for no second version)
    cargs_add_arg_str("-g", "--greeting", "the greeting");
    cargs_add_default("-g", "Hello");

    // when the argument is left as "", that means you don't have to add any prefix.
    // so, if you run `./greet Mars`, the flag "" will have `Mars` in it
    cargs_add_arg_str("", NULL, "enter your name");
    cargs_add_default("", "World");


    // this parses the arguments
    cargs_parse();

    // with cargs_get, you can use the shorthand or longhand form of the argument
    printf("%s, %s!\nHow are you?\n", cargs_get("-g"), cargs_get(""));

    return 0;
}
```

Run and compile: `gcc greet.c -lcargs -o greet`

Now, run `./greet -h` to view usage info.

This will print out:

```
Your Project Name v1.2.3

--info                                  show info
-h, --help                              show help / usage
--authors                               show authors
-g=S                                    the greeting
S                                       enter your name

Authors:
  Cade Brown <cade@chemicaldevelopment.us>
```

If you run `./greet`, the greeting will come out:

```
Hello, World!
How are you?
```

You can change the name, like `./greet Cade`:

```
Hello, Cade!
How are you?
```

You can change the greeting, like `./greet Cade -g=Hey` or `./greet Cade -g Hey` (the `=` is optional):

```
Hey, Cade!
How are you?
```


