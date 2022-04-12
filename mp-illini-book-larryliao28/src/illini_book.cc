#include "illini_book.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <queue>

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  // possible data structures: map<int, map<int, string>>

  // std::ifstream ifs_people(people_fpath);
  // std::ifstream ifs_path(relations_fpath);
  // // read ifs_people into a vector of strings
  // //  read relations_fpat
  // if (!(ifs_people.eof())) {
  //   // single_vector_.push_back(value)
  // }

  std::vector<int> persons;
  std::map<int, std::string> relationships;
  std::cout << "read the first file : " << std::endl;
  std::string line;

  std::ifstream fp(people_fpath);
  int line_num = 1;
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

  line_num = 1;
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

    relationships.insert(
        (std::pair<int, std::string>(second_vertex, relation)));

    //
    // insert the relationship into the map
    //

    int map_position = 0;
    std::map<int, std::map<int, std::string>>::iterator it;
    std::map<int, std::map<int, std::string>>::iterator it_end;
    it = graph_.begin();
    it_end = graph_.end();
    while (it != it_end) {
      if (it->first == first_vertex) {
        std::cout << "key: " << it->first << "\n";
        std::cout << "insert relationship: " << second_vertex << " " << relation
                  << "\n";
        graph_[map_position].insert(
            (std::pair<int, std::string>(second_vertex, relation)));
      }
      it++;
      map_position++;
    }
    line_num++;
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

// bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
//   for (int i = 0; i < graph_.size(); ++i) {
//     if (i = uin_1) {
//     }
//   }
// }
// bool IlliniBook::AreRelated(
//     int uin_1, int uin_2, const std::string& relationship) const {}
// int IlliniBook::GetRelated(int uin_1, int uin_2) const {}
// int IlliniBook::GetRelated(
//     int uin_1, int uin_2, const std::string& relationship) const {}
// std::vector<int> IlliniBook::GetSteps(int uin, int n) const {}
// size_t IlliniBook::CountGroups() const {}
// size_t IlliniBook::CountGroups(const std::string& relationship) const {}
// size_t IlliniBook::CountGroups(const std::vector<std::string>&
// relationships)
//     const {}

// int IlliniBook::Solve(const int& start, const int& dest) {
//   // Note that since this is not a node based graph (we are using adjacency
//   // lists), this will probably NOT be a recursive function

//   std::queue<int> queue;
//   std::vector<int> visited_nodes;
//   // map
//   std::map<std::string, int> dist;

//   for (const auto& init : adj_) {
//     dist.insert(std::pair<int, int>(init.first, 0));
//   }

//   queue.push(start);
//   visited_nodes.push_back(start);
//   // visited_nodes.push(start);
//   while (!queue.empty()) {
//     std::string current = queue.front();
//     queue.pop();
//     for (std::string& neighbor : GetAdjacencyList(current)) {
//       if (!FindV(visited_nodes, neighbor)) {
//         dist.find(neighbor)->second = dist.find(current)->second + 1;
//         queue.push(neighbor);
//         visited_nodes.push_back(neighbor);
//       }
//     }
//     if (current == dest) {
//       return dist.find(current)->second;
//     }
//   }

//   return -1;
// }

// bool IlliniBook::FindV(const std::vector<std::string>& vec,
//                        const std::string& value) {
//   for (const std::string& ele : vec) {
//     if (ele == value) {
//       return true;
//     }
//   }
//   return false;
// }
