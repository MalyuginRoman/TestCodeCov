all:
	g++ -std=c++17 main.cpp -o main
	g++ -std=c++17 equationTest.cpp -lcppunit -o equationTest
test:
	chmod +x main
	./equationTest
clean:
	$(RM) main equationTest
