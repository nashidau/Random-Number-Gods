PKGS="talloc"
PKGCONFIG=pkg-config

CFLAGS+=`${PKGCONFIG} --cflags ${PKGS}` -fPIC
LDFLAGS+=`${PKGCONFIG} --libs ${PKGS}` -lm -lpthread -lrt

####

LIB=librngod.so.0

OBJS=			\
	rngod.o		\
	constant.o	\
	dethread.o	\
	lcg.o		\
	randu.o		\
	sequence.o	\
	xorshift.o

LIBRNGH=		\
	constant.h	\
	dethread.h	\
	lcg.h		\
	sequence.h	\
	randu.h		\
	rng-private.h	\
	xorshift.h

TESTS=				\
	rngod_check.o		\
	constant_check.o	\
	dethread_check.o	\
	randu_check.o		\
	sequence_check.o	\
	xorshift_check.o

.DEFAULT: ${LIB} check
.PHONY : clean check fixme
.PRECIOUS: check

${LIB}: ${OBJS}
	${CC} -shared -Wl,-soname,$@ ${CFLAGS} -o $@ ${OBJS}

rngod.a: ${OBJS}
	ar rcs rngod.a ${OBJS}

install: ${LIB} rngod.pc checkrun
	mkdir -p /usr/local/include/rngod
	cp rngod.h /usr/local/include
	cp ${LIBRNGH} /usr/local/include/rngod
	rm -f /usr/local/lib/librngod*
	cp librngod.so.0 /usr/local/lib/
	ln -sf /usr/local/lib/librngod.so.0 /usr/local/lib/librngod.so
	mkdir -p /usr/local/lib/pkgconfig
	cp rngod.pc /usr/local/lib/pkgconfig

check: rngod.a ${TESTS}
	${CC} ${CFLAGS} -o check ${TESTS} rngod.a ${LDFLAGS} -lcheck

checkrun: check
	./check

fixme:
	egrep -i 'FIXME|XXX|TODO' *.[ch]

${OBJS} : rngod.h rng-private.h

clean:
	rm -f ${OBJS} ${LIB} rngod.a check
