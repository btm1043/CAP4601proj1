#  Makefile for project 1. it will make use of make(make all), make run, and make clean. 
CXX=g++
OBJECTS= ConnectM.o agent.o board.o
CXXFLAGS= -std=c++11 -c -g -Wall

# all compiles both files and then links the object files to build the dsp4MonteCarlo exe
all: $(OBJECTS)
	$(CXX) $(OBJECTS) -o ConnectM
	
# creates the agent object file
agent.o: agent.cpp
	$(CXX) $(CXXFLAGS) agent.cpp

# creates the board object file
board.o: board.cpp
	$(CXX) $(CXXFLAGS) board.cpp

# creates the ConnectM object file
ConnectM.o: ConnectM.cpp
	$(CXX) $(CXXFLAGS) ConnectM.cpp

# function to compile build and run the program to save time testing	
run: all
	./ConnectM 7 4
	
# basic remove to clean the folder
clean:
	$(RM) *o ConnectM