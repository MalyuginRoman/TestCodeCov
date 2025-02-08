all:
	g++ -std=c++17 main.cpp \
		src/com/icommand.cpp \
		src/sec/object.cpp \
		src/spe/eventloop.cpp \
		src/spe/exceptionhandler.cpp \
		src/spe/istate.cpp \
		src/com/movecommand.cpp \
		src/sec/producer.cpp -o state
	g++ -std=c++17 state_test.cpp \
		src/com/icommand.cpp \
		src/sec/object.cpp \
		src/spe/eventloop.cpp \
		src/spe/exceptionhandler.cpp \
		src/spe/istate.cpp \
		src/com/movecommand.cpp -lcppunit -o state_test
test:
	chmod +x state
	./state_test
clean:
	$(RM) state state_test
