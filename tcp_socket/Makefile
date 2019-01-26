.PHONY:all
all:tcp_clie tcp_serv
tcp_clie:tcp_clie.cpp
	g++ -o $@ $^ 
tcp_serv:tcp_serv.cpp
	g++ -o $@ $^ -std=c++11 -lpthread 
.PHONY:clean
clean:
	rm tcp_clie tcp_serv


