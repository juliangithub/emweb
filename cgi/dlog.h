/*===============================================================
*	Copyright (C) 2018 All rights reserved.
*	
*	Filename：dlog.h
*	Author：julian
*	Date：2018-08-05
*	Discription:
*	
*	release notes：
*
================================================================*/
#ifndef _DLOG_H
#define _DLOG_H
#include <stdio.h>
#define HEAD				"\e["// or "\033["
#define DISPLAY_DEF			"0"
#define DISPLAY_BOLD		"1"
#define DISPLAY_BLINK		"5"
#define DISPLAY_UNLINE		"24"

#define COLOR_FT_BLACK			";30m"
#define COLOR_FT_RED			";31m"
#define COLOR_FT_GREEN			";32m"
#define COLOR_FT_YELLOW			";33m"
#define COLOR_FT_BLUE			";34m"
#define COLOR_FT_PURPLE			";35m"
#define COLOR_FT_CYAN			";36m"
#define COLOR_FT_WHITE			";37m"

#define COLOR_BG_NONE			""
#define COLOR_BG_BLACK			";40"
#define COLOR_BG_RED			";41"
#define COLOR_BG_GREEN			";42"
#define COLOR_BG_YELLOW			";43"
#define COLOR_BG_BLUE			";44"
#define COLOR_BG_PURPLE			";45"
#define COLOR_BG_CYAN			";46"
#define COLOR_BG_WHITE			";47"

#define ENDL                 "\e[0m\n"


#define DLOG_EN

#define dlog_warn(format, ...)   {\
		FILE *dlog; \
		dlog = fopen("/var/log/cgic/debug", "a"); \
		fprintf(dlog, "Warning:(%s %d )"format"\n", __FILE__, __LINE__,##__VA_ARGS__); \
		fclose(dlog); \
}

#define dlog_err(format, ...)   {\
		FILE *dlog; \
		dlog = fopen("/var/log/cgic/debug", "a"); \
		fprintf(dlog, "Error:(%s %d )"format"\n", __FILE__, __LINE__,##__VA_ARGS__); \
		fclose(dlog); \
}

//#define dlog_warn(format, ...)   fprintf(stderr, HEAD DISPLAY_BLINK COLOR_BG_NONE COLOR_FT_YELLOW"Warning(%s %d )"format ENDL, __FILE__, __LINE__,##__VA_ARGS__)
//#define dlog_err(format, ...)   fprintf(stderr, HEAD DISPLAY_BLINK COLOR_BG_NONE COLOR_FT_RED"Error(%s %d )"format ENDL, __FILE__, __LINE__,##__VA_ARGS__)
#ifdef DLOG_EN
//    #define dlog_trace()                  fprintf(stderr, HEAD DISPLAY_DEF COLOR_BG_NONE COLOR_FT_BLUE"Trace: (%s %s %d )" ENDL, __FILE__, __FUNCTION__, __LINE__)
//    #define dlog_debug(format, ...)   fprintf(stderr, HEAD DISPLAY_DEF COLOR_BG_NONE COLOR_FT_PURPLE"Debug:(%s %d )"format ENDL, __FILE__, __LINE__,##__VA_ARGS__)
//    #define dlog_info(format, ...)   fprintf(stderr, HEAD DISPLAY_DEF COLOR_BG_NONE COLOR_FT_GREEN"Info:(%s %d )"format ENDL, __FILE__, __LINE__,##__VA_ARGS__)

#define dlog_trace(format, ...)   {\
		FILE *dlog; \
		dlog = fopen("/var/log/cgic/debug", "a"); \
		fprintf(dlog, "Trace:(%s %s %d )"format"\n", __FILE__, __FUNCTION__, __LINE__); \
		fclose(dlog); \
}

#define dlog_debug(format, ...)   {\
		FILE *dlog; \
		dlog = fopen("/var/log/cgic/debug", "a"); \
		fprintf(dlog, "Debug:(%s %d )"format"\n", __FILE__, __LINE__,##__VA_ARGS__); \
		fclose(dlog); \
}

#define dlog_info(format, ...)   {\
		FILE *dlog; \
		dlog = fopen("/var/log/cgic/debug", "a"); \
		fprintf(dlog, "Info:(%s %d )"format"\n", __FILE__, __LINE__,##__VA_ARGS__); \
		fclose(dlog); \
}


#else
    #define dlog_trace()
    #define dlog_debug(format, ...)
    #define dlog_info(format, ...)
#endif

#endif //DLOG_H
