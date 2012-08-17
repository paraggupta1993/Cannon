CPP = g++
OPTS =  -I"../include" -L"/usr/lib" ../bin/linux-gcc/libIrrKlang.so ../bin/linux-gcc/ikpMP3.so -pthread  -lglut -lGLU -g

all:
	$(CPP) cannon.cpp imageloader.cpp $(OPTS)
	

clean:
	rm example
