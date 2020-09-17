all: EX7 

OFILES= EX7.o

EX7: libEX7.a
	g++ -L. -lEX7 -o EX7

libEX7.a:$(OFILES)
	ar rc $@ $?
clean:
	rm -f *.a *.o EX7 *~	
