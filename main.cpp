#include <iostream>
#include "DLList.hpp"

using namespace std;

int main(void) {
  cout << string(20, '-') << "TESTING EMPTY LIST" << string(20, '-') << endl;
  DLList<int> a;
  DLList<int> b;
  cout << "TESTING pop_back, pop_front AND remove METHODS ON EMPTY LIST a\n";
  a.print();
  a.pop_back();
  a.pop_front();
  auto it = a.begin();
  a.remove(it);
  //  *it;

  cout << string(20, '-') << "TESTING CONSTRUCTORS" << string(20, '-') << endl;
  for (int i = 0; i < 4; i++) a.push_back(i);
  DLList<int> c(a);
  DLList<int> d(std::move(a));
  cout << "LIST a(should be empty): ";
  a.print();
  cout << "LIST c: ";
  c.print();
  cout << "LIST d: ";
  d.print();
  cout << endl;
  b = std::move(d);
  a = b;
  cout << "LIST a: ";
  a.print();
  cout << "LIST b: ";
  b.print();
  cout << "LIST d(should be empty): ";
  d.print();

  cout << string(20, '-') << "TESTING ADDING ELEMENTS" << string(20, '-')
       << endl;
  d.push_back(2);
  d.push_back(3);
  d.push_front(1);
  d.push_front(0);
  cout << "\nLIST d: ";
  d.print();
  int var = 15;
  cout << "\t\tOVERLOADED INSERT TEST\n";
  cout << "PASSING AS CONST T&:\n\t";
  d.insert(d.begin(), var);  // 15 => 0 1 2 3
  cout << "PASSING AS T&&:\n\t";
  d.insert(++d.begin(), 25);  // 15 | 25 | 0 1 2 3
  cout << "\nLIST d: ";
  d.print();

  cout << "NEW SIZE OF LIST d: " << d.size() << endl;

  cout << string(20, '-') << "TESTING REMOVING ELEMENTS" << string(20, '-')
       << endl;

  cout << "\nREMOVING FIRST ELEMENT OF LIST b\n";
  b.remove(b.begin());
  cout << "NEW SIZE OF LIST b: " << b.size() << endl;
  cout << "\nREMOVING SECOND ELEMENT OF LIST d\n";
  d.remove(++d.begin());
  cout << "NEW SIZE OF LIST d: " << d.size() << endl;

  cout << "\n\tLISTS b AND d BEFORE pop_back() AND pop_front()\n";
  b.print();
  d.print();
  cout << "\nREMOVING FIRST ELEMENT OF LIST b\n";
  b.pop_front();
  cout << "NEW SIZE OF LIST b: " << b.size() << endl;
  cout << "\nREMOVING LAST ELEMENT OF LIST d\n";
  d.pop_back();
  cout << "NEW SIZE OF LIST d: " << d.size() << endl;
  cout << "\n\tLISTS b AND d AFTER pop_back() AND pop_front()\n";
  b.print();
  d.print();

  cout << "\n\tTESTING REMOVING ELEMENTS WITH ONE ELEMENT IN LIST\n\n";
  DLList<double> k1;
  DLList<double> k2;
  DLList<double> k3;
  cout << "CONTENTS OF LISTS BEFORE\n";
  k1.push_back(24.55);
  k2.push_back(99.1254);
  k3.push_back(148.578);
  cout << "k1: " << *(k1.begin()) << "\tk2: " << *(k2.begin())
       << "\tk3: " << *(k3.begin());
  k1.pop_front();
  k2.pop_back();
  k3.pop_front();
  cout << "\n\nCONTENTS OF LISTS AFTER\n";
  k1.print();
  k2.print();
  k3.print();
  cout << "SIZE OF LISTS: " << k1.size() << k2.size() << k3.size() << endl;

  cout << string(20, '-') << "TESTING ITERATORS" << string(20, '-') << endl;
  cout << "LIST d: ";
  for (auto it = d.begin(); it != d.end(); it++) cout << *it << " ";
  cout << endl;

  cout << "LIST a BEFORE: ";
  a.print();
  auto source = d.begin();
  auto source_end = d.end();
  auto destination = a.begin();

  while (source != source_end) *destination++ = *source++;
  cout << "LIST a AFTER: ";
  a.print();

  cout << string(20, '-') << "TESTING DESTRUCTOR" << string(20, '-') << endl;
  DLList<int> f;
  for (auto i = 0; i < 11; i++) f.push_back(i);
  auto itt = f.begin();
  f.print();

  return 0;
}
