#pragma once

#include <vector>
#include <unordered_map>

#include "Node.hpp"

class PathFinder {
public:
  void buildAdjList(const std::string& path);
  void setRoot(const std::string& node_name);
  void runDijkstras(void);
  int pathToNode(const std::string& node_name) const;
  
private:
  std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> adj_list;
  std::string root;
  std::unordered_map<std::string, std::pair<int, std::string>> dijkstra_tree;
};