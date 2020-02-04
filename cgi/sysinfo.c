/*===============================================================
*	Copyright (C) 2018 All rights reserved.
*	
*	Filename：sysinfo.c
*	Author：julian.chen
*	Date：2018-09-04
*	Discription:
*	
*	release notes：
*
================================================================*/
#include "sysinfo.h"
#include "utils.h"

#define NONE_CLIENT		"\"0.0.0.0\":\"00:00:00:00:00:00\""
//#define NONE_CLIENT		"\"\":\"\""

static int parse_arp_table(char **ppStart, unsigned long *size, char *ip, char *mac, int *flag, char *device)
{
	static int num = 11;
	#if 1
		sprintf(ip, "192.168.88.%d", num);
		sprintf(mac, "a4:a8:0f:11:22:%d", num);
	#else
	struct arp_entry entry;
	u_int8_t empty_haddr[16]; 

	unsigned long tmp_expires = 0;
     memset(empty_haddr, 0, 16); 
	if ( *size < sizeof(entry) )
		return -1;

	entry = *((struct dhcpOfferedAddr *)*ppStart);
	*ppStart = *ppStart + sizeof(entry);
	*size = *size - sizeof(entry);

	if (entry.expires == 0)
		return 0;

	if(!memcmp(entry.chaddr, empty_haddr, 16)){
		//fprintf(stderr, "got a unavailable entry for ip=%s\n",inet_ntoa(*((struct in_addr *)&entry.yiaddr)));
		return 0;
	}
	strcpy(ip, inet_ntoa(*((struct in_addr *)&entry.yiaddr)) );
	snprintf(mac, 20, "%02x:%02x:%02x:%02x:%02x:%02x",
			entry.chaddr[0],entry.chaddr[1],entry.chaddr[2],entry.chaddr[3],
			entry.chaddr[4], entry.chaddr[5]);
	
	if(entry.expires == 0xffffffff)
	{
		sprintf(liveTime, "%s", "Always");
	}
	else
	{
		tmp_expires= (unsigned long)ntohl(entry.expires);
		
		sprintf(liveTime, "%lu:%lu:%lu", 
			(tmp_expires/60)/60, (tmp_expires/60)%60, tmp_expires%60);
	}
	sprintf(hostname, "%s", entry.hostname);
	#endif
	return 1;
}



int get_arp_list_json(char *json_buf, int buf_size)
{
	FILE *fp;
	int nBytesSent=0;
	int element=0, ret;
	char ipAddr[40], macAddr[40], liveTime[80], hostname[80],*buf=NULL, *ptr, tmpBuf[100];
	struct stat status;
	int pid;
	unsigned long fileSize=0;
	char json_item[128];
	int item_len;

	int flag = 0;
	char device[65]={0x0};
	
	if ( stat(_ARP_LIST, &status) < 0 )
		goto err;

	fileSize=status.st_size;
	buf = malloc(fileSize);
	if ( buf == NULL )
		goto err;
	fp = fopen(_ARP_LIST, "r");
	if ( fp == NULL )
		goto err;

	fread(buf, 1, fileSize, fp);
	fclose(fp);

	ptr = buf;
	
	while (element < 5) {
		ret = parse_arp_table(&ptr, &fileSize, ipAddr, macAddr, &flag, device);

		if (ret < 0 )
			break;
		if (ret == 0)
			continue;
		if(element == 0)
		{
			item_len = snprintf(json_item, sizeof(json_item), 
				"\"%s\":\"%s\"", ipAddr, macAddr);
		}
		else
		{
			item_len = snprintf(json_item, sizeof(json_item), 
				",\"%s\":\"%s\"", ipAddr, macAddr);
		}

		if(item_len > buf_size-nBytesSent-2)
		{
			printf("buffer space is not enough ,drop items.");
			break;
		}
		else{
			nBytesSent += snprintf(json_buf+nBytesSent, buf_size-nBytesSent,
				"%s", json_item);
		}
		element++;
	}
err:
	if (element == 0) {
		nBytesSent += snprintf(json_buf, buf_size-nBytesSent, 				
				NONE_CLIENT
				);
	}
	
	if (buf)
		free(buf);

	return nBytesSent;
}

int cpu_used_percent(void *paramt)
{
	FILE *fp = NULL;
	char line[128] = {0};
	unsigned long user=0, system=0, nice=0, idle=0;
	unsigned long total = 0;
	
	if((fp = popen("cat /proc/stat | grep cpu0", "r")) != NULL){
		fgets(line, sizeof(line), fp);
		pclose(fp);
		sscanf(line, "%*s %lu %lu %lu %lu", &user, &system, &nice, &idle);
	}
	
	total = user + system + nice + idle;
	if(total == 0) return RET_FAILD;

	sprintf(paramt, "%.2lf", 100.00*(user + system + nice)/total);
	return RET_SUCCESS;
}


int ram_used_percent(void *paramt)
{
	FILE *fp = NULL;
	unsigned long total = 0;
	unsigned long used = 0;
	char line[128] = {0};
	
	if((fp = popen("free | grep Mem:", "r")) != NULL){
		fgets(line, sizeof(line), fp);
		pclose(fp);
		sscanf(line, "%*s %lu %lu", &total, &used);
	}
	
	if(total == 0) return RET_FAILD;
	sprintf(paramt, "%.2lf", 100.00*used/total);
	return RET_SUCCESS;
}


