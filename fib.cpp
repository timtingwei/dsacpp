/*  ------------------------------
    Copyright <2018> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:fib.cpp
   Date:Thu Jan  4 23:55:35 CST 2018
   -----------------------------
*/

#include <iostream>

bool is_exist(int i);

bool is_exist(int i) {
  return (i >= 0 ? true : false);
}

int fib(int n) {
  return (2 > n) ? n : fib(n-1) + fib(n-2);
}


int fib_memoization(int n, int mem_lst[]) {
  // 将已经计算的结果, 制成表备查
  if (is_exist(mem_lst[n])) {
    return mem_lst[n];
  } else {
    if (2 > n) {mem_lst[n] = n;} else {
      mem_lst[n] = fib_memoization(n-1, mem_lst) +
          fib_memoization(n-2, mem_lst);
      return mem_lst[n];
    }
  }
}

int fib_dynamic(int n) {
  int f = 0, g = 1;          // fib(0) = 0; fib(1) = 1;
  while (0 < n--) {
    g = g + f;
    f = g - f;
  }
  return g;
}

int main() {
  // ..
  int T = 47;
  std::cout << "------------- Binary Recursion -------------" << std::endl;
  // for (int i = 0; i < T; i++) {std::cout << "fib" << i << " = "
  //                                        << fib(i) << std::endl;}
  std::cout << "------------- memoization Recursion -------------" << std::endl;
  int mem_lst[100] = {};
  // mem_lst[0] = 0; mem_lst[1] = 1;
  // for (int i = 0; i < T; i++) {mem_lst[i] = -1;}
  // for (int i = 0; i < T; i++) {
    // fib_memoization(i, mem_lst);
    // std::cout << "fib" << i << " = " << mem_lst[i] << std::endl;
  // }
  std::cout << "------------- Linear Recursion -------------" << std::endl;
  for (int i = 0; i < T; i++) {
    std::cout << "fib" << i << " = " << fib_dynamic(i) << std::endl;
  }

  return 0;
}


