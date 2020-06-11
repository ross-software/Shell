SRC = rad.c
OBJ = ${SRC:.c=.o}
BIN = ../bin/radian

LIBS = -lX11

all: ${BIN}

${BIN}: ${OBJ}
	gcc -o $@ ${OBJ} ${LIBS}

${OBJ}: ${SRC}
	gcc -o $@ -c $^ ${LIBS}
