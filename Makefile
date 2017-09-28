CXX=c++
CXXFLAGS=-c -std=c++11
LDLIBS=-lSDL2 -L/usr/local/Cellar
OBJECTS= main.o Swarm.o Particle.o Screen.o

SRC1=Screen.cpp Swarm.cpp Particle.cpp
SRC2=main.cpp
TARGET=run

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LDLIBS)

main.o: main.cpp Swarm.o Screen.o
	$(CXX) main.cpp $(CXXFLAGS)

Screen.o: Screen.cpp Screen.hpp
	$(CXX) Screen.cpp $(CXXFLAGS)

Swarm.o: Swarm.cpp Swarm.hpp Particle.o
	$(CXX) Swarm.cpp $(CXXFLAGS)

Particle.o: Particle.cpp Particle.hpp
	$(CXX) Particle.cpp $(CXXFLAGS)

clean:
	rm $(OBJECTS) $(TARGET)
