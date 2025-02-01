all:
	g++ -std=c++17 equation.cpp -o equation
	g++ -std=c++17 equationTest.cpp -lcppunit -o equationTest
test:
	chmod +x equation
	./equationTest
clean:
	$(RM) equation equationTest
