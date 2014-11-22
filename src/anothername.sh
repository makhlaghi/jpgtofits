#! /bin/bash
#
# Tests (examples) of using JPGtoFITS:
#
#
#
# General information:
# ====================
#
# autumnintohoku.jpg is very small image of a leaf I took in front of
# the Astronmical institute building in early autumn. It is put here
# as an example to test FITStoJPG.
#
# Since JPGtoFITS is not yet installed on the system, it is running
# from this directory, hence the `./jpgtofits`. After installation,
# run it with "jpgtofits" in any directory.
#
# After installation, see `jpgtofits --help` for a list of all the
# options.
#
#
# This test:
# -----------
#
# Convert the three color channels in autumnintohoku to the three
# extensions of a FITS image with another name.

./jpgtofits $srcdir/autumnintohoku.jpg anothername.fits
