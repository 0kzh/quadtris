CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -MMD -L/usr/X11/lib -I/opt/X11/include
SRC = $(shell find src/ -name "*.cpp")
HEADERS = $(shell find src/ -name "*.h")
OBJECTS = $(SRC:%.cpp=%.o)

DEPENDS = ${OBJECTS:.o=.d} # substitute .o with .d for dependency files
EXEC = prog

all: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

clean:
	rm –rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
