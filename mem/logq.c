#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"logq.h"

Logque *logque_init()
{
	Logque *logq=calloc(1, sizeof(Logque));
	if(logq==NULL) {
		fprintf(stderr, "[-]LOGQ: Error in allocating memory!\n");
		_exit(-1);
	}

	return logq;
}

void logque_push(Logque *logq, char *fmt, va_list args)
{
	Log *node=calloc(1, sizeof(Log));
	va_copy(node->args, args);
	node->fmt=fmt;

	if(logq->start==NULL)
		logq->start=node;
	else
		logq->end->next=node;
	logq->end=node;
}

Log *logque_pop(Logque *logq)
{
	if(logq->start==NULL)
		return NULL;
	Log *curr=logq->start;
	logq->start=curr->next;

	return curr;
}

void logque_deinit(Logque *logq)
{
	Log *curr=logq->start->next;
	while(logq->start->next!=NULL) {
		logq->start->next=curr->next;
		free(curr->fmt);
		va_end(curr->args);
		free(curr);
	}
	free(logq->start->fmt);
	va_end(logq->start->args);
	free(logq->start);
	free(logq);
}
