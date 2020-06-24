all: example.o

example.o: example.c
	${COMPILER} -I${COMPILE_PATH} ${COMPILER_FLAGS} -c example.c

clean:
	rm -f *.o
