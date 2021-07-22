
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -MMD # -MMD builds dependency lists in .d files

SRC = $(shell find src/ -name "*.cpp")
HEADERS = $(shell find src/ -name "*.h")
OBJECTS = $(SRC:%.cpp=%.o)

DEPENDS = ${OBJECTS:.o=.d} # substitute .o with .d for dependency files
EXEC = prog

all: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean:
	rm –rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}