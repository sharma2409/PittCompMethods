all: EX6

OFILES= EX6.o

EX6: libEX6.a
	g++ $(OFILES) -o EX6
	
libEX6.a:$(OFILES)
	ar rc $@$?	
	
clean:
	rm -f *.a *.o EX6 *~	
