/*===============================================================
*	Copyright (C) 2018 All rights reserved.
*	
*	Filename：sysinfo.h
*	Author：julian.chen
*	Date：2018-09-04
*	Discription:
*	
*	release notes：
*
================================================================*/
#ifndef _SYSINFO_H
#define _SYSINFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <linux/wireless.h>

#define _ARP_LIST		"/proc/net/arp"



int get_arp_list_json(char *json_buf, int buf_size);  
int cpu_used_percent(void *paramt);
int ram_used_percent(void *paramt);

   
#endif //SYSINFO_H
