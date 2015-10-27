#***************************************************************************
#                        Makefile
#                        -----------------------------------------------
#    copyright		: (C) 2015 by G. de Jonge
#    email		: development.gdj@netvisit.nl
#    license		: GPLv2 or later
#
#    modified		: 
#***************************************************************************


#**************************************************************************
#*                                                                        *
#*   This program is free software; you can redistribute it and/or modify *
#*   it under the terms of the GNU General Public License as published by *
#*   the Free Software Foundation; either version 2 of the License, or    *
#*   (at your option) any later version.                                  *
#*                                                                        *
#**************************************************************************/ 



TARGET  = el-calc

SOURCES = el_main.c	\
	el_string.c	\
	el_items.c	\
	el_args.c	\
	el_parse.c	\
	el_shop.c
OBJECTS = el_main.o	\
	el_string.o	\
	el_items.o	\
	el_args.o	\
	el_parse.o	\
	el_shop.o

HEADERS = 

LIBS    = 
INCLIB  =  

CC	= gcc
#CC	= clang
OC	= objcopy 
TOUCH   = touch

RM     = rm -f
CM     = chmod

STANDARD= --std=c99

CPFLAGS = -g -O0 -save-temps $(STANDARD) -Wall -pedantic -Wextra -Wstrict-prototypes -fno-builtin
LDFLAGS = 
DEFINES = 
#DEBUG = -DDEBUG		# Enable debug mode

.PHONY: elcalc clean distclean


.h.c:
	$(TOUCH) $(@)

.c.o:
	$(CC) -c $(CPFLAGS) $(INCLIB) $(DEFINES) $(DEBUG)  $(<) -o $(@)

all: $(OBJECTS)
	$(CC)  $(CPFLAGS) $(LDFLAGS) $(OBJECTS) $(DEFINES) $(DEBUG) -o $(TARGET)

elcalc: $(OBJECTS)
	$(CC)  $(CPFLAGS) $(LDFLAGS) $(OBJECTS) $(DEFINES) $(DEBUG) -o $(TARGET)

el_main.c: $(HEADERS)
	$(TOUCH) el_main.c

clean:
	$(RM) *~
	$(RM) *.o
	$(RM) *.ihex
	$(RM) *.map
	$(RM) *.i
	$(RM) *.s

distclean: clean
	$(RM) $(TARGET)
