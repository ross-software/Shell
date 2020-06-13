SRC = mm.c
OBJ = ${SRC:.c=.o}
BIN = ../bin/mmenu

LIBS = -lX11
INCDIRS = -I/opt/X11/include/X11/ -I/opt/X11/include/
LIBDIRS = -L/opt/X11/lib/X11/ -L/opt/X11/lib/

run: ${BIN}
	${BIN}

all: ${BIN}

${BIN}: ${OBJ}
	gcc -o $@ ${OBJ} ${INCDIRS} ${LIBDIRS} ${LIBS}

${OBJ}: ${SRC}
	gcc -o $@ -c $^ ${INCDIRS} ${LIBDIRS} ${LIBS}
