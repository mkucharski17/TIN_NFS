OBJS	= main.o
SOURCE	= main.cpp
HEADER	= ../data_structures/client_msg.h ../data_structures/server_msg.h ../data_structures/codes.h
OUT	= ../operationsSerwer
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)
