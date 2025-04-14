#include <fstream>
#include <iostream>
#include <sstream>

#include "PathFinder.hpp"

/**
 * @brief reads the contents of the file in path as an adj. list
 */
void PathFinder::buildAdjList(const std::string& path) {
  std::string buffer;
  std::ifstream in_file(path);
  if (!in_file.is_open()) throw std::runtime_error("Could not open file: " + path);

  while (getline(in_file, buffer)) {
    // if there is no colon, line is invalid
    if (buffer.find(':') == std::string::npos) continue;

    // find name of the node
    int colon_pos = buffer.find(':');
    std::string node_name = buffer.substr(0, colon_pos);

    // process edges
    std::vector<std::pair<std::string, int>> edges;
    std::string buffer2;
    std::stringstream temp_string_stream(
      buffer.substr(colon_pos + 1, buffer.size() - colon_pos)
    );
    while (getline(temp_string_stream, buffer2, ',')) {
      int open_p = buffer2.find('(');
      int close_p = buffer2.find(')');
      std::pair<std::string, int> p(
        buffer2.substr(0, open_p), 
        std::stoi(buffer2.substr(open_p + 1, close_p - open_p + 1))
      );
      edges.push_back(p);
    }

    // add node & edges to adj list
    adj_list[node_name] = edges;
  }

  in_file.close();

  // for (const auto& pair : adj_list) {
  //   std::cout << pair.first << " ~ \n";
  //   for (const auto& p : pair.second) {
  //     std::cout << p.first << ' ' << p.second << '\n';
  //   }
  // }
}

void PathFinder::setRoot(const std::string& node_name) {
  if (adj_list.empty())
    throw std::runtime_error("buildAdjList must be called before root set!");

  if (!adj_list.contains(node_name))
    throw std::runtime_error("Invalid value to be set as root!");

  root = node_name;
}

int main() {
  PathFinder p = PathFinder();
  p.buildAdjList("cities.txt");
  p.setRoot("New_York");
  return 0;
}