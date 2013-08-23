/*
 * specialreboot.c
 *
 *  Created on: Aug 8, 2013
 *      Author: Neal Peacock
 */
#ifndef _SPECIAL_REBOOT_H
#define _SPECIAL_REBOOT_H	1

#include <sys/mount.h>  // for _IOW, _IOR, mount()
#include <unistd.h>
#include <errno.h>
#include <libio.h>

// I'm not going to bother and try and included these from the right spots, this is a universal thing
#define  LINUX_REBOOT_CMD_RESTART 0x01234567
#define RB_AUTOBOOT LINUX_REBOOT_CMD_RESTART

#define NANDA_BLK_DEV "/dev/block/nanda"
#define NANDA_MNT_POINT "/mnt"
#define DEF_BOOT_FILE "/mnt/default-boot.conf"

#define LIN_BOOT_STRING "linux"
#define AND_BOOT_STRING "android"
#define EXT_BOOT_STRING "extra"
#define DEF_BOOT_STRING "default"

int special_reboot( char *arg );
int mount_nanda();
char* lookup_default_reboot();
int special_reboot_default( );

#endif

