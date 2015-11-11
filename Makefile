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


DIRS = src 

all:
	set -e; for d in $(DIRS); do $(MAKE) -C $$d ; done

clean:
	set -e; for d in $(DIRS); do $(MAKE) -C $$d clean; done

distclean:
	set -e; for d in $(DIRS); do $(MAKE) -C $$d distclean; done