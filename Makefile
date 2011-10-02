PKGS="talloc"
PKGCONFIG=pkg-config

CFLAGS:=`${PKGCONFIG} --cflags ${PKGS}`
LDFLAGS:=`${PKGCONFIG} --libs ${PKGS}`

####

OBJS=		\
	rng.o	\
	lcg.o

.DEFAULT: rng.a

rng.a: ${OBJS}
	ar rcs rng.a ${OBJS}

${OBJS} : rng.h rng-private.h
