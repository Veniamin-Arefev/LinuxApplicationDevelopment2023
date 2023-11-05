#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [1.00], [lol@tata.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([Rhash is needed])])
AC_CHECK_LIB([readline],[readline])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror strstr])


AC_ARG_ENABLE([readline],
    [AS_HELP_STRING([--enable-readline], [Enable input with readline])],
    [AC_CHECK_LIB(
        [readline],
        [readline],
        [AC_DEFINE(READLINE,[1],[Readline support])],
        [AC_MSG_ERROR([Readline not found])]
    )],
    []
)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
