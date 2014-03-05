####### Makefile for openwattson - manually generated
#
# All user parameters are stored in a config file
# Default locations are 
# 1. Path to config file including filename given as parameter
# 2. ./openwattson.conf
# 3. /usr/local/etc/openwattson.conf
# 4. /etc/openwattson.conf
#
# This makefile is made for Linux.
# No Windows version yet
#
# You may want to adjust the 3 directories below

prefix = /usr/local
exec_prefix = ${prefix}
bindir = ${exec_prefix}/bin

#########################################

CC  = gcc
OBJ = linuxwattson.o rwwattson.o 
FETCH_OBJ = fetchwattson.o $(OBJ)
LOG_OBJ = logwattson.o $(OBJ)
GET_POWER_OBJ = getpower.o $(OBJ)
GET_GEN_OBJ = getgen.o $(OBJ)

VERSION = 0.1
HTML_DIR = ../html_openwattson

CFLAGS = -Wall -O3 -DVERSION=\"$(VERSION)\"
CC_LDFLAGS = -lm
CC_WINFLAG = 
# For Windows - comment the two line above and un-comment the two lines below.
#CC_LDFLAGS = -lm -lwsock32
#CC_WINFLAG = -mwindows
INSTALL = install

####### Build rules

all: fetchwattson logwattson getpower getgen
	
fetchwattson : $(FETCH_OBJ)
	$(CC) $(CFLAGS) -o $@ $(FETCH_OBJ) $(CC_LDFLAGS)

logwattson : $(LOG_OBJ)
	$(CC) $(CFLAGS) -o $@ $(LOG_OBJ) $(CC_LDFLAGS)

getpower : $(GET_POWER_OBJ)
	$(CC) $(CFLAGS) -o $@ $(GET_POWER_OBJ) $(CC_LDFLAGS)

getgen : $(GET_GEN_OBJ)
        $(CC) $(CFLAGS) -o $@ $(GET_GEN_OBJ) $(CC_LDFLAGS)

install:
	mkdir -p $(bindir)
	$(INSTALL) fetchwattson $(bindir)
	$(INSTALL) logwattson $(bindir)
	$(INSTALL) getpower $(bindir)
	$(INSTALL) getgen $(bindir)
	
uninstall:
	rm -f $(bindir)/fetchwattson $(bindir)/logwattson $(bindir)/getpower $(binddir)/getgen

clean:
	rm -rf *~ *.o fetchwattson logwattson getpower getgen

cleanexe:
	rm -f *~ *.o fetchwattson.exe logwattson.exe getpower.exe getgen.exe

tarball: clean
	mkdir -p $(HTML_DIR)
	tar -cf $(HTML_DIR)/openwattson-$(VERSION).tar ../openwattson 
	gzip -9 $(HTML_DIR)/openwattson-$(VERSION).tar 
	cp -u README $(HTML_DIR)/
	cp -u INSTALL $(HTML_DIR)/
	cp -u COPYING $(HTML_DIR)/

