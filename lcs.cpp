/*  ------------------------------
    Copyright <2018> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:lcs.cpp
   Date:Fri Jan  5 16:45:33 CST 2018
   -----------------------------
*/

#include <iostream>

/*
int fib_dynamic(int n) {
  int f = 0, g = 1;          // fib(0) = 0; fib(1) = 1;
  while (0 < n--) {
    g = g + f;
    f = g - f;
  }
  return g;
}
*/

void test_char(char carr[], int n) {
  std::cout << "*carr = " << *carr << '\n'
            << "sizeof(carr) " << sizeof(carr)/sizeof(carr[0]) << '\n'
            << "carr[n-1] = " << carr[n-1] <<std::endl;
}

int main() {
  // ...

  char carr[] = {'a', 'b', 'c'};
  int n = 3;
  test_char(carr, n);
  return 0;
}


