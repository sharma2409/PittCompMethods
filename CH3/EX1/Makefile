all: crystal 

OFILES= crystal.o

crystal: libcrystal.a
	g++ -L. -lcrystal -o crystal

libcrystal.a:$(OFILES)
	ar rc $@ $?
clean:
	rm -f *.a *.o crystal *~	
