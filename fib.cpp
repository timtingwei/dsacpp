/*  ------------------------------
    Copyright <2018> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:fib.cpp
   Date:Thu Jan  4 23:55:35 CST 2018
   -----------------------------
*/

#include <iostream>


int fib(int n) {
  return (2 > n) ? n : fib(n-1) + fib(n-2);
}

int main() {
  // ..
  int T = 40;
  std::cout << "------------- Binary Recursion -------------" << std::endl;
  for (int i = 0; i < T; i++) {std::cout << "fib" << i << " = "
                                          << fib(i) << std::endl;}
  return 0;
}


