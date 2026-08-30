#include <pspmoduleexport.h>
#define NULL ((void *) 0)

extern void module_start;
extern void module_stop;
extern void module_info;
static const unsigned int __syslib_exports[6] __attribute__((section(".rodata.sceResident"))) = {
	0xD632ACDB,
	0xCEE8593C,
	0xF01D73A7,
	(unsigned int) &module_start,
	(unsigned int) &module_stop,
	(unsigned int) &module_info,
};

extern void pspUsbDeviceSetDevice;
extern void pspUsbDeviceFinishDevice;
static const unsigned int __pspUsbDevice_exports[4] __attribute__((section(".rodata.sceResident"))) = {
	0xD4D90520,
	0xB3CF0329,
	(unsigned int) &pspUsbDeviceSetDevice,
	(unsigned int) &pspUsbDeviceFinishDevice,
};

extern void pspUsbDeviceSetDevice;
extern void pspUsbDeviceFinishDevice;
static const unsigned int __pspUsbDevice_driver_exports[4] __attribute__((section(".rodata.sceResident"))) = {
	0xD4D90520,
	0xB3CF0329,
	(unsigned int) &pspUsbDeviceSetDevice,
	(unsigned int) &pspUsbDeviceFinishDevice,
};

const struct _PspLibraryEntry __library_exports[3] __attribute__((section(".lib.ent"), used)) = {
	{ NULL, 0x0000, 0x8000, 4, 1, 2, &__syslib_exports },
	{ "pspUsbDevice", 0x0000, 0x4001, 4, 0, 2, &__pspUsbDevice_exports },
	{ "pspUsbDevice_driver", 0x0000, 0x0001, 4, 0, 2, &__pspUsbDevice_driver_exports },
};
