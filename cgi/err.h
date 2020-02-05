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
	ERR_INVALID_VALUE=1,
	ERR_INVALID_TYPE=2,
	ERR_NOTFOUND=3,
	ERR_MEMORY=4,
	ERR_ACCESS_DENY=5
}RET_ERR_T;
   
#endif //ERR_H
