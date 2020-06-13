SRC = mm.c
OBJ = ${SRC:.c=.o}
BIN = ../bin/mmenu

LIBS = -lX11

INCDIRS_OSX = -I/opt/X11/include/X11/ -I/usr/X11R6/include/
LIBDIRS_OSX = -L/opt/X11/lib/X11/ -L/usr/X11R6/lib/

INCDIRS = -I/usr/X11R6/include/X11/ -I/opt/X11/include/
LIBDIRS = -L/usr/X11R6/lib/X11/ -L/opt/X11/lib/

run: ${BIN}
	${BIN}

all: ${BIN}

macos: ${SRC}
	gcc -o ${OBJ} -c $^ ${INCDIRS_OSX} ${LIBDIRS_OSX} ${LIBS}

${BIN}: ${OBJ}
	gcc -o $@ ${OBJ} ${INCDIRS} ${LIBDIRS} ${LIBS}

${OBJ}: ${SRC}
	gcc -o $@ -c $^ ${INCDIRS} ${LIBDIRS} ${LIBS}
