CC=g++
#CFLAGS=-g -Wall -O -fexceptions -O0
#CFLAGS=
LDFLAGS=$(shell sdl-config --cflags) $(shell sdl-config --libs)
SOURCES=  Graphics.cpp Swarm.cpp Particle.cpp Objectif.cpp
OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS:=$(OBJECTS:.C=.o)
EXECUTABLE=Graphics
GA_INC_DIR= /usr/local/include
GA_LIB_DIR= /usr/local/lib
INC_DIRS= -I$(GA_INC_DIR)
LIB_DIRS= -L$(GA_LIB_DIR)

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) -o $@ $(LIB_DIRS) $(OBJECTS) -lSDL -lm -ldl

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@ 

clean:
	rm -f *.o *.dat *.txt *~ Graphics
