OBJS	= request_handlers_test.o request_handlers.o Storage.o
SOURCE	= request_handlers_test.cpp ../operationsSerwer/request_handlers/request_handlers.h ../operationsSerwer/request_handlers/request_handlers.cpp ../operationsSerwer/storage/Storage.h ../operationsSerwer/storage/Storage.cpp
HEADER	= ../data_structures/client_msg.h ../data_structures/server_msg.h ../data_structures/codes.h request_handlers/request_handlers.h
OUT	= ./request_handlers_test
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

request_handlers.o: ../operationsSerwer/request_handlers/request_handlers.cpp
		$(CC) $(FLAGS) ../operationsSerwer/request_handlers/request_handlers.cpp -std=c++11

request_handlers_test.o: request_handlers_test.cpp
		$(CC) $(FLAGS) request_handlers_test.cpp -std=c++11

Storage.o: ../operationsSerwer/storage/Storage.cpp
	$(CC) $(FLAGS) ../operationsSerwer/storage/Storage.h ../operationsSerwer/storage/Storage.cpp -std=c++11

clean:
	rm -f $(OBJS) $(OUT)
