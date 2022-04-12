#include "illini_book.hpp"

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  // possible data structures: map<int, map<int, string>>

  std::vector<int> persons;
  std::map<int, std::string> relationships;
  std::map<int, std::string> newRelation;
  std::cout << "read the first file : " << std::endl;
  std::string line;

  std::ifstream fp(people_fpath);
  // int line_num = 1;
  std::string line_str;
  // int vertex_num = 1;
  while (getline(fp, line)) {
    std::cout << "in first while loop\n";

    int vertex_num = atoi(line.c_str());
    // cout << "string: " << line << "\n";
    std::cout << "vertex number: " << vertex_num << "\n";

    // initialize the book to be all empty relationships

    graph_.insert((
        std::pair<int, std::map<int, std::string>>(vertex_num, relationships)));
  }

  //
  // initialize the book to be a vector of empty relationship
  //
  //
  //
  std::cout << "vector size: " << persons.size() << "\n";

  std::cout << "\nread the second file: \n\n";

  std::ifstream sec_file(relations_fpath);

  // int line_num = 1;
  // int first_vertex = 0;
  // int second_vertex = 0;
  std::string relation;
  int n_pos = 0;

  while (getline(sec_file, line)) {
    std::cout << "in second while loop\n";
    int first_vertex = atoi(line.c_str());
    std::cout << "first vertex number: " << first_vertex << ",";

    n_pos = line.find(',');
    line.erase(0, n_pos + 1);
    int second_vertex = atoi(line.c_str());
    std::cout << "second vertex number: " << second_vertex << ",";

    n_pos = line.find(',');

    line.erase(0, n_pos + 1);

    relation = line.c_str();
    std::cout << "relation: " << relation << "\n";

    //
    // save the relationships
    //

    newRelation.insert((std::pair<int, std::string>(second_vertex, relation)));

    //
    // insert the relationship into the map
    //
    std::map<int, std::string> aMap;
    // int map_position = 0;
    std::map<int, std::map<int, std::string>>::iterator it;
    std::map<int, std::map<int, std::string>>::iterator it_end;
    it = graph_.begin();
    it_end = graph_.end();
    while (it != it_end) {
      if (it->first == first_vertex) {
        std::cout << "key: " << it->first << "\n";
        std::cout << "insert relationship: " << second_vertex << " " << relation
                  << "\n";
        graph_[first_vertex].insert({second_vertex, relation});
        // graph_[second_vertex].insert({first_vertex, second_vertex});
      }
      it++;
      // map_position++;
    }
    // line_num++;
  }
}

void IlliniBook::DisplayGraph() {
  for (auto const& kp : graph_) {
    std::cout << "netID: " << kp.first << std::endl;
    for (auto const& kl : kp.second) {
      std::cout << "related node: " << kl.first << " "
                << "relation:" << kl.second << std::endl;
    }
  }
}

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
      if (!FindVRelation(
              visited_nodes, neighbor.first, neighbor.second, relation)) {
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

bool IlliniBook::FindV(const std::vector<int>& vec, const int& value) const {
  for (const int& ele : vec) {
    if (ele == value) {
      return true;
    }
  }
  return false;
}

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

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  int result = Solve(uin_1, uin_2);
  return result != -1;
}

// does not wrok...
// bool IlliniBook::AreRelated(int uin_1,
//                             int uin_2,
//                             const std::string& relationship) const {
//   int result = SolveRelation(uin_1, uin_2, relationship);
//   return result != -1;
// }

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  return Solve(uin_1, uin_2);
}
// int IlliniBook::GetRelated(
//     int uin_1, int uin_2, const std::string& relationship) const {}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {}

size_t IlliniBook::CountGroupsHelp() {
  std::set<int> visited_node;
  int count = 0;
  for (const auto& i : graph_) {
    if (visited_node.find(i.first) == visited_node.end()) {
      count += 1;
      DFS(i.first, visited_node);
    }
  }
  // connected_ = count;
  return count;
}

// helper for countgroups
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
// size_t IlliniBook::CountGroups() const {
//   return const_cast<const IlliniBook*>(this) CountGroupsHelp();
// }

// size_t IlliniBook::CountGroups(const std::string& relationship) const {}
// size_t IlliniBook::CountGroups(const std::vector<std::string>&
// relationships)
//     const {}
