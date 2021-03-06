##############################################################################
##                                                                          ##
##  File Name:      makefile                                                ##
##                                                                          ##
##  Description:    Builds QstComm.so, the Solaris Shared Object (SO) file  ##
##                  that  supports  communication  with the Intel(R) Quiet  ##
##                  System Technology (QST) F/W Subsystem running  on  the  ##
##                  Intel(R)  Management  Engine (ME), and QstInst.so, the  ##
##                  Solaris SO file that supports the  instrumentation  of  ##
##                  sensors and fan controllers managed by Intel(R) QST.    ##
##                                                                          ##
##############################################################################

##############################################################################
##                                                                          ##
##     Copyright (c) 2005-2009, Intel Corporation. All Rights Reserved.     ##
##                                                                          ##
##  Redistribution and use in source and binary  forms,  with  or  without  ##
##  modification, are permitted provided that the following conditions are  ##
##  met:                                                                    ##
##                                                                          ##
##    - Redistributions of source code must  retain  the  above  copyright  ##
##      notice, this list of conditions and the following disclaimer.       ##
##                                                                          ##
##    - Redistributions  in binary form must reproduce the above copyright  ##
##      notice, this list of conditions and the  following  disclaimer  in  ##
##      the   documentation  and/or  other  materials  provided  with  the  ##
##      distribution.                                                       ##
##                                                                          ##
##    - Neither the name  of  Intel  Corporation  nor  the  names  of  its  ##
##      contributors  may  be  used to endorse or promote products derived  ##
##      from this software without specific prior written permission.       ##
##                                                                          ##
##  DISCLAIMER: THIS SOFTWARE IS PROVIDED BY  THE  COPYRIGHT  HOLDERS  AND  ##
##  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  ##
##  BUT  NOT  LIMITED  TO,  THE  IMPLIED WARRANTIES OF MERCHANTABILITY AND  ##
##  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN  NO  EVENT  SHALL  ##
##  INTEL  CORPORATION  OR  THE  CONTRIBUTORS  BE  LIABLE  FOR ANY DIRECT,  ##
##  INDIRECT, INCIDENTAL, SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL  DAMAGES  ##
##  (INCLUDING,  BUT  NOT  LIMITED  TO, PROCUREMENT OF SUBSTITUTE GOODS OR  ##
##  SERVICES; LOSS OF USE, DATA, OR  PROFITS;  OR  BUSINESS  INTERRUPTION)  ##
##  HOWEVER  CAUSED  AND  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,  ##
##  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING  ##
##  IN  ANY  WAY  OUT  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  ##
##  POSSIBILITY OF SUCH DAMAGE.                                             ##
##                                                                          ##
##############################################################################

CC      = /usr/sfw/bin/gcc
LIBDIR  = /usr/lib

CFLAGS  = -c -fPIC -ggdb -Wno-multichar -I../Common -I../../Include
LDFLAGS = -ggdb

BITS    = $(strip $(shell isainfo -b))

ifeq ($(BITS),64)
	CFLAGS  += -m64
	LDFLAGS += -m64
	LIBDIR   = /usr/lib/64
endif

##############################################################################
## Commands                                                                 ##
##############################################################################

.PHONY: install
install: Debug/libQstComm.so.1.0 Debug/libQstInst.so.1.0
	rm -f /usr/include/Qst*.h /usr/include/typedef.h
	cp ../../Include/Qst*.h /usr/include
	cp ../../Include/typedef.h /usr/include

.PHONY: uninstall
uninstall:
	rm -f /usr/include/Qst*.h /usr/include/typedef.h $(LIBDIR)/libQst*.so*

