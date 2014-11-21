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
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"
#include "config.h"
#include "argpparser.h"

#include "ui.h"			/* Needs main.h */





/****************************************************************
 *****************       Small functions       ******************
 ****************************************************************/
/* Check if the output image exists. If so, remove it. */
void
checkremoveoutimage(char *outname)
{
  FILE *tmpfile;
  if ((tmpfile = fopen(outname, "r")) != NULL) 
    {
      fclose(tmpfile);
      if(unlink(outname)==-1)
	{
	  fprintf(stderr, PACKAGE": '%s' already exists and could "
		  "not be removed.", outname);
	  exit(EXIT_FAILURE);
	}
    }
}





/* Check if input image exists. */
void
checkinimage(char *inname)
{
  FILE *tmpfile;

  if ((tmpfile = fopen(inname, "r")) != NULL) 
    fclose(tmpfile);
  else
    {
      fprintf(stderr, PACKAGE": %s could not be opened.\n", inname);
      exit(EXIT_FAILURE);
    }
}





void
findnamebase(char *inname, char **out, int removenamedir)
{
  char *base;
  size_t i, l, offset=0;

  l=strlen(inname);
  /* The 50 is added in case all extentions are requested,
     in which case a number will be added to the name and we 
     need this extra space!*/ 
  assert( (*out=base=malloc((l+50)*sizeof *base))!=NULL );
  strcpy(base, inname);
  for(i=l;i!=0;--i)
    if(base[i]=='.')
      {
	base[i]='\0';
	break;
      }
  if(i==0)
    {
      printf("\n\n\tError: %s does not have a '.'\n\n", inname);
      exit(EXIT_FAILURE);
    }

  /* If it is desired to remove the directory information from the
     name, do it here: */
  if(removenamedir)
    {
      l=strlen(base);
      for(i=l;i!=0;--i)	 	  /* Find the last forward slash.      */
	if(base[i]=='/')
	  {offset=i+1; break;}
      if(offset)
	for(i=offset;i<=l;++i)	  /* <= because we want to shift the   */
	  base[i-offset]=base[i]; /* '\0' character in the string too. */
    }
}



















/****************************************************************
 *****************        Read options:      ********************
 ****************************************************************/
/* Read all the options into the program */
void
setparams(struct mainparams *p, int argc, char *argv[])
{
  char *tmp;
  
  /* Set the default values: */
  p->inname        = NULL;
  p->outname       = NULL;
  p->flip          = 1;
  p->removenamedir = 1;

  /* Read the arguments: */
  argp_parse(&argp, argc, argv, 0, 0, p);

  /* First check if the input name was set. */
  checkinimage(p->inname);

  /* If outname was not set, set it here.*/
  if(p->outname==NULL)
    p->outname=p->inname;
  tmp=p->outname;		/* To see if it is changed or not. */
  findnamebase(p->outname, &p->outname, p->removenamedir);
  strcat(p->outname, ".fits");

  /* If outname was allocated, set this paramter to free the space in
     the end: */
  p->freeoutname = tmp==p->outname ? 0 : 1;

  /* Check if the output name exists, if so, delete it. */
  checkremoveoutimage(p->outname);
}
