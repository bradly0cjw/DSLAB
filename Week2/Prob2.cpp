//
// Created by LINBEI on 9/18/2023.
//
#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class Memory
{
public:
  static T **allocArray(int m, int n) {
      int i;
      T **A = (T **) malloc(m * sizeof(T *));
      for (i = 0; i < m; i++) {
          A[i] = (T *) malloc(n * sizeof(T));
      }
      return A;
  }
};

int main()
{
  int **array;
  array = Memory<int>::allocArray(5, 10);
  int j, k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      cout<<array[j][k]<<" ";
}
