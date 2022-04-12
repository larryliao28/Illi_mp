#include <iostream>

#include "illini_book.hpp"

int main() {
  IlliniBook test{
      "/home/vagrant/src/mp-illini-book-larryliao28/example/persons.csv",
      "/home/vagrant/src/mp-illini-book-larryliao28/example/relations.csv"};
  test.DisplayGraph();
  return 0;
}
