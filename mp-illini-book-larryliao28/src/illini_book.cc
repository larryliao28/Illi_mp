#include "illini_book.hpp"

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>

// read the files
IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::vector<int> persons;
  std::map<int, std::string> relationships;
  std::map<int, std::string> new_relation;
  std::string line;

  std::ifstream fp(people_fpath);
  std::string line_str;
  while (getline(fp, line)) {
    int vertex_num = atoi(line.c_str());
    graph_.insert((
        std::pair<int, std::map<int, std::string>>(vertex_num, relationships)));
  }

  std::ifstream sec_file(relations_fpath);
  std::string relation;
  int n_pos = 0;

  while (getline(sec_file, line)) {
    int first_vertex = atoi(line.c_str());
    n_pos = line.find(',');
    line.erase(0, n_pos + 1);
    int second_vertex = atoi(line.c_str());
    n_pos = line.find(',');
    line.erase(0, n_pos + 1);
    relation = line.c_str();
    //
    // save the relationships
    //

    new_relation.insert((std::pair<int, std::string>(second_vertex, relation)));
    //
    // insert the relationship into the map
    //
    std::map<int, std::map<int, std::string>>::iterator it;
    std::map<int, std::map<int, std::string>>::iterator it_end;
    it = graph_.begin();
    it_end = graph_.end();
    while (it != it_end) {
      if (it->first == first_vertex) {
        graph_[first_vertex].insert({second_vertex, relation});
        graph_[second_vertex].insert({first_vertex, relation});
      }
      it++;
    }
  }
}

// display the read in graph
void IlliniBook::DisplayGraph() {
  for (auto const& kp : graph_) {
    std::cout << "netID: " << kp.first << std::endl;
    for (auto const& kl : kp.second) {
      std::cout << "related node: " << kl.first << " "
                << "relation:" << kl.second << std::endl;
    }
  }
}

// helper for getRelated and arerelated, passing the test
int IlliniBook::Solve(const int& uin_1, const int& uin_2) const {
  std::queue<int> queue;
  std::vector<int> visited_nodes;
  std::map<int, int> dist;

  for (const auto& init : graph_) {
    dist.insert(std::pair<int, int>(init.first, 0));
  }

  queue.push(uin_1);
  visited_nodes.push_back(uin_1);
  while (!queue.empty()) {
    int current = queue.front();
    queue.pop();
    std::map<int, std::string> adj = graph_.find(current)->second;
    for (auto& neighbor : adj) {
      if (!FindV(visited_nodes, neighbor.first)) {
        dist.find(neighbor.first)->second = dist.find(current)->second + 1;
        queue.push(neighbor.first);
        visited_nodes.push_back(neighbor.first);
      }
    }
    if (current == uin_2) {
      return dist.find(current)->second;
    }
  }

  return -1;
}

// helper for getRlated and are related with relationhips, does not work
int IlliniBook::SolveRelation(const int& uin_1,
                              const int& uin_2,
                              const std::string& relation) const {
  std::queue<int> queue;
  std::vector<int> visited_nodes;
  std::map<int, int> dist;

  for (const auto& init : graph_) {
    dist.insert(std::pair<int, int>(init.first, 0));
  }

  queue.push(uin_1);
  visited_nodes.push_back(uin_1);
  while (!queue.empty()) {
    int current = queue.front();
    queue.pop();
    std::map<int, std::string> adj = graph_.find(current)->second;
    for (auto& neighbor : adj) {
      if (neighbor.second != relation) {
        visited_nodes.push_back(neighbor.first);
      } else if (!FindVRelation(visited_nodes,
                                neighbor.first,
                                neighbor.second,
                                relation)) {
        dist.find(neighbor.first)->second = dist.find(current)->second + 1;
        queue.push(neighbor.first);
        visited_nodes.push_back(neighbor.first);
      }
    }
    if (current == uin_2 &&
        adj[uin_1] ==
            relation) {  // maybe add && adj.find(current)->second == relation
      return dist.find(current)->second;
    }
  }

  return -1;
}

// helper for solve, works
bool IlliniBook::FindV(const std::vector<int>& vec, const int& value) const {
  for (const int& ele : vec) {
    if (ele == value) {
      return true;
    }
  }
  return false;
}

// helper for solveRelation, does not work
bool IlliniBook::FindVRelation(const std::vector<int>& vec,
                               const int& value,
                               const std::string& current_relation,
                               const std::string& relation) const {
  for (const int& ele : vec) {
    if (ele == value && current_relation == relation) {
      return true;
    }
  }
  return false;
}

// works
bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  int result = Solve(uin_1, uin_2);
  return result != -1;
}

// does not work...
bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  int result = SolveRelation(uin_1, uin_2, relationship);
  return result != -1;
}

// works
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  return Solve(uin_1, uin_2);
}

// does not work
// int IlliniBook::GetRelated(int uin_1,
//                            int uin_2,
//                            const std::string& relationship) const {
//   return SolveRelation(uin_1, uin_2, relationship);
// }

// to be implemented, works in local test
std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::queue<int> queue;
  std::vector<int> visited_nodes;
  std::map<int, int> dist;

  for (const auto& init : graph_) {
    dist.insert(std::pair<int, int>(init.first, 0));
  }

  queue.push(uin);
  visited_nodes.push_back(uin);
  while (!queue.empty()) {
    int current = queue.front();
    queue.pop();
    std::map<int, std::string> adj = graph_.find(current)->second;
    for (auto& neighbor : adj) {
      if (!FindV(visited_nodes, neighbor.first)) {
        dist.find(neighbor.first)->second = dist.find(current)->second + 1;
        queue.push(neighbor.first);
        visited_nodes.push_back(neighbor.first);
      }
    }
  }

  std::vector<int> result = {};

  for (const auto& node : dist) {
    if (node.second == n) {
      result.push_back(node.first);
    }
  }
  return result;
}
// helper fucntion for count group
size_t IlliniBook::CountGroupsHelp() {
  std::set<int> visited_node;
  int count = 0;
  for (const auto& i : graph_) {
    if (visited_node.find(i.first) == visited_node.end()) {
      count += 1;
      DFS(i.first, visited_node);
    }
  }
  return count;
}

// helper for countgrouphelps
void IlliniBook::DFS(const int& node, std::set<int>& visited_node) {
  visited_node.insert(node);

  std::map<int, std::string> adj = graph_.find(node)->second;
  std::list<int> list = {};
  for (const auto& n : adj) {
    list.push_back(n.first);
  }
  std::list<int>::iterator it;
  for (it = list.begin(); it != list.end(); ++it) {
    if (visited_node.find(*it) == visited_node.end()) {
      DFS(*it, visited_node);
    }
  }
}

// cannot call nonconstant function under const function !!!!!
// size_t IlliniBook::CountGroups() const { return CountGroupsHelp(); }

// to be implemented
// size_t IlliniBook::CountGroups(const std::string& relationship) const {
//   int i = relationship.length();
//   return i;

// }

// to be implemented
// size_t IlliniBook::CountGroups(
//     const std::vector<std::string>& relationships) const {
//   int i = relationships.size();
//   return i;
// }

// way sto do countgroups with relationship: