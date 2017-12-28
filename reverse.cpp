/*  ------------------------------
    Copyright <2017> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:reverse.cpp
   Date:Thu Dec 28 22:34:22 CST 2017
   -----------------------------
*/

#include <iostream>

// 任给数组A[0,n), 将其前后颠倒  // 更一般的子区间[lo, hi]

void reverse(int* A, int lo, int hi);
void reverse_iterate_original(int* A, int lo, int hi);
void reverse_iterate(int* A, int lo, int hi);
void swap(int* a, int* b);
void print_array(int* A, int lo, int hi);

// test C++
void test_arrayPtr(int* A);
void test_add();


void reverse(int* A, int lo, int hi) {
  // 输入指向数组A的指针, A中要转置的左区间lo， A中要转置的右区间lo
  // 无返回值，改变指针A所指向的数组, 使其倒序
  if (lo < hi) {
    swap(&(A[lo]), &(A[hi]));
    if (((hi-lo) == 1) || ((hi - lo) == 0)) return;
    reverse(A, lo + 1, hi - 1);
  }
}

void reverse_iterate_original(int* A, int lo, int hi) {
  // 迭代原始版本
next:
  if (lo < hi)
  {swap(&A[lo], &A[hi]); lo++; hi--; goto next;}
}

void reverse_iterate(int* A, int lo, int hi) {
  // 迭代版本
  while (lo < hi) swap(&A[lo++], &A[hi--]);
}

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b; *b = tmp;
}

void print_array(int* A, int lo, int hi) {
  for (int i = lo; i <= hi; i++)
    std::cout << A[i] << std::endl;
}


int main() {
  // ...

  // third point
  int A[] = {1, 2, 3, 4, 5};
  int lo = 1, hi = 3;
  // reverse(A, lo, hi);
  // reverse_iterate(A, lo, hi);
  reverse_iterate_original(A, lo, hi);
  print_array(A, lo, hi);

  // ...
  // std::cout << " A[0] = " << A[0] << std::endl;
  // test_arrayPtr(A);
  // test_add();

  return 0;
}


void test_add() {
  int a;
  int lo = 5;
  a = lo++;    // 后置递增， 递增前的value给a
  std::cout << "a = " << a << '\n'
            << "lo = " << lo << std::endl;
    std::cout << "-----finish test_add()---" << std::endl;
}

void test_arrayPtr(int* A) {
  std::cout << "*A = " << *A  << '\n'
            << "*(A+1) = " << *(A+1) << '\n'
            << "*(A+2) = " << *(A+2) << '\n'
            <<"A [1]= " << A[1] << std::endl;
  A[0] = 5;
  std::cout << "-----finish test_arrayPtr---" << std::endl;
} 

