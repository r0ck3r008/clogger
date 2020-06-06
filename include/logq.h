#ifndef LOGQ_H
#define LOGQ_H

#include<stdarg.h>

#include"logger.h"

typedef struct Log
{
	char *log;
	LOG_LVL lvl;
	struct Log *next;
} Log;

typedef struct Logque
{
	Log *start, *end;
} Logque;

Logque *logque_init();
void logque_push(Logque *, char *, LOG_LVL);
Log *logque_pop(Logque *);
void logque_deinit(Logque *);

#endif
