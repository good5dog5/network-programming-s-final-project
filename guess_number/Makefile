include ../Make.defines

PROGS =	guessnumcli guessnumserv

.PHONY: all guessnumcli guessnumserv

all: ${PROGS}


guessnumcli:	guessnumcli.o
		${CC} ${CFLAGS} -o $@ guessnumcli.o ${LIBS}
guessnumserv:	guessnumserv.o
		${CC} ${CFLAGS} -o $@ guessnumserv.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES} *.o *.log
