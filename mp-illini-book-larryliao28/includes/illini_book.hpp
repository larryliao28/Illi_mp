#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

class IlliniBook {
public:
  IlliniBook(const std::string& people_fpath,
             const std::string& relations_fpath);
  IlliniBook(const IlliniBook& rhs) = delete;
  IlliniBook& operator=(const IlliniBook& rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string& relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string& relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string& relationship) const;
  size_t CountGroups(const std::vector<std::string>& relationships) const;

  // helper
  int Solve(const int& uin_1, const int& uin_2) const;
  bool FindV(const std::vector<int>& vec, const int& value) const;

  int SolveRelation(const int& uin_1,
                    const int& uin_2,
                    const std::string& relation) const;
  bool FindVRelation(const std::vector<int>& vec,
                     const int& value,
                     const std::string& current_relation,
                     const std::string& relation) const;

  void DisplayGraph();

  void DFS(const int& node, std::set<int>& visited_node);
  // void DFS(const int& node) const;
  size_t CountGroupsHelp();

private:
  std::map<int, std::map<int, std::string>> graph_;
  std::set<int> visited_node_;
};

#endif
