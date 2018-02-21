LINKERFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS = -Wall -g  -o
main: main.cpp
	g++ main.cpp $(CPPFLAGS) main $(LINKERFLAGS)

clean:
	rm -f *.o
