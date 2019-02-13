CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
INC=include
SRC=src

ROOTFLAG=`root-config --cflags --libs`
CPPFLAG=-I$(INC)

all: runPfCandCleaner

PfCandCleaner.o: $(SRC)/PfCandCleaner.C
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(CPPFLAG) $(ROOTFLAG)

runPfCandCleaner: runPfCandCleaner.C PfCandCleaner.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(CPPFLAG) $(ROOTFLAG)

.PHONY:
	clean
	all

clean:
	rm -f runPfCandCleaner
