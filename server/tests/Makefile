OBJS	= request_handlers_test.o request_handlers.o Storage.o
SOURCE	= request_handlers_test.cpp ../operations_serwer/request_handlers/request_handlers.h ../operations_serwer/request_handlers/request_handlers.cpp ../operations_serwer/storage/Storage.h ../operations_serwer/storage/Storage.cpp
HEADER	= ../data_structures/client_msg.h ../data_structures/server_msg.h ../data_structures/codes.h request_handlers/request_handlers.h
OUT	= ./request_handlers_test
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

request_handlers.o: ../operations_serwer/request_handlers/request_handlers.cpp
		$(CC) $(FLAGS) ../operations_serwer/request_handlers/request_handlers.cpp -std=c++11

request_handlers_test.o: request_handlers_test.cpp
		$(CC) $(FLAGS) request_handlers_test.cpp -std=c++11

Storage.o: ../operations_serwer/storage/Storage.cpp
	$(CC) $(FLAGS) ../operations_serwer/storage/Storage.h ../operations_serwer/storage/Storage.cpp -std=c++11

clean:
	rm -f $(OBJS) $(OUT)
