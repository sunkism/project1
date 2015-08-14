CC	= /usr/bin/gcc
CPP	= /usr/bin/g++
AR	= /usr/bin/ar
LD	= /usr/bin/ld

MYHOME = ${HOME}/project1
SRC_HOME = ${MYHOME}/src
BIN_HOME = ${MYHOME}/bin

CFLAGS	= -Wall -std=c99 -g -D_XOPEN_SOURCE=600
CPPFLAGS = -I.

COMPILE.c = $(CC) -c
COMPILE.cpp = $(CPP) -c

SRCS = FileWatcher.c test.c
OBJS = $(SRCS:%.c=%.o)
TARGET = $(basename $(SRCS))

#.SUFFIXES: .c .o
.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

all : FileWatcher test

FileWatcher : FileWatcher.o
	$(CC) -o $@ $<
	mv -f $@ ../bin/

test : test.o
	$(CC) -o $@ $<
	mv -f $@ ../bin/
clean:
	rm -f *.o core
