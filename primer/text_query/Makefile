CC=g++
CXXFLAGS=-std=c++11 -Wall
DEPS=text_query.hpp
OBJ=text_query.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

run: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS)

clean:
	rm -rf *.o run
