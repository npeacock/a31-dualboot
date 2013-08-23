/*
 * specialreboot.c
 *
 *  Created on: Aug 8, 2013
 *      Author: Neal Peacock
 */

#include "specialreboot.h"
#include "common.h"

int special_reboot( char *arg )
{

	int ret;

	write_misc(arg);
	ret = reboot(RB_AUTOBOOT);

	return ret;
}

int mount_nanda()
{
	int ret = 0;

	if(  access(DEF_BOOT_FILE, F_OK) ){
		const char* devname = NANDA_BLK_DEV;
		const char* mount_point = NANDA_MNT_POINT;
		const char* filesystem = "vfat";
		const unsigned long flags = MS_NOATIME | MS_NODIRATIME;

		ret = mount(devname, mount_point, filesystem, flags, NULL);
	}

	return ret;

}

int unmount_nanda()
{
	return umount(NANDA_MNT_POINT);
}

char* lookup_default_reboot()
{
	char* ret = DEF_BOOT_STRING;
	int mounterr = 0;

	mounterr = mount_nanda();

	if(!mounterr){
		FILE* defboot = fopen(DEF_BOOT_FILE, "r");
		if (defboot == NULL) {
			LOGE("failed to open %s (%s)\n", DEF_BOOT_FILE,strerror(errno));
			return DEF_BOOT_STRING;
		}

		char buffer[1024];
		int i;
		while (fgets(buffer, sizeof(buffer)-1, defboot)) {
			for (i = 0; buffer[i] && isspace(buffer[i]); ++i);
			if (buffer[i] == '\0' || buffer[i] == '#') continue;

			char* def_boot_type = strtok(buffer+i, " \t\n");
			ret = strdup(def_boot_type);
		}

		fclose(defboot);
		unmount_nanda();
	}

	return ret;
}


int set_default_reboot( char* defbootstr)
{
	int ret = 0;
	int test = 0;

	ret = mount_nanda();

	if(!ret){
		FILE* defboot = fopen(DEF_BOOT_FILE, "w");
		if (defboot == NULL) {
			LOGE("failed to open %s (%s)\n", DEF_BOOT_FILE,strerror(errno));
			ret = errno;
		}else{
			test = fputs(defbootstr,defboot);

			if( test < 0){
				LOGE("failed to write to %s default boot of %s)\n", DEF_BOOT_FILE, defbootstr);
				ret = test;
			}else{
				ret = fclose(defboot);

				if(ret != 0){
					LOGE("failed to close %s\n", DEF_BOOT_FILE);
				}else {
					ret = unmount_nanda();

					if(ret != 0){
						LOGE("failed to unmount nanda\n");
					}
				}
			}
		}
	}
	return ret;
}



void special_reboot_default( )
{

	char* type = lookup_default_reboot();

	special_reboot(type);
}

