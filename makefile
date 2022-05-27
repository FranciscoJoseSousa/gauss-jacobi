CC = gcc
CFLAGS = -O3 -g3  -W -Wall -Wextra -Wuninitialized -Wstrict-aliasing -std=c11

seq:
	${CC} ${CFLAGS} jacobiseq.c -o jacobiseq.out -lm
	./jacobiseq.out

clean:
	rm -f acobiseq.out