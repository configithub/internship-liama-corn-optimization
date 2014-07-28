CC=g++
#CFLAGS=-g -Wall -O -fexceptions -O0
#CFLAGS=
LDFLAGS=
SOURCES= Particle.cpp Objectif.cpp Swarm.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS:=$(OBJECTS:.C=.o)
EXECUTABLE=PSwarm
GA_INC_DIR= /usr/local/include
GA_LIB_DIR= /usr/local/lib
INC_DIRS= -I$(GA_INC_DIR)
LIB_DIRS= -L$(GA_LIB_DIR)

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) -o $@ $(LIB_DIRS) $(OBJECTS) -lga -lm

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@ 

clean:
	rm -f *.o *.dat *.txt *~ PSwarm 
