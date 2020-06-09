#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#include"logchild.h"

Logchild *logchild_init(int sock, char *path, LOG_LVL lvl)
{
	Logchild *lchild=calloc(1, sizeof(Logchild));
	if(lchild==NULL) {
		fprintf(stderr, "[-]LOGCHILD: Error in allocating memory!\n");
		return NULL;
	}
	lchild->sock=sock;
	lchild->lvl=lvl;
	if(!strcmp("-", path)) {
		lchild->outf=stdout;
	} else if((lchild->outf=fopen(path, "w"))==NULL) {
		fprintf(stderr, "[-]LOGCHILD: Fopen: %s\n", strerror(errno));
		return NULL;
	}

	return lchild;
}

int logchild_pretty_p(Logchild *lchild, char *buf)
{
	LOG_LVL loglvl=(LOG_LVL)strtol(strtok(buf, ":"), NULL, 10);
	if(loglvl < lchild->lvl)
		return 1;
	switch(loglvl) {
	case LOG_DBG:
		fprintf(lchild->outf, "[DBG] ");
		break;
	case LOG_WRN:
		fprintf(lchild->outf, "[WRN] ");
		break;
	case LOG_ERR:
		fprintf(lchild->outf, "[ERR] ");
		break;
	default:
		fprintf(lchild->outf, "LOGCHILD: Unknown log level!\n");
		return 0;
	}
	fprintf(lchild->outf, "%s\n", strtok(NULL, ":"));

	return 1;
}

void logchild_exec(Logchild *lchild)
{
	while(1) {
		char buf[512];
		if(read(lchild->sock, buf, sizeof(char)*512)<0) {
			fprintf(lchild->outf, "LOGCHILD: Read: %s\n",
							strerror(errno));
			break;
		}
		if(!strcmp("EXIT", buf))
			break;
		else if(!logchild_pretty_p(lchild, buf))
			break;
	}

	logchild_deinit(lchild);
}

void logchild_deinit(Logchild *lchild)
{
	close(lchild->sock);
	fclose(lchild->outf);
	free(lchild);
}
