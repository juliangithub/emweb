/*===============================================================
*	Copyright (C) 2020 All rights reserved.
*	
*	Filename：recipe.c
*	Author：julian
*	Date：2020-02-03
*	Discription:
*	
*	release notes：
*
================================================================*/
//#include "recipe.h"
#ifndef _OPERATIONS_H
#define _OPERATIONS_H

#include "sysinfo.h"
int set_str_access_deny(void *paramt){
	sprintf(paramt, "access deny!");
	return ERR_NOERROR;
}

int set_num_access_deny(void *paramt){
	return ERR_ACCESS_DENY;
}

int set_str_test(void *paramt){
	char cmd[128]={0x0};
	static int count=0;
	sprintf(cmd, "echo str[%d]%s >> /var/tmp/cgic", count++, (char*)paramt);
	system(cmd);
	return ERR_NOERROR;
}

int set_num_test(void *paramt){
	char cmd[128]={0x0};
	static int count=0;
	sprintf(cmd, "echo int[%d]%d >> /var/tmp/cgic", count++, *(int*)paramt);
	system(cmd);
	return ERR_NOERROR;
}


struct mib_operations operations_table[]=
{
	/*{"name",		type,		init_type, 		index, 		get, 				assert, 	set}*/
	{"cpuUsed",		MIB_STR,	INIT_FLAG_NULL,	0,			cpu_used_percent,	NULL,		set_str_test},
	{"ramUsed",		MIB_STR,	INIT_FLAG_NULL,	0,			ram_used_percent,	NULL,		set_str_test},
	{"setNum",		MIB_NUM,	INIT_FLAG_NULL,	0,			NULL,	NULL,		set_num_test},
	{"setStr",		MIB_STR,	INIT_FLAG_NULL,	0,			NULL,	NULL,		set_str_test},
//	{"arpTable",	MIB_NUM,	INIT_FLAG_NULL,	0,	ram_used_percent,	NULL,	NULL},
//	{"req_mode", MIB_NUM,	INIT_FLAG_NULL, 0,	NULL,	NULL,	NULL},

	{NULL,	MIB_NUM,	INIT_FLAG_NULL, 0, NULL, NULL, NULL}
};

#endif//OPERATIONS_H
