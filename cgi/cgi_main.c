/*===============================================================
*	Copyright (C) 2020 All rights reserved.
*	
*	Filename：cgi_main.c
*	Author：julian
*	Date：2020-01-12
*	Discription:
*	
*	release notes：
*
================================================================*/
//#include "cgi_main.h"
#include <stdio.h>
#include <stdlib.h>

#include "cgic.h"
#include "utils.h"
#include "dispatch.h"
#include "err.h"
#define RET_CGI_HEAD() printf("Content-Type=text/html;charset=utf-8\n\n")
int cgiMain(void)
{
	RET_CGI_HEAD();
//	printf("{\"__DATE__\":\"%s\",\"__TIME__\":\"%s\",\"__FILE__\":\"%s\",\"__LINE__\":\"%d\"}", 
//                            __DATE__, __TIME__, __FILE__, __LINE__);
//	printf("[%s %s] file: %s line: %d \n", __DATE__, __TIME__, __FILE__, __LINE__);

	char *json_str = cJSON_Print(cgiJSONObject);
	REQ_MODE_T req_mode = REQ_NOSPT;
	RET_ERR_T ret = ERR_INVALID_VALUE;
	char json_buf[2048] = {0};
//	printf("%s", json_str);
//	return 0;
	
	if(NULL != json_str){
		free(json_str);
	}
	cJSON *p_req_mode = cJSON_GetObjectItem(cgiJSONObject, "req_mode");
	if(p_req_mode == NULL )
	{
		JSON_RET(ERR_INVALID_VALUE);
		return -1;
	}
	dlog_debug("p_req_mode: %s \n", p_req_mode->valuestring);
	if(strcmp(p_req_mode->valuestring, "get")==0)
	{
		req_mode = REQ_GET;
	}
	else if(strcmp(p_req_mode->valuestring, "set")==0)
	{
		req_mode = REQ_SET;
	}
	else
	{	
		JSON_RET(ERR_INVALID_TYPE);
		return -1;
	}
	switch(req_mode)
	{
		case REQ_GET:
			ret = get_jsonpkt(cgiJSONObject, json_buf, sizeof(json_buf));
			if(ret == ERR_NOERROR)
			{
				dlog_debug("get response:%s", json_buf);
				//build_ret_packet(trsfb, json_buf);
				printf("%s", json_buf);
			}
			else
			{
				JSON_RET(ret);
			}
			break;
			
		case REQ_SET:
			ret = set_jsonpkt(cgiJSONObject);
			JSON_RET(ret);
			break;
			
		default:
			JSON_RET(ret);
	}
	fflush(stdout);

	return 0;
}
