#include "solution.hpp"

#include <iostream>
#include <queue>

Solution::Solution(
    const std::vector<std::pair<std::string, std::string>>& prerequisites) {
  for (const std::pair<std::string, std::string>& item : prerequisites) {
    if (!VertexInGraph(item.first)) {
      AddVertex(item.first);                                  
    }
    if (!VertexInGraph(item.second)) {
      AddVertex(item.second);       
    }
    GetAdjacencyList(item.first).push_back(item.second);
  }
}

int Solution::Solve(const std::string& start, const std::string& dest) {
  // Note that since this is not a node based graph (we are using adjacency
  // lists), this will probably NOT be a recursive function
  if (!VertexInGraph(start) || !VertexInGraph(dest)) {
    return -1;
  }
  std::queue<std::string> queue;        
  std::vector<std::string> visited_nodes;      
  // map
  std::map<std::string, int> dist;

  for (const auto& init : adj_) {                        
    dist.insert(std::pair<std::string, int>(init.first, 0));
  }

  queue.push(start);            
  visited_nodes.push_back(start);          
  // visited_nodes.push(start);
  while (!queue.empty()) {
    std::string current = queue.front();
    queue.pop();    
    for (std::string& neighbor : GetAdjacencyList(current)) {    
      if (!FindV(visited_nodes, neighbor)) {         
        dist.find(neighbor)->second = dist.find(current)->second + 1;
        queue.push(neighbor);   
        visited_nodes.push_back(neighbor);     
      }
    }
    if (current == dest) {   
      return dist.find(current)->second;
    }
  }

  return -1;
}

bool Solution::FindV(const std::vector<std::string>& vec,
                     const std::string& value) {
  for (const std::string& ele : vec) {
    if (ele == value) {
      return true;
    }
  }
  return false;
}
///////////////////////////////////////////////////////////////////////////////
// Provide function definitions (uncomment to use!)                          //
///////////////////////////////////////////////////////////////////////////////

void Solution::AddVertex(const std::string& vertex) {
  if (VertexInGraph(vertex))
    throw std::runtime_error("vertex already in graph.");
  adj_.insert(std::pair<std::string, std::list<std::string>>(
      vertex, std::list<std::string>()));   
}

std::list<std::string>& Solution::GetAdjacencyList(const std::string& vertex) {
  return adj_.find(vertex)->second;          
}

bool Solution::VertexInGraph(const std::string vertex) {
  if (adj_.find(vertex) != adj_.end())    
    return true;
  else
    return false;
}

std::ostream& operator<<(std::ostream& os, const Solution& sol) {
  os << "Contents:" << std::endl;

  for (const auto& pair : sol.adj_) {
    os << "  " << pair.first << ": [ ";

    for (const auto& list_entry : pair.second) {
      os << list_entry << " ";
    }

    os << "]" << std::endl;
  }

  return os;
}