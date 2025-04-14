#include <iostream>
#include <string>

#include "PathFinder.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Format: ./pathFinder [FILENAME]\n";
    return 1;
  }

  PathFinder p = PathFinder();
  std::string filename = argv[1];
  p.buildAdjList(filename);

  std::string start;
  std::cout << "\nEnter your start city: ";
  std::cin >> start;
  p.setRoot(start);

  p.runDijkstras();

  std::string dest;
  while (1) {
    std::cout << "\nWhere to go to (q to quit)? ";
    std::cin >> dest;
    if (dest == "q") return 0;
    p.pathToNode(dest);
  }

  return 0;
}