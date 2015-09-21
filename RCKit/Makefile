# Makefile
#
# Makefile for the Arduino RCKt project
#
# Author: Mike McCauley (mikem@open.com.au)
# Copyright (C) 2010 Mike McCauley
# $Id: Makefile,v 1.2 2010/06/30 02:49:05 mikem Exp mikem $

PROJNAME = RCKit
# Dont forget to also change the version at the top of RCRx.h and in the full package name
DISTFILE = $(PROJNAME)-2.0.zip

all:	doxygen dist upload

doxygen: 
	doxygen project.cfg

ci:
	ci -l `cat MANIFEST`

dist:	
	(cd ..; zip $(PROJNAME)/$(DISTFILE) `cat $(PROJNAME)/MANIFEST`)

upload:
	rsync -avz $(DISTFILE) doc/ server2:/var/www/html/mikem/arduino/$(PROJNAME)

#	scp $(DISTFILE) doc/*.html doc/*.gif doc/*.png doc/*.css doc/*.pdf server2:/var/www/html/mikem/arduino/$(PROJNAME)
