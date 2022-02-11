CXX = g++

XML2CFLAGS = $(shell pkg-config libxml++-2.6 --cflags)
XML2LIBS = $(shell pkg-config libxml++-2.6 --libs)

CXXFLAGS = -Wall -Werror -std=c++11 $(XML2CFLAGS)
LDFLAGS = $(XML2LIBS)

IGNORE_WARNINGS = -Wno-deprecated-declarations

PROGRAM = tmx2vera
OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

.SUFFIXES:	.o .cpp

.cpp.o:
	$(CXX) -g -c $(CXXFLAGS)  $(IGNORE_WARNINGS) -o $@ $<

all:	$(PROGRAM)

$(PROGRAM):		$(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) $(LDFLAGS)

run: all
	./$(PROGRAM)

tags:
	ctags * --recurse

clean:
	rm -f *.o $(PROGRAM)

