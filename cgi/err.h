/*===============================================================
*	Copyright (C) 2020 All rights reserved.
*	
*	Filename：err.h
*	Author：julian
*	Date：2020-02-01
*	Discription:
*	
*	release notes：
*
================================================================*/
#ifndef _ERR_H
#define _ERR_H
typedef enum { 
	ERR_NOERROR=0, 
	ERR_BADVALUE=1,
	ERR_WRONGTYPE=2,
	ERR_NOTFOUND=3,
	ERR_MEMORY=4
}RET_ERR_T;
   
#endif //ERR_H
