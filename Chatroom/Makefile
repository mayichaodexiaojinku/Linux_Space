server=ChatServer
client=ChatClient
.PHONY:all
all:$(server) $(client)
$(server):ChatServer.cpp
	g++ -o $@ $^ -lpthread
$(client):ChatClient.cpp
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -rf $(server) $(client)
