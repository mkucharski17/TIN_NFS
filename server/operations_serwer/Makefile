OBJS	= main.o Storage.o
SOURCE	= main.cpp Storage.h Storage.cpp
HEADER	= ../data_structures/client_msg.h ../data_structures/server_msg.h ../data_structures/codes.h
OUT	= ../operationsSerwer
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11

Storage.o: Storage.cpp
	$(CC) $(FLAGS) Storage.h Storage.cpp -std=c++11

clean:
	rm -f $(OBJS) $(OUT)
