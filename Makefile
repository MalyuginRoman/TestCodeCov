all:
	g++ -std=c++17 main.cpp include/CommandFuelBurn.cpp include/CommandFuelCheck.cpp include/CommandLoger.cpp include/CommandMove.cpp include/CommandQueue.cpp include/CommandRepeat.cpp include/CommandRotate.cpp include/CommandSimpleMacro.cpp include/ExceptionHandler.cpp include/object.cpp -o MacroCommand
	g++ -std=c++17 test_macrocommand.cpp include/CommandFuelBurn.cpp include/CommandFuelCheck.cpp include/CommandLoger.cpp include/CommandMove.cpp include/CommandQueue.cpp include/CommandRepeat.cpp include/CommandRotate.cpp include/CommandSimpleMacro.cpp include/ExceptionHandler.cpp include/object.cpp -lcppunit -o test_macrocommand
test:
	chmod +x MacroCommand
	./test_macrocommand
clean:
	$(RM) MacroCommand test_macrocommand
