/*===============================================================
*	Copyright (C) 2020 All rights reserved.
*	
*	Filename：config.h
*	Author：julian
*	Date：2020-02-03
*	Discription:
*	
*	release notes：
*
================================================================*/
#ifndef _CONFIG_H
#define _CONFIG_H

int nvram_set(unsigned int index, void * paramt); 
 int nvram_get(unsigned int index, void * paramt);  
#endif //CONFIG_H
