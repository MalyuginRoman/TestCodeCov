all:
	g++ -std=c++17 main.cpp include/CommandLoger.cpp include/CommandMove.cpp include/CommandQueue.cpp include/CommandRepeat.cpp include/CommandRotate.cpp include/ExceptionHandler.cpp -o ExceptionHandler
	g++ -std=c++17 test_exception.cpp include/CommandLoger.cpp include/CommandMove.cpp include/CommandQueue.cpp include/CommandRepeat.cpp include/CommandRotate.cpp include/ExceptionHandler.cpp -lcppunit -o test_exception
test:
	chmod +x ExceptionHandler
	./test_exception
clean:
	$(RM) ExceptionHandler test_exception
