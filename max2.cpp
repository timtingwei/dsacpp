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
  int* x1 = &lo;
  int lo_next = lo + 1;
  int* x2 = &lo_next;
  if (A[*x1] < A[*x2]) {x1 = &lo_next; x2 = &lo;}
  for (int i = lo + 2; i <= hi; i++) {
    if (A[*x2] < A[i]) {      // 索引i的对象比较小的值大
      if (A[*x1] < A[i]) {    // 索引i的对象甚至超过了较大值
        x2 = &(*x1); x1 = &i;
        break;
      }
      *x2 = i;                // x1指针指向的元素赋值成i
    }
  }
  std::cout << " A[*x1] "  << A[*x1] << '\n'
            << " A[*x2] "  << A[*x2] << std::endl;
}

/*
int max2(int A[], int lo, int hi, int & x1, int &x2) {
  if (A[x1 = lo] < A[x2 = lo + 1]) swap(x1, x2);
  for (int i = lo + 2; i < hi; i++)
    if (A[x2] < A[i])
      if (A[x2] < A[x2 = i])
        swap(x1, x2);
}
*/


// 分析:
// 被分解成两个相似问题，mid_sum(n/2)
// 规模每次缩减一半，最后到达递归基
// 将多个问题结果合并

void test_ptr() {
  int i = 5, i2 = 2;
  int* ip = &i;
  int &ir = i;
  // ip = &(i+6);
  // *ip = i2;       // *ip = 2; i = 2;   *ip代表i, i2赋值给i
  ip = &i2;       // *ip = 2; i = 5;   ip地址指向i2
  std::cout << "*ip = " << *ip << '\n'
            << "i = " << i << '\n'
            << std::endl;
  std::cout << "ir = " << ir << std::endl;
}

int main() {
  // ..
  int A[] = {19, 2, 3, -1, 5, 10, 9, 15};
  int lo = 0, hi = 7;
  max2(A, lo, hi);
  // test_move_right();
  // test_ptr();
  return 0;
}


