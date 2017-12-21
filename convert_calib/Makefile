CXX=g++
CXXFLAGS= -std=c++11

CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

all:
	$(CXX) -o main main.cpp $(CFLAGS) $(LIBS)


clean:
	rm *~
	rm main
