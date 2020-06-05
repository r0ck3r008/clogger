#ifndef LOGQ_H
#define LOGQ_H

#include<stdarg.h>

typedef struct Log
{
	char *fmt;
	va_list args;
	struct Log *next;
} Log;

typedef struct Logque
{
	Log *start, *end;
} Logque;

Logque *logque_init();
void logque_push(Logque *, char *, va_list);
Log *logque_pop(Logque *);
void logque_deinit(Logque *);

#endif
