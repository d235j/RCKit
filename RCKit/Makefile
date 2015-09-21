# Makefile
#
# Makefile for the Arduino RCKt project
#
# Author: Mike McCauley (mikem@airspayce.com)
# Copyright (C) 2010 Mike McCauley
# $Id: Makefile,v 1.2 2010/06/30 02:49:05 mikem Exp mikem $

PROJNAME = RCKit
# Dont forget to also change the version at the top of RCRx.h and in the full package name
DISTFILE = $(PROJNAME)-2.5.zip

all:	doxygen dist upload

doxygen: 
	doxygen project.cfg

ci:
	ci -l `cat MANIFEST`

dist:	
	(cd ..; zip $(PROJNAME)/$(DISTFILE) `cat $(PROJNAME)/MANIFEST`)

upload:
	rsync -avz $(DISTFILE) doc/ www.airspayce.com:public_html/mikem/arduino/$(PROJNAME)
