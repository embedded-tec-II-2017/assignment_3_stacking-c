AC_INIT([stacking_c], [0.0.1], [user@email.com], [stacking_c], [http://www.example.com])
AM_INIT_AUTOMAKE

AM_PROG_AR
LT_INIT

AC_PREREQ([2.68])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

AC_CONFIG_FILES([Makefile src/Makefile])

AC_CONFIG_SRCDIR([src/test_main.c])

AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

PKG_CHECK_MODULES(LIBTIFF, libtiff-4)

AC_SUBST(LIBTIFF_CFLAGS)

AC_SUBST(LIBTIFF_LIBS)

AC_OUTPUT
