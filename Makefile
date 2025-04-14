FLAGS := -std=c++20 -Wall -Wextra

pathFinder: main.o pathFinder.o
	g++ $(FLAGS) $^ -o pathFinder

main.o: src/main.cpp src/PathFinder.hpp
	g++ $(FLAGS) -c $< -o main.o

pathFinder.o: src/PathFinder.cpp src/PathFinder.hpp src/Node.hpp
	g++ $(FLAGS) -c $< -o pathFinder.o

clean:
	rm -rf *.o pathFinder