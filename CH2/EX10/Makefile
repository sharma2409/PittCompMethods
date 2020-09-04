all: eigen clean

OFILES= eigen.o

libeigen.a:$(OFILES)
	ar rc $@ $?

eigen: $(OFILES)
	g++ $(OFILES) -o eigen
	
clean:
	rm -f *.a *.o eigen *~	
