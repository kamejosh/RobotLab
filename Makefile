CC=g++
CFLAGS=-std=c++11 -g -Wall -O
all: mazerunner
mazerunner: main.o node.o robot.o lab.o
	${CC} ${CFLAGS} -o mazerunner main.o node.o robot.o lab.o
lab.o: lab.cpp lab.h robot.h node.h
	${CC} ${CFLAGS} -c lab.cpp
robot.o: robot.cpp robot.h node.h
	${CC} ${CFLAGS} -c robot.cpp
node.o: node.cpp node.h
	${CC} ${CFLAGS} -c node.cpp
main.o: main.cpp lab.h
	${CC} ${CFLAGS} -c main.cpp
clean:
	rm -f lab.o robot.o node.o main.o mazerunner
