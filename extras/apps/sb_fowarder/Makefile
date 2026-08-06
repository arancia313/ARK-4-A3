ARKROOT ?= ../../../
TARGET = sb_forwarder
OBJS = main.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBS = -lpspiofilemgr -lpsputility -lpspuser

BUILD_PRX = 1
PSP_EBOOT_TITLE = ARK-4 A3 SB Fowarder
PSP_EBOOT_ICON = ICON0.PNG

EXTRA_TARGETS = EBOOT.PBP

include $(ARKROOT)/common/make/global.mak
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
include $(ARKROOT)/common/make/beauty.mak
