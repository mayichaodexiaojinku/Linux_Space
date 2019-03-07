server=ChatServer
client=ChatClient
.PHONY:all
all:$(server) $(client)
$(server):ChatServer.cpp
	g++  -o $@ $^ -std=c++11 -lpthread -ljsoncpp
$(client):ChatClient.cpp
	g++  -o $@ $^ -std=c++11 -lpthread -lncurses -ljsoncpp
.PHONY:clean
clean:
	rm -rf $(server) $(client)
