# FreeS/WAN subdir makefile
# Copyright (C) 1998-2001  Henry Spencer.
# 
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
#
# RCSID $Id: //WIFI_SOC/MP/SDK_4_3_0_0/RT288x_SDK/source/user/openswan-2.4.9/testing/kunit/Makefile#1 $

OPENSWANSRCDIR?=$(shell cd ../..; pwd)
include $(OPENSWANSRCDIR)/Makefile.inc

SUBDIRS=libkern rcv-01 rcv-02 xmit-01

def:
	@echo "Please read doc/intro.html or INSTALL before running make"
	@false

# programs

include/linux/madelinks: include/linux/files.txt
	@(cd include/linux && make links )

include/net/madelinks: include/net/files.txt
	@(cd include/net && make links )

include/asm/madelinks: include/asm/files.txt
	@(cd include/asm && make links )

check:	include/linux/madelinks include/net/madelinks include/asm/madelinks

cleanall distclean mostlyclean realclean install programs checkprograms check clean spotless install_file_list:
	@for d in $(SUBDIRS) ; \
	do \
		(cd $$d && $(MAKE) srcdir=${srcdir}$$d/ OPENSWANSRCDIR=$(OPENSWANSRCDIR) $@ ) || exit 1;\
	done; 

