COMPILER := gcc
COMPILER_FLAGS := '-g -Wall -Werror -fpic'
COMPILE_PATH := ${shell pwd}/include
LINKER_FLAGS := -shared

ALL_OBJS := entrypoint/*.o logger/*.o

all: libclogger.so

libclogger.so: entrypoint_objs logger_objs
	${COMPILER} ${ALL_OBJS} ${LINKER_FLAGS} -o libclogger.so
	make clean_objs

entrypoint_objs:
	COMPILER=${COMPILER} COMPILE_PATH=${COMPILE_PATH} \
		 COMPILER_FLAGS=${COMPILER_FLAGS} make -C entrypoint/

logger_objs:
	COMPILER=${COMPILER} COMPILE_PATH=${COMPILE_PATH} \
		 COMPILER_FLAGS=${COMPILER_FLAGS} make -C logger/

clean_objs:
	make -C entrypoint/ clean
	make -C logger/ clean

clean: clean_objs
	rm -f *.so
