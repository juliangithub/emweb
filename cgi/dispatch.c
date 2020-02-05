/*===============================================================
*	Copyright (C) 2020 All rights reserved.
*	
*	Filename：dispatch.c
*	Author：julian
*	Date：2020-02-01
*	Discription:
*	
*	release notes：
*
================================================================*/
#include "dispatch.h"
#include "err.h"
#include "utils.h"
#include "cJSON.h"
#include "conf.h"
#include "operations.h"

static MIB_OPERATIONS_S *find_ops_handles(MIB_OPERATIONS_S *object, const char *string)	
{
	MIB_OPERATIONS_S *idx = object;
	
	while(idx->name != NULL){
		if(!strncasecmp(idx->name, string, MAX(strlen(idx->name),strlen(string)))){
			dlog_debug("found the cell name: %s", idx->name);
			return idx;
		}
		idx++;
	}

	return NULL;
}

static void json_set_init(int init_flag)
{

	if(init_flag == INIT_FLAG_NULL){
		return;
	}
	else if(init_flag == INIT_FLAG_WIFI){
		//system("reinit_wifi");
	}
	else if(init_flag == INIT_FLAG_WAN){
		//system("reinit_wan");
	}
	else if(init_flag == INIT_FLAG_MODE){
		//system("change_mode");
	}
	else
	{
		//system("reinit_all");
	}

}

int set_jsonpkt(cJSON *object)
{
	RET_ERR_T json_ret = ERR_NOERROR;
	int mib_ret = 0;
	cJSON *element = NULL;
	char setVal[MIB_VAL_MAX_LEN] = {0};
	MIB_OPERATIONS_S *idx = NULL;
	int init_flag = 0;
	
	
	for(idx = operations_table; (idx->name != NULL); idx++)
	{
		element = cJSON_GetObjectItem(object, idx->name);
		if(element == NULL){
			continue;
		}
		
		dlog_info("set key:%s, mib_index=%d, valuestring:%s, valueint:%d", 
			element->string, idx->mib_index, element->valuestring, element->valueint);
		if(element->type == cJSON_String && idx->type == MIB_STR)
		{
			strncpy(setVal, element->valuestring, sizeof(setVal));
		}
		else if(idx->type == MIB_NUM)
		{
			if(element->type == cJSON_Number)
			{
				memcpy(setVal, &(element->valueint), sizeof(int));
			}
			else if (element->type == cJSON_String && element->valuestring != NULL)
			{
				element->valueint = atoi(element->valuestring);
				memcpy(setVal, &(element->valueint), sizeof(int));
			}
		}
		else
		{
			json_ret = ERR_INVALID_VALUE;
			dlog_err("invalid value!!!");
			return json_ret;
		}

		//if this mib unit need  some special step first. eg,check parameter.
		if(idx->mib_assert != NULL)
		{
			mib_ret = idx->mib_assert((void *)setVal);
			if(mib_ret != ERR_NOERROR)
			{
				json_ret =  ERR_INVALID_VALUE;
				return json_ret;
			}
		}

		if(idx->mib_set!= NULL){
			//some mib unit set no so simply as to update a value.need some special process.
			mib_ret = idx->mib_set((void *)setVal);
			if(mib_ret != ERR_NOERROR)
			{
				dlog_err("mib_set failed");
				json_ret = mib_ret;
				return json_ret;
			}
		}
		else
		{
			mib_ret = nvram_set(idx->mib_index, (void *)setVal);
			if(mib_ret != ERR_NOERROR)	
			{
				dlog_err("mib_set failed");
				json_ret = mib_ret;
				return json_ret;
			}
		}
		//set init_flag.
		init_flag |= idx->init_type;
	}
	dlog_info("set_jsonpkt SUCCESS");
	json_set_init(init_flag);
	return json_ret;
}


int get_jsonpkt(cJSON *json_obj, char *json_str, int max_length)
{
	RET_ERR_T json_ret = ERR_NOERROR;
	int mib_ret = 0;
	int nBytes=0;
	char mibVal[MIB_VAL_MAX_LEN] = {0};
	MIB_OPERATIONS_S *idx = NULL;
	cJSON *c = NULL;

	nBytes += snprintf(json_str+nBytes, max_length, "{");
	for(c=json_obj->child; (c!=NULL&&c->string!=NULL&&c->type!=cJSON_Object); c=c->next)
	{
		if(!strncasecmp(c->string, "req_mode", MAX(strlen(c->string),strlen("req_mode"))))
		{
			continue;
		}
			
		idx = find_ops_handles(operations_table, c->string);

		if(idx == NULL)
		{
			dlog_err("no such json key:%s", c->string);
			nBytes += snprintf(json_str+nBytes, max_length, JSON_GET_RET, c->string, "unknow");
			continue;
		}
		
		memset(mibVal, 0x00, sizeof(mibVal));
				
		if(idx->mib_get!= NULL)
		{
			//some mib unit get no so simply as to update a value.need some special process.
			mib_ret = idx->mib_get((void*)mibVal);
		}
		else
		{
			mib_ret = nvram_get(idx->mib_index, (void *)mibVal);
		}

		if(mib_ret != ERR_NOERROR)
		{
			dlog_err("apmib_get Faild MIB index :%d", idx->mib_index);
			json_ret = ERR_MEMORY;
			return json_ret;
		}
		else
		{
			if(idx->type == MIB_NUM)
			{	
				int intVal = 0;
				memcpy(&intVal, mibVal, sizeof(intVal));
				sprintf(mibVal, "%d", intVal);
			}
			
			nBytes += snprintf(json_str+nBytes, max_length, JSON_GET_RET, idx->name, mibVal);
		}
	}

	
	if(nBytes <= 1){
		return ERR_NOTFOUND;
	}
	else{
		snprintf(json_str+nBytes-1, max_length, "}");
		return json_ret;
	}
}

