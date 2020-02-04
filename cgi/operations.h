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
struct mib_operations operations_table[]=
{
	/*	{"name",	mib_type,	INIT_FLAG_T, mibindex, get_func, set_pre_func, set_func}*/
	{"cpuUsed",	MIB_STR,	INIT_FLAG_NULL,	0,	cpu_used_percent,	NULL,	NULL},
	{"ramUsed",	MIB_STR,	INIT_FLAG_NULL,	0,	ram_used_percent,	NULL,	NULL},
//	{"req_mode", MIB_NUM,	INIT_FLAG_NULL, 0,	NULL,	NULL,	NULL},

	{NULL,	MIB_NUM,	INIT_FLAG_NULL, 0, NULL, NULL, NULL}
};

#endif//OPERATIONS_H
