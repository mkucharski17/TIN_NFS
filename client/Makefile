ODIR = obj/
OBJS	= $(ODIR)main.o $(ODIR)fileOperations.o $(ODIR)directoryOperations.o $(ODIR)open.o $(ODIR)send_message.o $(ODIR)DirStorage.o $(ODIR)authorization.o
SOURCE	= main.cpp fileOperations.cpp directoryOperations.cpp file/open/open.cpp send_message/send_message.cpp storage/DirStorage.cpp authorization/authorization.cpp
HEADER	= fileOperations.h directoryOperations.h file/open/open.h send_message/send_message.h storage/DirStorage.h authorization/authorization.h data_structures/client_msg.h data_structures/server_msg.h data_structures/codes.h
OUT	= client
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

$(ODIR)main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++14 -o $(ODIR)main.o

$(ODIR)fileOperations.o: fileOperations.cpp
	$(CC) $(FLAGS) fileOperations.cpp -std=c++14 -o $(ODIR)fileOperations.o

$(ODIR)directoryOperations.o: directoryOperations.cpp
	$(CC) $(FLAGS) directoryOperations.cpp -std=c++14 -o $(ODIR)directoryOperations.o

$(ODIR)open.o: file/open/open.cpp
	$(CC) $(FLAGS) file/open/open.cpp -std=c++14 -o $(ODIR)open.o

$(ODIR)send_message.o: send_message/send_message.cpp
	$(CC) $(FLAGS) send_message/send_message.cpp -std=c++14 -o $(ODIR)send_message.o

$(ODIR)DirStorage.o: storage/DirStorage.cpp
	$(CC) $(FLAGS) storage/DirStorage.cpp -std=c++14 -o $(ODIR)DirStorage.o

$(ODIR)authorization.o: authorization/authorization.cpp
	$(CC) $(FLAGS) authorization/authorization.cpp -std=c++14 -o $(ODIR)authorization.o


clean:
	rm -f $(OBJS) $(OUT)
