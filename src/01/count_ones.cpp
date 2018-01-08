/*  ------------------------------
    Copyright <2017> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:count_ones
   Date:Thu Dec 28 11:45:54 CST 2017
   -----------------------------
*/

#include <iostream>

// 对于任意非负整数,统计其二进制展开中数位1的总数。
int countOnes(unsigned int n);

int countOnes(unsigned int n) {
  n -= 7;
  return n;
}

int main() {
  // ..
  std::cout << countOnes(5) << std::endl;
  return 0;
}


