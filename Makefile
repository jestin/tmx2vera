CXX = g++

XML2CFLAGS = $(shell xml2-config --cflags)
XML2LIBS = $(shell xml2-config --libs)

CXXFLAGS = -Wall -Werror -std=c++11 $(XML2CFLAGS)
LDFLAGS = $(XML2LIBS)

PROGRAM = tmx2vera
OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

.SUFFIXES:	.o .cpp

.cpp.o:
	$(CXX) -g -c $(CXXFLAGS) -o $@ $<

all:	$(PROGRAM)

$(PROGRAM):		$(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) $(LDFLAGS)

run: all
	./$(PROGRAM)

tags:
	ctags * --recurse

clean:
	rm -f *.o $(PROGRAM)

