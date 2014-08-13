/*********************************************************************
jpgtofits - Convert a JPEG image to a FITS image.

Copyright (C) 2014 Mohammad Akhlaghi
Tohoku University Astronomical Institute, Sendai, Japan.
http://astr.tohoku.ac.jp/~akhlaghi/

jpgtofits is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

jpgtofits is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with jpgtofits. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/
#ifndef MAIN_H
#define MAIN_H

#define JPGTOFITSVERSION "v0.1"

struct mainparams
{
  char       *inname;		/* Input JPEG name.                  */
  char      *outname;		/* Output FITS name.                 */
  int           flip;		/* ==1: Flip the image horizontally. */
  int    freeoutname;		/* ==1: output name was allocated.   */
  size_t   numcolors;		/* Number of color channels.         */
  size_t          s0;		/* Height of image.                  */
  size_t          s1;		/* Width of image.                   */
  unsigned char  **a;		/* Array to keep JPEG image.         */
};

void
readjpeg(struct mainparams *p);

#endif
