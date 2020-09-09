all: plus 

OFILES= main.o add.o print.o parse.o

plus: libplus.a
	g++ -L. -lplus -o plus

libplus.a:$(OFILES)
	ar rc $@ $?
clean:
	rm -f *.a *.o plus *~	
