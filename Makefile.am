AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4
# 将config.h包含在编译中
AM_CPPFLAGS = -I$(top_srcdir)/include -include config.h
AM_CFLAGS = -Wall -g -O3 -MD
AM_LDFLAGS = -L. -lhotcalls -lpthread

# Specify shared libraries to be built
lib_LTLIBRARIES = libhotcalls.la
libhotcalls_la_SOURCES = src/hotcalls.c \
                    src/spinlock.c
libhotcalls_la_LDFLAGS = -version-info 1:0:0

# Specify executables to be built
bin_PROGRAMS = hot_calls_test
hot_calls_test_SOURCES = src/hot_calls_test.c
hot_calls_test_LDADD = libhotcalls.la

# Specify headers to be installed
pkgincludedir = $(includedir)/hotcalls
pkginclude_HEADERS = include/hotcalls.h