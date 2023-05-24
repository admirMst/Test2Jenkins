#include <iostream>
#include "DLList.hpp"

using namespace std;

int main(void)
{
  DLList<int> A;
  for(int i=1; i<7 ; i++) A.push_back(i);

  A.print();
  
  A.swapp();
  A.print();
  A.swapp();
  A.print();
  return 0;
}
