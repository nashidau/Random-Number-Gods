PKGS="talloc"
PKGCONFIG=pkg-config

CFLAGS+=`${PKGCONFIG} --cflags ${PKGS}`
LDFLAGS+=`${PKGCONFIG} --libs ${PKGS}`

####

OBJS=			\
	rng.o		\
	constant.o	\
	dethread.o	\
	lcg.o

TESTS=				\
	rng_check.o		\
	constant_check.o	\
	dethread_check.o

.DEFAULT: rng.a check

rng.a: ${OBJS}
	ar rcs rng.a ${OBJS}

check: rng.a ${TESTS}
	${CC} ${CFLAGS} -o check ${TESTS} rng.a ${LDFLAGS} -lcheck

${OBJS} : rng.h rng-private.h

clean:
	rm ${OBJS} rng.a
