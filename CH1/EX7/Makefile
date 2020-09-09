all: plus 
CXXFLAGS=-fPIC
OFILES= main.o add.o print.o parse.o

plus: libPlus.so
	g++ -L. -lPlus -o plus


libPlus.so:$(OFILES)
	g++ -shared -o $@ $?


clean:
	rm -f *.so *.o plus *~	
