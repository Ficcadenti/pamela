#------------------------------------------------------------------------------
#
#  Makefile for Pamela
#
#  Author: Raffaele Ficcadenti
#
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
# Program and directories

#SHELL	= /bin/bash

# Basic directories
TOP	= $(shell pwd)
SR	= $(TOP)/src
IN	= $(TOP)/include
LB	= $(TOP)/lib
BN      = $(TOP)/bin

#------------------------------------------------------------------------------
# Included options (result of ./configure)

include $(TOP)/config/Makefile.options
include $(TOP)/config/Makefile.config

CFLAGS	+= -I$(IN)
LDFLAGS += -L$(LB)


#------------------------------------------------------------------------------
# Commands:

#.NOPARALLEL:
.EXPORT_ALL_VARIABLES: all shared dispatcher pamelaroot
.SILENT:
.NOTPARALLEL: shared dispatcher pamelaroot
.SUFFIXES:
.SUFFIXES: .cpp .h .o .so


#------------------------------------------------------------------------------
# Pamela

PAMELALIBS = -lshared 

all: link shared 
	@$(MAKE) all -C src

shared: link
	@$(MAKE) shared -C src

dispatcher: link shared
	@$(MAKE) dispatcher -C src	

pamelaroot: link shared
	@$(MAKE) pamelaroot -C src


#------------------------------------------------------------------------------
# additional options:

link:
	$(MAKE) -s link -C src 

clean:
	@$(MAKE) -s clean -C src 
	$(RM) -f $(LB)/*.o
	$(RM) -f $(LB)/*.$(DLL)
ifneq ($(DLL),so)
	$(RM) -f $(LB)/*.so
endif
	$(RM) -f *~
	$(RM) -f \#*
	$(RM) -f $(IN)/*.h

realclean: clean
	$(RM) -f bin/*
	$(RM) -f lib/*
	$(RM) -f include/*

#
#------------------------------------------------------------------------------


