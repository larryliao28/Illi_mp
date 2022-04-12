#include <iostream>

#include "illini_book.hpp"

int main() {
  IlliniBook test{
      "/home/vagrant/src/mp-illini-book-larryliao28/example/persons.csv",
      "/home/vagrant/src/mp-illini-book-larryliao28/example/relations.csv"};
  // test.DisplayGraph();
  std::cout << test.AreRelated(1, 7) << std::endl;
  // std::cout << test.GetRelated(1, 15) << std::endl;
  // std::cout << test.AreRelated(1, 2, "128") << std::endl;
  std::cout << test.CountGroupsHelp() << std::endl;
  return 0;
}
