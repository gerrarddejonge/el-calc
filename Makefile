#***************************************************************************
#                        Makefile
#                        -----------------------------------------------
#    copyright		: (C) 2015 by G. de Jonge
#    email		: development.gdj@netvisit.nl
#    license		: GPLv2 or later
#
#    modified		: 
#***************************************************************************


DIRS = src 

all:
	set -e; for d in $(DIRS); do $(MAKE) -C $$d ; done

clean:
	set -e; for d in $(DIRS); do $(MAKE) -C $$d clean; done

distclean:
	set -e; for d in $(DIRS); do $(MAKE) -C $$d distclean; done