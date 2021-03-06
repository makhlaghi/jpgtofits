/*********************************************************************
JPGtoFITS -- Convert a JPEG image into a FITS image.

Copyright (C) 2014 Mohammad Akhlaghi
Tohoku University Astronomical Institute, Sendai, Japan.
http://astr.tohoku.ac.jp/~akhlaghi/

JPGtoFITS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

JPGtoFITS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with JPGtoFITS. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <stdlib.h>
#include <jpeglib.h>

#include "main.h"
#include "fitsarrayvv.h"

#include "ui.h"			/* Needs main.h */
#include "readjpg.h"		/* Needs main.h */

int
main(int argc, char *argv[])
{
  size_t i;
  char extname[100];
  struct mainparams p;

  /* Read the input parameters: */
  setparams(&p, argc, argv);

  /* Read and separate the JPEG file: */
  readjpg(&p);

  /* Write the arrays to FITS: */
  for(i=0;i<p.numcolors;++i)
    {
      sprintf(extname, "Color %lu", i+1);
      array_to_fits(p.outname, NULL, extname, BYTE_IMG, p.a[i], p.s0, p.s1);
      free(p.a[i]);
    }
  free(p.a);

  /* Free all the allocated arrays: */
  if(p.freeoutname) 
    free(p.outname);

  /* Return */
  return 0;
}
