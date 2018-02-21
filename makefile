LINKERFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS = -Wall -g -std=c++14 -o 
main: main.cpp
	g++ main.cpp $(CPPFLAGS) main $(LINKERFLAGS)

clean:
	rm -f *.o
