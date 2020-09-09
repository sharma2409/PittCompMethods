all: plus 

OFILES= plus.o

libplus.so:$(OFILES)
	ar rc $@ $?

plus: $(OFILES)
	g++ $(OFILES) -o plus

clean:
	rm -f *.a *.o plus *~	
