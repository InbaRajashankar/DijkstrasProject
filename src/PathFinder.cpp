#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <stack>

#include "PathFinder.hpp"

/**
 * @brief reads the contents of the file in path as an adj. list
 * 
 * @param path string filepath
 * 
 * @author Inba
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

  std::cout << "\nCITIES:\n";
  for (const auto& pair : adj_list) {
    std::cout << " - " << pair.first << "\n";
  }
}

/**
 * @brief sets the root node to node_name
 * 
 * @param node_name string name of node to be set as root
 * 
 * @author Inba
 */
void PathFinder::setRoot(const std::string& node_name) {
  if (adj_list.empty())
    throw std::runtime_error("buildAdjList must be called before root set!");

  if (!adj_list.contains(node_name))
    throw std::runtime_error("Invalid value to be set as root!");

  root = node_name;
}

/**
 * @brief run Dijkstra's algorithm to create a shortest-path tree,
 *        which is stored in dijkstra_tree
 * 
 * @author Inba
 */
void PathFinder::runDijkstras(void) {
  if (root.empty())
    throw std::runtime_error("setRoot must be called before runDijkstra run!");

  // DIJKSTRA's

  // Initialize hashmaps to store dists & previous nodes
  std::unordered_map<std::string, int> dists;
  std::unordered_map<std::string, std::string> prevs;
  for (const auto& p : adj_list) {
    dists[p.first] = p.first == root ? 0 : INT_MAX;
    prevs[p.first] = "\0";
  }

  // priority queue based on cost to get to node
  class NodeComp {
    public:
      bool operator()(const Node a, const Node b) {
        return a.cost >= b.cost;
      }
    };
  std::priority_queue <Node, std::vector<Node>, NodeComp> pq;
  Node n = {root, 0, "\0"};
  pq.push(n);

  // Go through pq, examining nodes
  while (!pq.empty()) {
    Node temp = pq.top();
    pq.pop();

    // examine neigbours
    for (const auto& p : adj_list[temp.val]) {
      int alt = p.second + temp.cost;
      if (alt < dists[p.first]) {
        dists[p.first] = alt;
        prevs[p.first] = temp.val;
        Node neighbour = {p.first, p.second + temp.cost, temp.val};
        pq.push(neighbour);
      }
    }
  }

  // populate distances
  for (const auto& p : adj_list) dijkstra_tree[p.first] = {dists[p.first], prevs[p.first]};
}

/**
 * @brief return the shortest path from root to node
 * 
 * @param dest node to visit
 * 
 * @author Inba
 */
void PathFinder::pathToNode(const std::string& dest) const {
  if (dijkstra_tree.empty()) 
    throw std::runtime_error("runDijkstra must be called before path can be found!");

  if (!adj_list.contains(dest))
    throw std::runtime_error("Invalid value to visit!");

  std::cout << "Path from " << root << " to " << dest << " found!\n";
  std::cout << " - Cost: " << dijkstra_tree.at(dest).first << ".\n";
  
  std::stack<std::string> path;

  std::string temp = dest;
  while (temp != "\0") {
    path.push(temp);
    temp = dijkstra_tree.at(temp).second;
  }

  std::cout << " - Path: ";
  std::string prev;
  std::string cur;
  while (!path.empty()) {
    prev = path.top();
    path.pop();
    if (path.empty()) {
      std::cout << prev << ".";
    } else {
      cur = path.top();

      std::cout << prev << " -(";
      for (const auto& p : adj_list.at(prev)) {
        if (p.first == cur) {
          std::cout << p.second;
        }
      }
      std::cout << ")-> ";
    }
  }
  std::cout << std::endl;
}