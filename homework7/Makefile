all:
	g++ -std=c++17 queue.cpp include/icommand.cpp include/object.cpp include/eventloop.cpp include/exceptionhandler.cpp -o queue
	g++ -std=c++17 queue_test.cpp include/icommand.cpp include/object.cpp include/eventloop.cpp include/exceptionhandler.cpp -lcppunit -o queue_test
test:
	chmod +x queue
	./queue_test
clean:
	$(RM) queue queue_test
