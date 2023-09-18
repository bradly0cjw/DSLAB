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
//      non-consecutive memory
//      int i;
//      T **A = (T **) malloc(m * sizeof(T *));
//      for (i = 0; i < m; i++) {
//          A[i] = (T *) malloc(n * sizeof(T));
//      }
//      return A;

//    in C++ we can use new function as malloc in C (it's okay to use malloc in C++)
      T **A = new T*[m];
      //init memory for each row
      int *block=new T[m*n];
      //init memory for whole array
      for (int i=0;i<m;i++) {
          A[i] = block + i * n;
          //by adding block memory address let 2d array functional
      }
      return A;
      //this is not void function needs to return Memory
  }
};

int main()
{
  int **array;
  array = Memory<int>::allocArray(5, 10);
//  array = allocArray<int>(5, 10);
  int j, k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      cout<<array[j][k]<<" ";
}
