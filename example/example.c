#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"clogger/clogger.h"

int main(int argc, char **argv)
{
	Logger *logger=logger_init(argv[1], LOG_DBG);

	logger_msg(logger, LOG_DBG,
			"A debug message!\n");
	logger_msg(logger, LOG_WRN,
			"A warning msg!\n");
	logger_msg(logger, LOG_ERR,
			"An error message\n");

	logger_deinit(logger);
}
