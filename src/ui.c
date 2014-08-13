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
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"
#include "ui.h"





/****************************************************************
 *****************     Small functions used    ******************
 *********************      in main()      **********************
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
	  fprintf(stderr, "'%s' already exists and could", outname); 
	  fprintf(stderr, " not be removed");
	  exit(EXIT_FAILURE);
	}
    }
}





/* Check if input image exists. */
void
checkinimage(char *inname)
{
  FILE *tmpfile;

  if(strlen(inname)==0)
    {
      printf("\n\n\tError: No input name specified.\n\n");
      exit(EXIT_FAILURE);
    }

  if ((tmpfile = fopen(inname, "r")) != NULL) 
    fclose(tmpfile);
  else
    {
      printf("\n\n\tError: %s does not exist\n\n", inname);
      exit(EXIT_FAILURE);
    }
}





void
findnamebase(char *inname, char **out)
{
  size_t i, l;
  char *base;

  l=strlen(inname);
  /* The 50 is added in case all extentions are requested,
     in which case a number will be added to the name and we 
     need this extra space!*/
  assert( (base=malloc((l+50)*sizeof *base))!=NULL );
  strcpy(base, inname);
  for(i=l;i!=0;i--)
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
  *out=base;
}



















/****************************************************************
 *****************        Read options:      ********************
 ****************************************************************/
/* Check if an integer input is positive (>=0). */
void
checkint(char *optarg, int *var, int opt)
{
  long tmp;
  char *tailptr;
  tmp=strtol(optarg, &tailptr, 0);
  if(tmp<0)
    {
      printf("\n\n Error: argument to -%c ", opt); 
      printf("should be positive\n\n");
      exit(EXIT_FAILURE);
    }
  *var=tmp;  
}





void
checkintlimit(char *optarg, int *var, int opt, 
	      int llimit, int hlimit)
{
  long tmp;
  char *tailptr;
  tmp=strtol(optarg, &tailptr, 0);
  if(tmp<llimit)
    {
      printf("\n\n Error: argument to `-%c` ", opt); 
      printf("should be larger than %d\n\n", llimit);
      exit(EXIT_FAILURE);
    }
  if(tmp>hlimit)
    {
      printf("\n\n Error: argument to `-%c` ", opt); 
      printf("should be smaller than %d\n\n", hlimit);
      exit(EXIT_FAILURE);
    }
  *var=tmp;  
}





void
printversioninfo()
{
  printf("\n\njpgtofits %s\n", JPGTOFITSVERSION);
  printf("============\n");
  printf("Convert a JPEG image to a FITS image.\n");
  printf("\nCopyright (C) 2014  Mohammad Akhlaghi\n");
  printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
  printf("This is free software, and you are welcome to\n");
  printf("modify and redistribute it under the ");
  printf("GNU Public License v3 or later.\n\n\n");
}





/* Print the help menu. */
void
printhelp()
{
  printversioninfo();
  printf("####### Options that won't run 'fitstojpg'.\n");
  printf(" -h:\tPrint this command and abort.\n\n");
  printf(" -v:\tPrint only version and copyright information.\n\n\n");


  printf("####### Options with no arguments (off by default):\n");
  printf(" -f:\n\tDon't flip the image vertically. If you only convert\n"
	 "\ta JPEG image to FITS without flipping it along the horizontal\n"
	 "\tline cutting the image in half, then the image that will be\n"
	 "\tdisplayed in SAO ds9 will be up-side-down! In some cases \n"
	 "\tthis might be desired, but by default it is off. So the image\n"
	 "\tis flipped, resulting in ds9 to diplay the image in the same\n"
	 "\torientation as you see in your browser.\n");

  printf("####### Options with arguments:\n");
  printf(" -i FILENAME\n\tInput JPEG image name.\n\n");

  printf(" -o FILENAME\n\tOutput FITS image name\n");
  printf("\tdefault. When input is 'base.jpg': 'base.fits'.\n\n");


  exit(EXIT_SUCCESS);
}





/* Read all the options into the program */
void
prepareparams(struct mainparams *p, int argc, char *argv[])
{
  int c;

  if(argc==1)
    printhelp(p);

  /* Set the default values: */
  p->freeoutname=1;
  p->inname=DEFAULTNAME;
  p->flip=1;

  while( (c=getopt(argc, argv, "hvfi:o:")) != -1 )
    switch(c)
      {
      case 'h':			/* Print help. */
	printhelp(p);
      case 'v':			/* Print version. */
	printversioninfo();
	exit(EXIT_SUCCESS);

      case 'f':			/* Flip horizontally? */
	p->flip=0;
	break;

      /* Options with arguments: */
      case 'i':			/* Input JPEG image name. */
	p->inname=optarg;
	break;
      case 'o': 		/* Output FITS image name. */
	p->outname=optarg;
	p->freeoutname=0;
	break;

      case '?':
	fprintf(stderr, "\nUnknown option: '-%c'.\n\n", optopt);
	exit(EXIT_FAILURE);
      default:
	abort();
      }

  /* First check if the input name was set. */
  checkinimage(p->inname);

  /* If outname was not set, set it here.*/
  if(p->freeoutname==1)
    {
      findnamebase(p->inname, &p->outname);
      strcat(p->outname, ".fits");
    }

  /* Check if the output name exists, if so, delete it. */
  checkremoveoutimage(p->outname);
}
