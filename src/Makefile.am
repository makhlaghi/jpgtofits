## Process this file with automake to produce Makefile.in
##
## Hand written file: used as input into Autotools.
##
## NOTE:
## This file will be called by the Makefile.am in the top directory,
## so this file does not need to be called directly by automake to
## make the full JPGtoFITS package.
##
## This is the automake instructions to build JPGtoFITS.  JPGtoFITS
## will convert a JPEG image into a FITS image, each color channel as
## one extension. It is free software released under GNU GPLv3+.
##
## Copyright (C) 2014 Mohammad Akhlaghi
## Tohoku University Astronomical Institute, Sendai, Japan.
## http://astr.tohoku.ac.jp/~akhlaghi/

AM_CFLAGS = -Wall -O3
##AM_CFLAGS = -Wall -g -O0
AM_LDFLAGS = -lcfitsio -ljpeg -lm

bin_PROGRAMS = jpgtofits
jpgtofits_SOURCES = main.c main.h ui.c ui.h fitsarrayvv.c	\
fitsarrayvv.h readjpg.c readjpg.h argpparser.h

## Necessary commands for `make check`:
TESTS = simple.sh anothername.sh
CLEANFILES = autumnintohoku.fits anothername.fits
