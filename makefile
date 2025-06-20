TARGET = screen-thing
SOURCES = src/screen-thing.c src/chromatic.c src/sb.c
HEADERS = src/chromatic.h src/sb.h

${TARGET}: ${SOURCES} ${HEADERS} 
	clang ${SOURCES} -o ${TARGET} -Wall -Werror -pedantic -std=c99 -g -D_POSIX_C_SOURCE=199309L
