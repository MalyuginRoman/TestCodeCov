all:
	g++ -std=c++17 server.cpp include/eventloop.cpp include/exceptionhandler.cpp include/icommand.cpp include/object.cpp include/producer.cpp -o server
	g++ -std=c++17 client.cpp -lcppunit -o client
test:
	chmod +x server
	./client
clean:
	$(RM) server client
