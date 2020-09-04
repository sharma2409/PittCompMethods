all: threepi clean

OFILES= threepi.o

libthreepi.a:$(OFILES)
	ar rc $@ $?

threepi: $(OFILES)
	g++ $(OFILES) -o threepi
	
clean:
	rm -f *.a *.o threepi *~	
