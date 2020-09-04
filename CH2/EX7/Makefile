all: quant clean

OFILES= quant.o

libquant.a:$(OFILES)
	ar rc $@ $?

quant: $(OFILES)
	g++ $(OFILES) -o quant
	
clean:
	rm -f *.a *.o quant *~	
