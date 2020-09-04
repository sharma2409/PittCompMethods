all: quad clean

OFILES= quad.o

libquad.a:$(OFILES)
	ar rc $@ $?

quad: $(OFILES)
	g++ $(OFILES) -o quad
	
clean:
	rm -f *.a *.o quad *~	
