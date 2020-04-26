CC=g++
CXXFLAGS=-std=c++11 -Wall
DEPS=message.hpp folder.hpp
OBJ=message.o folder.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

run: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS)

clean:
	rm -rf *.o run