.PHONY: clean
clean:
	-rm -f Debug/*
	-rmdir -p Debug

##############################################################################
## Rules/Dependencies                                                       ##
##############################################################################

Debug:
	mkdir -p Debug

Debug/QstComm.o: QstComm.c Debug heci.h ../../Include/QstComm.h \
	../../Include/QstCmd.h ../../Include/QstCfg.h ../../Include/typedef.h
	$(CC) $(CFLAGS) -o $@ $<

Debug/LegTranslationFuncs.o: ../Common/LegTranslationFuncs.c Debug \
	../Common/LegTranslationFuncs.h ../../Include/QstCmd.h \
	../../Include/QstCfg.h ../../Include/QstCmdLeg.h ../../Include/typedef.h
	$(CC) $(CFLAGS) -o $@ $<

Debug/heci.o: heci.c Debug heci.h ../../Include/typedef.h
	$(CC) $(CFLAGS) -o $@ $<

Debug/CritSect.o: CritSect.c Debug ../Common/CritSect.h \
	../../Include/typedef.h
	$(CC) $(CFLAGS) -o $@ $<

Debug/libQstComm.so.1.0: Debug/QstComm.o Debug/heci.o Debug/CritSect.o \
	Debug/LegTranslationFuncs.o
	$(CC) $(LDFLAGS) -shared -Wl,-soname,libQstComm.so.1 -o $@ $^
	rm -f $(LIBDIR)/libQstComm.so*
	cp Debug/libQstComm.so.1.0 $(LIBDIR)
	ln -sf $(LIBDIR)/libQstComm.so.1.0 $(LIBDIR)/libQstComm.so
	ln -sf $(LIBDIR)/libQstComm.so.1.0 $(LIBDIR)/libQstComm.so.1



Debug/QstDll.o: ../Common/QstDll.c Debug ../Common/QstDll.h \
	../Common/INIFile.h ../Common/AccessQst.h ../Common/MilliTime.h \
	../../Include/QstCmd.h ../../Include/QstCfg.h ../Common/GlobMem.h \
	../Common/CritSect.h ../../Include/typedef.h
	$(CC) $(CFLAGS) -o $@ $<

Debug/AccessQst.o: ../Common/AccessQst.c Debug ../Common/QstDll.h \
	../../Include/QstComm.h ../Common/AccessQst.h ../../Include/QstInst.h \
	../Common/MilliTime.h ../../Include/QstCmd.h ../../Include/QstCfg.h \
	../../Include/typedef.h
	$(CC) $(CFLAGS) -o $@ $<

Debug/QstInst.o: ../Common/QstInst.c Debug ../Common/QstDll.h \
	../../Include/QstInst.h ../../Include/QstComm.h ../Common/MilliTime.h \
	../../Include/QstCmd.h ../../Include/QstCfg.h ../../Include/typedef.h
	$(CC) $(CFLAGS) -o $@ $<

Debug/MilliTime.o: ../Common/MilliTime.c Debug ../Common/MilliTime.h \
	../../Include/typedef.h
	$(CC) $(CFLAGS) -o $@ $<

Debug/INIFile.o: ../Common/INIFile.c Debug ../Common/INIFile.h \
	../Common/BFileIO.h ../../Include/typedef.h
	$(CC) $(CFLAGS) -o $@ $<

Debug/BFileIO.o: ../Common/BFileIO.c Debug ../Common/BFileIO.h \
	../../Include/typedef.h
	$(CC) $(CFLAGS) -o $@ $<

Debug/GlobMem.o: GlobMem.c Debug ../Common/GlobMem.h ../../Include/typedef.h
	$(CC) $(CFLAGS) -o $@ $<

Debug/libQstInst.so.1.0: Debug/QstDll.o Debug/QstInst.o Debug/AccessQst.o \
	Debug/MilliTime.o Debug/INIFile.o Debug/BFileIO.o Debug/GlobMem.o \
	Debug/CritSect.o
	$(CC) $(LDFLAGS) -shared -Wl,-soname,libQstInst.so.1 -lQstComm -o $@ $^
	rm -f $(LIBDIR)/libQstInst.so*
	cp Debug/libQstInst.so.1.0 $(LIBDIR)
	ln -sf $(LIBDIR)/libQstInst.so.1.0 $(LIBDIR)/libQstInst.so
	ln -sf $(LIBDIR)/libQstInst.so.1.0 $(LIBDIR)/libQstInst.so.1


