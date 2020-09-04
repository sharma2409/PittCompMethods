all: identity clean

OFILES= identity.o

libidentity.a:$(OFILES)
	ar rc $@ $?

identity: $(OFILES)
	g++ $(OFILES) -o identity
	
clean:
	rm -f *.a *.o identity *~	
