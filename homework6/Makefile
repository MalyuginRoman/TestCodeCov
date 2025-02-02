all:
	g++ -std=c++17 main.cpp include/icommand.cpp include/imoving.cpp include/irotateble.cpp include/object.cpp -o main_adapter
	g++ -std=c++17 test_adapter.cpp include/icommand.cpp include/imoving.cpp include/irotateble.cpp include/object.cpp -lcppunit -o test_adapter

test:
	chmod +x main_adapter
	./test_adapter
clean:
	$(RM) main_adapter test_adapter
