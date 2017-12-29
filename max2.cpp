/*  ------------------------------
    Copyright <2017> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:max2.cpp
   Date:Fri Dec 29 12:07:45 CST 2017
   -----------------------------
*/

#include <iostream>

// 从数组区间A[lo, hi)中找出最大的两个整数A[x1]和A[x2]   // A[x1] > A[x2]
// 比较次数要尽可能的少

int max2(int A[], int lo, int hi);
int max2_three_iters(int A[], int lo, int hi);

int max2_three_iters(int A[], int lo, int hi) {
  int max1 = 0, max2 = 0;
  int x1, x2;
  if (hi < lo) return -1;
  for (int i = lo; i <= hi; i++)
    if (max1 < A[i]) {max1 = A[i]; x1 = i;}

  if (x1 != lo) {
    for (int i_lo  = lo; i_lo < x1; i_lo++)
      if (max2 < A[i_lo]) {max2 = A[i_lo]; x2 = i_lo;}
  }
  if (x1 != hi) {
    for (int i_hi = x1+1; i_hi <= hi; i_hi++)
      if (max2 < A[i_hi]) {max2 = A[i_hi]; x2 = i_hi;}
  }
  int max_array[2] = {max1, max2};
  std::cout << " A[x1] = " << A[x1] << '\n'
            << " A[x2] = " << A[x2] << std::endl;
}

int max2(int A[], int lo, int hi) {
  // 遍历一次，改变指针
  int* x1 = &lo, *x2 = &lo;         // attention:定义指针的方式
  for (int i = lo; i <= hi; i++) {
    if (A[*x2] < A[i]) {      // 索引i的对象比较小的值大
      if (A[*x1] < A[i]) {    // 索引i的对象甚至超过了较大值
        x2 = &(*x1); x1 = &i;
        break;
      }
      x1 = &i;                // x1指针地址指向此时的i
    }
  }
  std::cout << " A[*x1] "  << A[*x1] << '\n'
            << " A[*x2] "  << A[*x2] << std::endl;
}


// 分析:
// 被分解成两个相似问题，mid_sum(n/2)
// 规模每次缩减一半，最后到达递归基
// 将多个问题结果合并

int main() {
  // ..
  int A[] = {9, 2, 3, -1, 5, 10, 9, 15};
  int lo = 0, hi = 7;
  max2(A, lo, hi);
  // test_move_right();
  return 0;
}


