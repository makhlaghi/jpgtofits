#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([JPGtoFITS], [0.1], [makhlaghi@gmail.com], [jpgtofits],
        [https://github.com/makhlaghi/jpgtofits])
AM_INIT_AUTOMAKE([-Wall -Werror gnu])
AC_CONFIG_SRCDIR([src/ui.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
${CFLAGS=""}
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([cfitsio], [main], [], [AC_MSG_ERROR([Cannot continue.])])
AC_CHECK_LIB([jpeg], [main], [], [AC_MSG_ERROR([Cannot continue.])])
AC_CHECK_LIB([m], [main], [], [AC_MSG_ERROR([Cannot continue.])])

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdlib.h string.h unistd.h argp.h], [],
                 [AC_MSG_ERROR([Cannot continue.])])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strtol])

#Tell configure which files to work on:
AC_CONFIG_FILES([Makefile
                 src/Makefile])

#Read the configuration date.
AC_MSG_CHECKING([for date of configuration])
AC_DEFINE_UNQUOTED([CONFIGDATE], ["`date +"%d %B %Y"`"], 
                   [Date of configuration])
AC_DEFINE_UNQUOTED([CONFIGTIME], ["`date +"%H:%M"`"], 
                   [Time of configuration])
AC_MSG_RESULT([done])	

#Make the outputs:
AC_OUTPUT

#Print a bye-bye message:
echo
echo "==================================================="
echo "AC_PACKAGE_STRING is now configured:"
echo
echo "You are now ready to compile AC_PACKAGE_STRING".
echo "Simply run the commands: \`make\` then \`make install\`"
echo "You can run \`make check\` before installing."
echo "==================================================="
echo
