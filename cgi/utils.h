/*===============================================================
 *	Copyright (C) 2018 All rights reserved.
 *	
 *	Filename：utils.h
 *	Author：julian
 *	Date：2018-07-27
 *	Discription:
 *	
 *	release notes：
 *
 ================================================================*/
#ifndef _UTILS_H
#define _UTILS_H
#include "dlog.h"
typedef enum
{
	RET_SUCCESS = 0,
	RET_FAILD = 1,
	RET_INVALID_PARMT = 2,
	RET_ERR_GENERAL = 3,
}RET;

/** @def MAX(a, b)
  Computers the maximum of a and b. */
#define MAX(a,b) ((a) > (b) ? (a) : (b))

/** @def MIN(a, b)
  Computers the minimum of a and b. */
#define MIN(a,b) ((a) > (b) ? (b) : (a))

static inline int dump_buf(unsigned char *packet, int buf_len, char *filename, int line)
{
	printf("*****************%s %d*********************\n", filename, line);
	printf("%s \n", packet);
	printf("**************************************\n");
}

int get_pid(char *filename);
void sleep_interval_dynamic();


//================================================================

typedef enum { 
	MIB_NUM = 0,
	MIB_STR=1, 
}JSON_CELL_TYPE_T;

typedef enum{
	INIT_FLAG_NULL=0x00, 
	INIT_FLAG_ALL=0x01, 
	INIT_FLAG_WIFI=0x02, 
	INIT_FLAG_WAN=0x04, 
	INIT_FLAG_MODE=0x08
}INIT_FLAG_T;

typedef int (*MIB_ASSERT_CB)(void* paramt);
typedef int (*MIB_SET_CB)(void* paramt);
typedef int (*MIB_GET_CB)(void* paramt);

typedef struct mib_operations{
	const char *name;
	int type;
	int init_type;
	unsigned int mib_index;
	MIB_GET_CB mib_get;
	MIB_ASSERT_CB mib_assert;
	MIB_SET_CB mib_set;
}MIB_OPERATIONS_S,*DATA_OPERATIONS_TP;

#define JSON_GET_RET	"\"%s\":\"%s\","
//	printf("%s", (err_code==0)?"{\"result\":\"success\"}":"{\"result\":\"fail\"}"); 
//	printf("%s", (err_code==0)?"{\"result\":\"success\"}":"{\"result\":\"fail\",\"file\":"__FILE__"\"line\":"__LINE__"}"); }

#define JSON_RET(err_code) { \
		printf("%s", (err_code==0)?"{\"result\":\"success\"}":"{\"result\":\"fail\"}"); }


#endif //UTILS_H
