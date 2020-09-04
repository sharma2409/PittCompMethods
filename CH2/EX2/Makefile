all: stretch clean

OFILES= stretch.o

libstretch.a:$(OFILES)
	ar rc $@ $?

stretch: $(OFILES)
	g++ $(OFILES) -o stretch
	
clean:
	rm -f *.a *.o stretch *~	
