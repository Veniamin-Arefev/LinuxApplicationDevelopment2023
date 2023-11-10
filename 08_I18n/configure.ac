#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([guessr], [1.00], [lol@tata.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)
GETTEXT_PACKAGE=guessr
AC_SUBST(GETTEXT_PACKAGE)
ALL_LINGUAS="ru"

AC_CONFIG_SRCDIR([src/guessr.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INTLTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([realpath setlocale])

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile.in])
AC_OUTPUT
