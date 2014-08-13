jpgtofits
=========

Convert a JPEG image to a FITS file (colors as FITS extensions).

Description:
------------

The [FITS image
standard](https://heasarc.gsfc.nasa.gov/docs/heasarc/fits.html) is the
standard used by astronomers to archive and use astronomical
data. This package converts images saved in the JPEG format into
FITS. 

In case the JPEG image is not greyscale (with only one color channel),
several color channels will be involved. `jpgtofits` will save the
channels (in the same order that they are saved in the JPEG file) as
successive extensions to the output FITS image.

Requirements:
------------
`jpgtofits` requires two packages to be installed on your
machine, installing them is easy and straightforward. 

- [IJG's libjpeg](http://www.ijg.org/), which should already be
  installed  on your system.
- [cfitsio](http://heasarc.nasa.gov/fitsio/fitsio.html) For
  reading and writing FITS files. I have explained [how to install
  `cfitsio` here](http://www.astr.tohoku.ac.jp/~akhlaghi/cfitsiowcslibinstall.html)


Installing and running:
------------
 
To install `jpgtofits`, after downloading or cloning it, all you have
to do is to run `make` in the downloaded directory. In order to be
able to run `jpgtofits` from anywhere on your system, run `make
install` as root after the installation finishes.

Some command line options can be given so you can customize the
output, to learn them, run `./jpgtofits -h`.  A full list of all the
options with some explanation and their default values will be shown.
Nealy all the operation of `jpgtofits` can be defined by these input
options and their arguments.  The [POSIX argument syntax
conventions](http://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html#Argument-Syntax) apply.

In short the options are:
* `-h`: View details and default values of all the options.
* `-v`: View only version and copyright information.

On/Off options:
* `-f`: Don't flip the image (flipping is necessary for the image to
        have the same orientation in a FITS viewer and a JPEG viewer). 

Options that require arguments:
* `-i`: Input JPG filename.
* `-o`: Output FITS name.

Future updates and issues:
------------
1. Add much more functionality and generality.
2. Work on a better user experience.
3. Fix any bugs I have not found yet!

Comments and suggestions:
----------------------------------------

I hope `jpgtofits` will be useful for you. If you find any problems in
this program please contact me so I can correct them. I would also be
very glad to hear any suggestions or comments you might have, thank
you.

makhlaghi@gmail.com 

akhlaghi@astr.tohoku.ac.jp

http://astr.tohoku.ac.jp/~akhlaghi/

----------------------------------------
Copyright:
----------------------------------------
Copyright (C) 2014 Mohammad Akhlaghi

Tohoku University Astronomical Institute

http://astr.tohoku.ac.jp/~akhlaghi/

`jpgtofits` is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

`jpgtofits` is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with `jpgtofits`.  If not, see <http://www.gnu.org/licenses/>.