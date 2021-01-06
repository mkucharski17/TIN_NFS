OBJS	= main.o request_handlers.o
SOURCE	= main.cpp request_handlers/request_handlers.cpp
HEADER	= ../data_structures/client_msg.h ../data_structures/server_msg.h ../data_structures/codes.h request_handlers/request_handlers.h
OUT	= ../operationsSerwer
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11

request_handlers.o: request_handlers/request_handlers.cpp
		$(CC) $(FLAGS) request_handlers/request_handlers.cpp -std=c++11

clean:
	rm -f $(OBJS) $(OUT)
