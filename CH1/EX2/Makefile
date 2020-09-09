all: exp clean

OFILES= exp.o

libexp.a:$(OFILES)
	ar rc $@ $?

exp: $(OFILES)
	g++ $(OFILES) -o exp
	
clean:
	rm -f *.a *.o exp *~	
