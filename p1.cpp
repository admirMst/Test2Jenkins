#include <iostream>
#include "DLList.hpp"

using namespace std;
int main() {
  DLList<int> A;
  for (int i = 1; i < 11; i++) A.push_back(i);

  A.print();

  A.remove(A.begin()+2,A.begin()+3);

  A.print();

  return 0;
}
