TARGET = sb_fowarder
OBJS = main.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBS = -lintraFont -lglib2d -lpspgum -lpspgu -lpng -lz -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = ARK-4 A3 Smartbuilder Forwarder

all: EBOOT.PBP

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak


EBOOT.PBP: $(TARGET).prx
pack-pbp EBOOT.PBP PARAM.SFO NULL NULL NULL NULL NULL $(TARGET).prx
@echo "--- Generated the eboot for this thing. ---"
