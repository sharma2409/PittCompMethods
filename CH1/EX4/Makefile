all: foo

OFILES= foo.o
libfoo.a:$(OFILES)
	ar rc $@ $?

foo: $(OFILES)
	g++ $(OFILES) -o foo

clean:
	rm -f *.a *.o foo *~	
