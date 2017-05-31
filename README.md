# cargs

## What is cargs?

cargs is a C library for argument parsing, as a more robust alternative to getopt and other antiquated frameworks.

# Building

## Release

Download the source, and run `./configure && make && make check && make install`

## Source

You need autotools, and possibly [libcheck](https://libcheck.github.io/check/web/install.html)

Now, run `autoreconf -i && ./configure && make`



