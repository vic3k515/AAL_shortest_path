CXX=g++
CXXFLAGS=-std=c++11 -O2 -lpthread -lX11 -Wall
BIN=path.out

all: $(OBJ)
	$(CXX) $(CXXFLAGS) src/*.cpp -o $(BIN)

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)
