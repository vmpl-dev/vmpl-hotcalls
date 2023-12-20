# Makefile.am
AUTOMAKE_OPTIONS = foreign

lib_LIBRARY = libhotcalls
hotcalls_SOURCES = src/hot_calls.c src/spinlock.c                   

bin_PROGRAMS = hot_calls_test
my_program_SOURCES = src/spinlock.c src/hot_calls_test.c
check_PROGRAMS = hot_calls_test
TESTS = $(check_PROGRAMS)