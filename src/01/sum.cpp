/*  ------------------------------
    Copyright <2017> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:sum.cpp
   Date:Thu Dec 28 21:45:01 CST 2017
   -----------------------------
*/

#include <iostream>

int sum(int A[], int n);
int mid_sum(int A[], int lo, int hi);

void test_move_right();

// 求n个总数之和

// -------------------减而治之----------------------------
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


// -------------------分而治之----------------------------

int mid_sum(int A[], int lo, int hi) {
  // 数组求和 :二分递归
  if (lo == hi) return A[lo];
  int mid = (lo + hi) >> 1;
  return mid_sum(A, lo, mid) + mid_sum(A, mid + 1, hi);
}

// 分析:
// 被分解成两个相似问题，mid_sum(n/2)
// 规模每次缩减一半，最后到达递归基
// 将多个问题结果合并

int main() {
  // ..
  int A[] = {1, 2, 3, 4, 5, 8, 9, 10};
  int n = 8;
  int lo = 0, hi = 7;

  std::cout << "sum() = " << sum(A, n) << std::endl;
  std::cout << "mid_sum() = " << mid_sum(A, lo, hi) << std::endl;

  // test_move_right();
  return 0;
}



void test_move_right() {
  // 测试右移动运算符, 除以2后向下取整数
  int n = -3;
  int n_moved = n >> 1;    // floor(n/2)
  std::cout << "n_moved = " << n_moved << std::endl;
}
