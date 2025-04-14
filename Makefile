FLAGS := -std=c++20 -Wall -Wextra

pathFinder: pathFinder.o
	g++ $(FLAGS) $^ -o pathFinder

pathFinder.o: src/PathFinder.cpp src/PathFinder.hpp src/Node.hpp
	g++ $(FLAGS) -c $< -o pathFinder.o

clean:
	rm -rf *.o pathFinder