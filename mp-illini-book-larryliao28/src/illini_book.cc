#include "illini_book.hpp"

#include <fstream>
#include <map>

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  // read people_fapath as nodes and relations_fpath as the realtions
  // store it into a map std::map<string of relationship, std::map of
  // relationhips.

  std::ifstream ifs_people(people_fpath);
  std::ifstream ifs_path(relations_fpath);
  if (!(ifs_people.eof())) {
    // single_vector_.push_back(value)
  }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {}
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
