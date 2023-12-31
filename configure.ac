AC_INIT([hotcalls], [1.0] [your-email@example.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Enable static linking
AC_ENABLE_STATIC

AC_PROG_CC([musl-gcc])

# Specify the desired archiver program with options
AR=ar

# Checks for programs
AM_PROG_AR
AM_PROG_AS

LT_INIT([static, shared])

# Set installation prefix
AC_PREFIX_DEFAULT([/usr/local/musl])
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_MACRO_DIRS([m4])

AC_OUTPUT