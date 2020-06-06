#ifndef _LOGGER_H
#define _LOGGER_H

#include<stdio.h>
#include<stdarg.h>

typedef enum LOG_LVL
{
	LOG_DBG,
	LOG_WRN,
	LOG_ERR
} LOG_LVL;

typedef struct Logger
{
	int sock;
} Logger;

Logger *logger_init(char *, LOG_LVL);
void logger_msg(Logger *, LOG_LVL, char *, ...);
void logger_deinit(Logger *);

#endif
