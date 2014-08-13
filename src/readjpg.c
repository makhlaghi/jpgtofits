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
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <assert.h>
#include <jpeglib.h>

#include "main.h"
#include "readjpg.h"		/* Needs main.h */

/* Read the example.c in libjpeg's source code to understand the
   details of what I am doing here.  */

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}





void
makejsample(JSAMPLE **a, struct mainparams *p)
{
  size_t size;
  JSAMPLE *jsarr;

  if(sizeof *jsarr!=1)
    {
      printf("\n\nJSAMPLE has to be unsigned char!\n\n");
      exit(EXIT_FAILURE);
    }

  size=p->s0*p->s1*p->numcolors;

  assert( (jsarr=malloc(size*sizeof *jsarr))!=NULL );

  *a=jsarr;
}





void
readjpg(struct mainparams *p)
{
  FILE * infile;
  JSAMPROW jrow;
  JSAMPLE *jsamp;
  int rowstride, c;
  JSAMPARRAY jsarr;
  unsigned char **all;
  size_t i, j, size, nc;
  struct my_error_mgr jerr;
  struct jpeg_decompress_struct cinfo;

  /* Open the input file */
  if ((infile = fopen(p->inname, "rb")) == NULL) 
    {
      fprintf(stderr, "\n\nError: Can't open %s\n", p->inname);
      exit(EXIT_FAILURE);
    }
  
  /* Set up the error and decompressing (reading) functions. */
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  if (setjmp(jerr.setjmp_buffer)) 
    {
      printf("\n\nError in JPEG code.\n\n");
      jpeg_destroy_decompress(&cinfo);
      fclose(infile);
      exit(EXIT_FAILURE);
    }
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);

  /* Read the JPEG header information and start de-compressing: */
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);

  /* Get the array width and height and number of color channels: */
  p->s0=cinfo.output_height;
  p->s1=cinfo.output_width;
  nc=p->numcolors=cinfo.output_components;
  rowstride=p->s1*p->numcolors;
  makejsample(&jsamp, p);
  size=p->s0*p->s1;
  
  /* Allocate all the arrays for each color: */
  assert( (all=p->a=malloc(p->numcolors*sizeof *p->a))!=NULL );
  for(i=0;i<p->numcolors;++i)
    assert( (p->a[i]=malloc(p->s0*p->s1*sizeof *p->a[i]))!=NULL );
  
  /* Read the image line by line: */
  if(p->flip)
    {
      c=p->s0-1;
      while (cinfo.output_scanline < cinfo.output_height) 
	{
	  jrow=&jsamp[c-- * rowstride];
	  jsarr=&jrow;
	  jpeg_read_scanlines(&cinfo, jsarr, 1);
	}
    }
  else
    while (cinfo.output_scanline < cinfo.output_height) 
      {
	jrow=&jsamp[cinfo.output_scanline * rowstride];
	jsarr=&jrow;
	jpeg_read_scanlines(&cinfo, jsarr, 1);
      }

  /* Put the different colors into the different arrays */
  for(i=0;i<size;++i)
    for(j=0;j<nc;++j)
      all[j][i]=jsamp[i*nc+j];

  /* Finish decompression, destroy it and close file: */
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);
  free(jsamp);
}
