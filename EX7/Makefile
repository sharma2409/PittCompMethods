all: plus clean

OFILES= main.o add.o print.o parse.o

libplus.so:$(OFILES)
	ar rc $@ $?

plus: $(OFILES)
	g++ $(OFILES) -o plus
	
clean:
	rm -f *.a *.o plus *~	
