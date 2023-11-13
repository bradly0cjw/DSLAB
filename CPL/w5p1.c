//
// Created by LINBEI on 11/13/2023.
//
#include <stdio.h>

////泡沫排序
void bubble_sort(long arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[i]) {
                long temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}

///特殊排序
void com(long arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] < arr[j]) {
                long temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
            if (arr[i] % 2 != 0) {
                long temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}

int main(void) {
    int N, M, i, j, v, p, q, n = 0, ans;
    long num = 0;
    while (scanf("%d %d", &N, &M), N != 0 && M != 0) {
        long arr[N], arr1[N], arr_ans[N];
        ans = 0;
        p = N, q = M;
        for (i = 0; i < N; i++) {
            scanf("%ld\n", &num);
            arr[i] = num;
        }
        bubble_sort(arr, N);
        printf("%d %d\n", p, q);
        ///把餘數為0~M的數慢慢輸出到另外的陣列中，並且按照餘數大小進行排列
        for (j = (-M + 1); j < M; j++) {
            for (i = 0, v = 0; i < N; i++) {
                if (arr[i] % M == j) {
                    arr1[v] = arr[i];
                    v++;
                }
            }
            com(arr1, v);
            for (i = 0; i < v; i++) {
                arr_ans[ans] = arr1[i];
                ans++;
            }
        }
        for (i = 0; i < N; i++) {
            printf("%ld\n", arr_ans[i]);
        }
        n++;
    }
    printf("%d %d\n", 0, 0);
    return 0;
}