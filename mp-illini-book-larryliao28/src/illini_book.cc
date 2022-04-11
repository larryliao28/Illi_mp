#include "illini_book.hpp"

#include <fstream>
#include <map>
#include <queue>

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  // read people_fapath as nodes and relations_fpath as the realtions
  // store it into a map std::map<string of relationship, std::map of
  // relationhips.

  std::ifstream ifs_people(people_fpath);
  std::ifstream ifs_path(relations_fpath);
  // read ifs_people into a vector of strings
  //
  if (!(ifs_people.eof())) {
    // single_vector_.push_back(value)
  }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  for (int i = 0; i < graph_.size(); ++i) {
    if (i = uin_1) {
    }
  }
}
bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {}
int IlliniBook::GetRelated(int uin_1, int uin_2) const {}
int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {}
std::vector<int> IlliniBook::GetSteps(int uin, int n) const {}
size_t IlliniBook::CountGroups() const {}
size_t IlliniBook::CountGroups(const std::string& relationship) const {}
size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {}

int IlliniBook::Solve(const std::string& start, const std::string& dest) {
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

bool IlliniBook::FindV(const std::vector<std::string>& vec,
                       const std::string& value) {
  for (const std::string& ele : vec) {
    if (ele == value) {
      return true;
    }
  }
  return false;
}
