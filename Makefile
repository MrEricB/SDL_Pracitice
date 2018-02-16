CC=g++
SRCS=main.cpp Screen.cpp Partical.cpp Swarm.cpp


sim:
	${CC} ${SRCS} -o main -Wall -I include -L lib -l SDL2-2.0.0