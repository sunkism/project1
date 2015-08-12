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

SRCS = dir_search.c test.c
OBJS = $(SRCS:%.c=%.o)
TARGET = $(basename $(SRCS))

.SUFFIXES :
%   : %.o
	$(CC) -o $@ $<

all	: $(TARGET)

%   : %.o
	$(CC) -o $@ $<
%.o : %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean :
	rm -f *.o core

