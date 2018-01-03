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
int print_array(int A[], int lo, int hi);


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

// 做一次循环，改变指针所指向的对象，x1指向最大值, x2指向次大值, 先比较x2
int max2_one_iter(int A[], int lo, int hi) {
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


// 递归分成两部分, 左边的最大值和右边的最大值比较, 得到最大值;
// 较小的值和最大值列表中的次大值比较, 得到整体的次大值

void max2(int A[], int lo, int hi, int & x1, int & x2) {     // [lo, hi)
  if (lo + 2 == hi) {
    if (A[lo] < A[lo+1]) {
      x1 = A[lo+1]; x2 = A[lo];
    } else {
      x2 = A[lo+1]; x1 = A[lo];
    }
    return;
  }                         // T(2) = 1
  if (lo + 3 == hi) {       // lo, lo+1, lo+2, lo+3; 19, 2, 3, -1;
    x1 = lo, x2 = lo+1;
    if (A[x1] < A[x2]) {x1 = lo+1; x2 = lo;}
    for (int i = lo+2; i < hi+1; i++) {
      if (A[i] > A[x2]) {
        if (A[i] > A[x1]) {
          int tmp = x1;
          x1 = i; x2 = tmp;
          break;
        }
        x2 = i;
      }
    }
    return;
  }                         // T(3) <= 3
  int mid = (lo + hi) >> 1;
  int x1L, x2L; max2(A, lo, mid, x1L, x2L);
  int x1R, x2R; max2(A, mid+1, hi, x1R, x2R);
  if (A[x1L] > A[x1R]) {
    x1 = x1L; x2 = (x2L < x1R) ? x1R:x2L;
  } else {
    x1 = x1R; x2 = (x2R < x1L) ? x1L:x2R;
  }
}

int print_array(int A[], int lo, int hi) {
  std::cout << "-- -----array-------- --" << std::endl;
  for (int i = lo; i < hi+1; i++)
    std::cout << i << " : " << A[i] << std::endl;
}

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
  int A[] = {13, 2, -1, 3, 5, 15, 9, 19};
  int lo = 0, hi = 7;
  int x1, x2;
  max2(A, lo, hi, x1, x2);
  std::cout << "-- -------------- --\n" <<"A[x1] = " << A[x1]
            << " A[x2] = " << A[x2] << std::endl;
  // print_array(A, lo, hi);
  // test_move_right();
  // test_ptr();
  return 0;
}


