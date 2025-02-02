all:
	g++ -std=c++17 main.cpp include/icommand.cpp include/object.cpp include/eventloop.cpp include/exceptionhandler.cpp include/istate.cpp -o state
	g++ -std=c++17 state_test.cpp include/icommand.cpp include/object.cpp include/eventloop.cpp include/exceptionhandler.cpp include/istate.cpp -lcppunit -o state_test
test:
	chmod +x state
	./state_test
clean:
	$(RM) state state_test
