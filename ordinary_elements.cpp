/*  ------------------------------
    Copyright <2017> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:ordinary_elements
   Date:Thu Dec 28 09:15:13 CST 2017
   -----------------------------
*/


#include <iostream>

int ordinaryElements(int A[], int n);
void swap(int* a, int* b);

int ordinaryElements(int A[], int n) {
  // 从n >= 3个互异整数中,除最大、最小者以外,任取一个“常规元素”
  // int x = A[0], y = A[1], z = A[2];
  int x = 0, y = 0, z = 0;
  // x = 3, y = 1, z =2;
  (A[1] < A[0]) ? x++ : y++;
  (A[2] < A[1]) ? y++ : z++;
  (A[2] < A[0]) ? x++ : z++;
  if (x == 1) return A[0];
  else if (y == 1) return A[1];
  else if (z == 1) return A[2];
}

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b; *b = tmp;
}

int main() {
  int A[] = {1, 3, -1};
  std::cout << "mid value = "  << ordinaryElements(A, 3) << std::endl;
  return 0;
}


