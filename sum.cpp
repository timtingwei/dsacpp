/*  ------------------------------
    Copyright <2017> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:sum.cpp
   Date:Thu Dec 28 21:45:01 CST 2017
   -----------------------------
*/

#include <iostream>

// 求n个总数之和

int sum(int A[], int n) {
  // A为整数数组, n为问题规模, 返回数组中整数的总和
  return
      (n < 1) ?
      0 : sum(A, n-1) + A[n-1];
}

// 分析:
// 该问题分解为一个缩减问题sum(A, n-1) 和 一个平凡问题A[n-1]
// 最后规模小到一定程度时， 缩减问题变为 平凡问题
// 将两个问题合并得到结果


int main() {
  // ..
  int A[] = {1, 2, 3, 4, 5};
  int n = 5;
  // A[4] + A[3] + A[2] + A[1] + A[0] + 0;
  std::cout << sum(A, n) << std::endl;
  return 0;
}


