all:
	g++ -std=c++17 moving.cpp object.cpp EventManager.cpp -o moving
	g++ -std=c++17 movingTest.cpp -lcppunit -o movingTest
test:
	chmod +x moving
	./movingTest
clean:
	$(RM) moving movingTest
