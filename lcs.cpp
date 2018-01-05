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
/*
char* lcs(char carr1[], int n, char carr2[], int m, char sub_s[], int n_r) {
  // 返回数组carr_r为最大公共子串 carr1[0,n], carr2[0,m]
  if (n < 0 || m < 0) {
    n_r++;
    sub_s[n_r] = ' ';
    return ' ';
  }
  if (carr1[n] == carr2[m]) {
    n_r++;
    sub_s[n_r] = carr1[n];
    return lcs(carr1, n, carr2, m, sub_s, n_r);
  } else {
    // carr1[n] != carr2[m]
    lcs(carr1, n-1, carr2, m, sub_s, n_r);
    lcs(carr1, n, carr2, m-1, sub_s, n_r);
    return;
  }
}
*/
void test_char(char carr[], int n) {
  std::cout << "*carr = " << *carr << '\n'
            << "sizeof(carr) " << sizeof(carr)/sizeof(carr[0]) << '\n'
            << "carr[n-1] = " << carr[n-1] << '\n'
            << "carr[-1]" << carr[-1] << std::endl;
  char c_value = 'c';
  c_value = c_value + 'a';
  std::cout << "c_value = " << c_value << std::endl;

  carr[4] = 'd';
  std::cout << "carr[4] = " << carr[4] << std::endl;
}


char* fill_carr(char carr[], int n) {
  // 用递归的方法, 将't'填满数组carr
  if (n < 0) return carr;
  carr[n] = 't';
  return fill_carr(carr, n-1);
  // 函数递归的返回类型并不是char*, 只是函数本身的类型
}

int main() {
  // ...

  char carr[] = {'a', 'b', 'c'};
  int n = 3;
  // test_char(carr, n);
  fill_carr(carr, n);
  std::cout << "-- ----print carr after fill_carr()----- -- " << std::endl;
  for (int i = 0; i < n; i++) {std::cout << *(carr+i) << std::endl;}
  return 0;
}


