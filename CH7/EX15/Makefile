all: EX15

OFILES= EX15.o

EX15: libEX15.a
	g++ $(OFILES) -o EX15
		
libEX15.a:$(OFILES)
	ar rc $@$?

clean:
	rm -f *.a *.o EX15 *~
