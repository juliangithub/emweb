/*===============================================================
*	Copyright (C) 2018 All rights reserved.
*	
*	Filename：utils.c
*	Author：julian
*	Date：2018-07-27
*	Discription:
*	
*	release notes：
*
================================================================*/
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>	
#include "utils.h"

 void sleep_interval_dynamic()
{
	static int interval = 1;
	if(2 * interval < 300) 
	{
		interval *= 2;
	}
	dlog_info("wait next loop in :%d second\n", interval);
	sleep(interval);

}


int get_pid(char *filename)
{
	struct stat status;
	char buff[100];
	FILE *fp;

	if ( stat(filename, &status) < 0)
		return -1;
	fp = fopen(filename, "r");
	if (!fp) {
        	fprintf(stderr, "Read pid file error!\n");
		return -1;
   	}
	fgets(buff, 100, fp);
	fclose(fp);

	return (atoi(buff));
}

