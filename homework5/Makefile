all:
	g++ -std=c++17 main.cpp include/icommand.cpp include/object.cpp -o IoC
	g++ -std=c++17 test_IoC.cpp include/icommand.cpp include/object.cpp -lcppunit -o test_IoC
test:
	chmod +x IoC
	./test_IoC
clean:
	$(RM) IoC test_Ioc
