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
#ifndef ARGPPARSER_H
#define ARGPPARSER_H

#include <argp.h>

#include "main.h"

/* Definition parameters for the argp: */
const char *argp_program_version=PACKAGE_STRING
  "\nCopyright (C) 2014 Mohammad Akhlaghi.\n"
  "License GPLv3+: GNU GPL version 3 or later "
  "<http://gnu.org/licenses/gpl.html>\n"
  "This is free software: you are free to change "
  "and redistribute it.\n"
  "There is NO WARRANTY, to the extent permitted by law.";





const char *argp_program_bug_address=PACKAGE_BUGREPORT;





static char args_doc[] = "[FITSimage.fits] JPEGimage";





const char doc[] = 
  /* Before the list of options: */
  "\n"PACKAGE_STRING" -- Convert a JPG image to a FITS image image. \n"
  "Configured for this machine on "CONFIGDATE", "CONFIGTIME".\n\n"
  "See \"Running "PACKAGE_NAME"\" in the official documentation for more "
  "detailed explanation. Official documentation can be found by running:"
  "`info "PACKAGE"`.\n"
  /* After the list of options: */
  "\v"
  PACKAGE_NAME" home page: "PACKAGE_URL;





/* The options are classified into these categories:
   1. Operating mode like quiet, help and version.
   2. Input (image, mask and kernel name, extensions and ...)
   3. Meshs and threads.
   4. Detection 

   Available letters for short options:
   a b c d e g h i j k l m n p q r s t u v w x y z
   A B C D E F G H I J L M N O P Q R S T U W X X Y Z

   Number keys used: <=500.

   Options with keys (second structure element) larger than 500 do not
   have a short version.
 */
static struct argp_option options[] =
  {
    /* Such cases are group headers */
    {
      "hflip",		      /* Long name for this option.         */
      'f',		      /* Short name or key for this option. */
      0,		      /* Informative type of value it gets. */
      0,                      /* Flags for this option. */
      "Do not flip the image along the horizontal.",
      -1		      /* Option group ID. */
    },
    {
      "output",
      'o',
      "STR",
      0,
      "Name of output file (with any extension).",
      -1
    },
    {
      "keepnamedir",
      'K',
      0,
      0,
      "Keep directory information for output.",
      -1
    },

    
    {0}
  };





/* Parse a single option: */
static error_t
parse_opt(int key, char *arg, struct argp_state *state)
{ 
  /* Save the arguments structure: */
  struct mainparams *p = state->input;
  
  /* In case the user incorrectly uses the equal sign (for example
     with a short format or with space in the long format, then `arg`
     start with (if the short version was called) or be (if the long
     version was called with a space) the equal sign. So, here we
     check if the first character of arg is the equal sign, then the
     user is warned and the program is stopped: */
  if(arg && arg[0]=='=')
    argp_error(state, "Incorrect use of the equal sign (`=`). For short "
	       "options, `=` should not be used and for long options, "
	       "there should be no space between the option, equal sign "
	       "and value.");
 
  switch(key)
    {

    case 'f':
      p->flip=0;
      break;
    case 'K':
      p->removenamedir=0;
      break;      
    case 'o':
      if(p->outname)
	argp_error(state, "Only one JPEG image name should be given.");
      else
	p->outname=arg;
      break;
      
      /* Read the non-option argument: */
    case ARGP_KEY_ARG:
      /* Since there are only two arguments, state->arg_num should
	 never be more than 2. Note that it starts from zero.*/
      if(state->arg_num >= 2)
	argp_error(state, "Too many arguments! ");

      /* See what type of input value it is and put it in. */
      if( strcmp(&arg[strlen(arg)-5], ".fits")==0 )
	{
	  if(p->outname)
	    argp_error(state, "Only one FITS image should be given.");
	  else
	    p->outname=arg;
	}
      else if( strcmp(&arg[strlen(arg)-4], ".jpg")==0
	       || strcmp(&arg[strlen(arg)-4], ".JPG")==0
	       || strcmp(&arg[strlen(arg)-5], ".jpeg")==0
	       || strcmp(&arg[strlen(arg)-5], ".JPEG")==0)
	{
	  if(p->inname)
	    argp_error(state, "Only one JPEG image name should be given.");
	  else
	    p->inname=arg;
	}
      else
	argp_error(state, "Argument not recognized as a FITS image "
		   "(ending with `.fits`) or a JPEG image (ending in "
		   "any of `.jpg`, `.jpeg`, `.JPG` or `.JPEG`).");
      break;
      
      /* Make sure an argument is given: */
    case ARGP_KEY_END:
      if(state->arg_num==0)
	argp_error(state, "No argument given!");
      if(p->inname==NULL)
	argp_error(state, "No input JPEG image provided!");
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}





/* Basic structure defining the whole argument reading process. */
static struct argp argp = {options, parse_opt, args_doc, doc};


#endif
