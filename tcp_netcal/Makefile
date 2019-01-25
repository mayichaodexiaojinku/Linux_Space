.PHONY:all
all:server client
server:server.cc
	g++ -o $@ $^ -fpermissive -lpthread
client:client.cc
	g++ -o $@ $^ -fpermissive
.PHONY:clean
clean:
	rm server client
