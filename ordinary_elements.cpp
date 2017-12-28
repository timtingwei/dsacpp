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
void print_abc(const int a, const int b, const int c);


int ordinaryElements(int A[], int n) {
  // 从n >= 3个互异整数中,除最大、最小者以外,任取一个“常规元素”
  // 先比较a,b;再确定c对于(a,b)区间的关系
  int a = A[0], b = A[1], c = A[2];    // 从特定单元读取元素O(3)
  // 统一成区间(a, b), 用于c对其判断
  if (a < b) { } else {
    swap(&a, &b);
  }
  if (c < a) return a;
  else if (c > b) return b;
  else
    return c;
  // return 输出非极端数O(1)

  // =======================================
  // T(n) = O(3) + O(3) + O(1) = O(7) = O(1)
}

int another_ordinaryElements(int A[], int n) {
  // 从n >= 3个互异整数中,除最大、最小者以外,任取一个“常规元素”
  // 先比较a,b;再确定c对于(a,b)区间的关系, 有较多分支
  int a = A[0], b = A[1], c = A[2];                 // 从特定单元读取元素O(3)
  // 统一成区间(a, b), 用于c对其判断
  if (a < b) { } else {
    swap(&a, &b);
  }

  if (c < a) { swap(&c, &a); swap(&c, &b);} else {
    if (b < c) {} else {
      swap(&b, &c);
    }
  }
  // 最多三次比较O(3)

  /*======以上展开=====
  if (c < a) {                           // c 在(-, a)
    // c < a < b;
    // c,a 交换; c,b 交换
    swap(&c, &a);
    swap(&c, &b);
  } else {                               // c 在[a, +)
    // a<b & a>=c; 比较b,c
    if (b < c) {                         // c 在(b, +)
      // a < b < c; 不交换
    } else {                             // c 在[a,b)
      // a <= c < b; 交换b,c
      swap(&b, &c);
    }
  }
  */
  return b;  // 输出非极端数O(1)
  // ===================================
  // T(n) = O(3) + O(3) + O(1) = O(7) = O(1)
}

int my_ordinaryElements(int A[], int n) {
  // 从n >= 3个互异整数中,除最大、最小者以外,任取一个“常规元素”
  // 比较三次，每次比较较大的数的计数值+1, 返回计数为1所对应值
  int x = 0, y = 0, z = 0;
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

void print_abc(const int a, const int b, const int c) {
  std::cout << " a = "<< a << " b = " << b  << " c = " << c << std::endl;
}


int main() {
  int A[] = {1, 3, 2};
  std::cout << "mid value = "  << ordinaryElements(A, 3) << std::endl;
  return 0;
}


