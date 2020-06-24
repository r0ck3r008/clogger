#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>

#include"logchild.h"
#include"logger.h"

Logger *logger_init(char *path, LOG_LVL lvl)
{
	Logger *logger=malloc(sizeof(Logger));
	if(logger==NULL) {
		fprintf(stderr, "[-]LOGGER: Error in allocating memory!\n");
		return NULL;
	}
	int socks[2]={0};
	if(socketpair(AF_UNIX, SOCK_STREAM, 0, socks)<0) {
		fprintf(stderr, "[-]LOGGER: Socket: %s\n", strerror(errno));
		return NULL;
	}

	pid_t pid=fork();
	if(!pid) {
		//child
		close(socks[0]);
		Logchild *lchild=NULL;
		if((lchild=logchild_init(socks[1], path, lvl))==NULL)
			_exit(-1);
		logchild_exec(lchild);
		_exit(1);
	} else if(pid<0) {
		//error
		fprintf(stderr, "[-]LOGGER: Fork: %s\n", strerror(errno));
		return NULL;
	} else {
		//child
		close(socks[1]);
		logger->sock=socks[0];
	}

	return logger;
}

void logger_msg(Logger *logger, LOG_LVL lvl, char *fmt, ...)
{
	char buf[512];
	va_list args;
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	if(write(logger->sock, buf, sizeof(char)*512)<0) {
		fprintf(stderr, "[-]LOGGER: Write: %s\n", strerror(errno));
		_exit(-1);
	}
	va_end(args);
}

void logger_deinit(Logger *logger)
{
	if(write(logger->sock, "EXIT", sizeof(char)*512)<0) {
		fprintf(stderr, "[-]LOGGER: Write: %s\n", strerror(errno));
		_exit(-1);
	}

	close(logger->sock);
}
