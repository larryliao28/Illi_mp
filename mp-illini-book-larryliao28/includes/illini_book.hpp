#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <list>
#include <map>
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
  int Solve(const int& start, const int& dest);
  bool FindV(const std::vector<int>& vec, const int& value);
  void DisplayGraph();

private:
  std::map<int, std::map<int, std::string>> graph_;
  // std::map<std::string, std::list<std::string>> adj_;
};

#endif
