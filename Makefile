PROJECT_NAME = solver.exe

.PHONY : clean debug release

debug : ./obj/main.o ./obj/functions.o ./obj/tests.o
	g++ ./obj/main.o ./obj/functions.o ./obj/tests.o -o $(PROJECT_NAME) -fsanitize=address -g

release : ./obj/main.o ./obj/functions.o ./obj/tests.o
	g++ ./obj/main.o ./obj/functions.o ./obj/tests.o -o $(PROJECT_NAME)

./obj/main.o : ./src/main.cpp
	g++ -c ./src/main.cpp -o ./obj/main.o

./obj/functions.o : ./src/functions.cpp
	g++ -c ./src/functions.cpp -o ./obj/functions.o

./obj/tests.o : ./src/main.cpp
	g++ -c ./tests/tests.cpp -o ./obj/tests.o

clean :
	rm $(PROJECT_NAME) ./obj/*.o

