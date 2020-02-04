/*===============================================================
*	Copyright (C) 2020 All rights reserved.
*	
*	Filename：dispatch.h
*	Author：julian
*	Date：2020-02-01
*	Discription:
*	
*	release notes：
*
================================================================*/
#ifndef _DISPATCH_H
#define _DISPATCH_H
   
typedef enum { 
	REQ_NOSPT = 0,
	REQ_GET=1, 
	REQ_SET=2
}REQ_MODE_T;

#define MIB_VAL_MAX_LEN 128
#endif //DISPATCH_H
