all: entrypoint.o

entrypoint.o: entrypoint.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c entrypoint.c

clean:
	rm -f *.o
