/*
 * specialreboot.c
 *
 *  Created on: Aug 8, 2013
 *      Author: Neal Peacock
 */

// I'm not going to bother and try and included these from the right spots, this is a universal thing
#define  LINUX_REBOOT_CMD_RESTART 0x01234567
#define RB_AUTOBOOT LINUX_REBOOT_CMD_RESTART

int special_reboot( char *arg )
{

	int ret;

	write_misc(arg);
	ret = reboot(RB_AUTOBOOT);

	return ret;
}



