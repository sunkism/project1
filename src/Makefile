CC	= /usr/bin/gcc
CPP	= /usr/bin/g++
AR	= /usr/bin/ar
LD	= /usr/bin/ld

MYHOME = ${HOME}/project1
SRC_HOME = ${MYHOME}/src
BIN_HOME = ${MYHOME}/bin
INCLUDE  = -I.

CFLAGS	= -Wall -std=c99 -g -D_XOPEN_SOURCE=600 $(INCLUDE)
CPPFLAGS = -I.

COMPILE.c = $(CC) -c
COMPILE.cpp = $(CPP) -c

HDRS = logger.h
SRCS = FileWatcher.c logger.c
OBJS = $(SRCS:%.c=%.o)
TARGET = $(basename $(SRCS))

#.SUFFIXES: .c .o
.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

all : FileWatcher

FileWatcher : $(OBJS) 
	$(CC) -o $@ $(OBJS)
	mv -f $@ ../bin/

$(OBJS) : $(HDRS)

clean:
	rm -f *.o core
