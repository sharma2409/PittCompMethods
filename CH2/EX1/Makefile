all: precision clean

OFILES= precision.o

libprecision.a:$(OFILES)
	ar rc $@ $?

precision: $(OFILES)
	g++ $(OFILES) -o precision
	
clean:
	rm -f *.a *.o precision *~
