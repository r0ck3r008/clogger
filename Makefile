COMPILER := gcc
COMPILER_FLAGS := '-g -Wall -Werror -fpic'
COMPILE_PATH := ${shell pwd}/include
LINKER_FLAGS := -shared

ALL_OBJS := entrypoint/*.o logger/*.o

all: libclogger.so
	${COMPILER} example/example.o -L${shell pwd} -lclogger -o example.out
	make clean_objs

libclogger.so: entrypoint_objs logger_objs example_objs
	${COMPILER} ${ALL_OBJS} ${LINKER_FLAGS} -o libclogger.so

entrypoint_objs:
	COMPILER=${COMPILER} COMPILE_PATH=${COMPILE_PATH} \
		 COMPILER_FLAGS=${COMPILER_FLAGS} make -C entrypoint/

logger_objs:
	COMPILER=${COMPILER} COMPILE_PATH=${COMPILE_PATH} \
		 COMPILER_FLAGS=${COMPILER_FLAGS} make -C logger/

example_objs:
	COMPILER=${COMPILER} COMPILE_PATH=${COMPILER_PATH} \
		 COMPILER_FLAGS=${COMPILER_FLAGS} make -C example/

clean_objs:
	make -C entrypoint/ clean
	make -C logger/ clean
	make -C example/ clean

clean: clean_objs
	rm -f *.so
	rm -f *.out
