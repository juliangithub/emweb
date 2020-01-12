#WALL=-g -Wall -Waggregate-return -Wmissing-declarations  -Wmissing-prototypes -Wredundant-decls -Wshadow -Wstrict-prototypes -Winline 
#CPPFLAGS=-I../../target-install/message/usr/include
#LDFLAGS=-L../../target-install/message/usr/lib -L../../target-install/nvram/usr/lib
#LIBS= -lmessage -lcrypt -lnvram
OBJ= cgic.o cgi_main.o 

all: json.cgi
#	echo $(shell pwd)

json.cgi: $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o json.cgi ${LDFLAGS} ${LIBS}

install:
#	cp libcgic.a /usr/local/lib
#	cp cgic.h /usr/local/include
#	@echo libcgic.a is in /usr/local/lib. cgic.h is in /usr/local/include.




clean:
	rm -rf *.o *.a json.cgi 
	rm -f ../www/cgi-bin/json.cgi


