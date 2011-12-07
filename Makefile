PKGS="talloc"
PKGCONFIG=pkg-config

CFLAGS+=`${PKGCONFIG} --cflags ${PKGS}`
LDFLAGS+=`${PKGCONFIG} --libs ${PKGS}`

####

LIB=librngod.so.0

OBJS=			\
	rng.o		\
	constant.o	\
	dethread.o	\
	lcg.o

LIBRNGH=		\
	rng.h		\
	lcg.h		\
	dethread.h	\
	rng-private.h

TESTS=				\
	rng_check.o		\
	constant_check.o	\
	dethread_check.o

.DEFAULT: rng.a ${LIB} check

${LIB}: ${OBJS}
	${CC} -shared -Wl,-soname,$@ ${CFLAGS} -o $@ ${OBJS}

rng.a: ${OBJS}
	ar rcs rng.a ${OBJS}

install: ${LIB} rngod.pc
	mkdir -p /usr/local/include/rngod
	cp ${LIBRNGH} /usr/local/include/rngod
	rm -f /usr/local/lib/librngod*
	cp librngod.so.0 /usr/local/lib/
	ln -sf /usr/local/lib/librngod.so.0 /usr/local/lib/librngod.so
	mkdir -p /usr/local/lib/pkgconfig
	cp rng.pc /usr/local/lib/pkgconfig

check: rng.a ${TESTS}
	${CC} ${CFLAGS} -o check ${TESTS} rng.a ${LDFLAGS} -lcheck

${OBJS} : rng.h rng-private.h

clean:
	rm ${OBJS} ${LIB} rng.a
