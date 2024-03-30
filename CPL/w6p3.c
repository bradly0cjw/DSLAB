#include <stdio.h>
int main() {
  char a, arr[4000] = {};
  int i, k;
  while (fgets(arr, k = sizeof(arr), stdin) != NULL) {
    for (i = 0; i < k - 1; i++) {
      //第一個字必大寫
      //英文字才能大寫
      //換行後上引號後第一個英文字大寫
      //句點後空格後英文字母大寫
      if (i == 0 ||
          ((((arr[i - 2] == 10 && arr[i - 1] == 34) ||
             (arr[i - 1] == 32 || arr[i - 2] == 46) || arr[i - 1] == 10)) &&

           (arr[i] < 123 && arr[i] > 96))) {
        arr[i] = arr[i] - 32;
      }
    }
    printf("%s", arr);
  }

  return 0;
}