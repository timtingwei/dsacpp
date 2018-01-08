/*  ------------------------------
    Copyright <2017> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:bubblesort
   Date:Thu Dec 28 07:41:28 CST 2017
   -----------------------------
*/

#include <iostream>


void swap(int*, int*);
void print_array(int A[], int length);

void bubblesort(int A[], int n) {
  const int length = n+1;
  for (bool sorted = false; sorted = !sorted; n--)
    for (int i = 1; i < n+1; i++) {  // 自左向右逐对检查[0,n)各相邻元素
      if (A[i-1] > A[i]) {         // 若逆序,则
        swap(&A[i-1], &A[i]);      // 令其交换位置
        sorted = false;            // 消除全局有序标记
      }
    }
  print_array(A, length);
}



void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b; *b = tmp;
}

void print_array(int A[], int length) {
  if (length != 0) {
    for (int i = 0; i < length; i++)
     std::cout << A[i] << std::endl;
  } else {
    std::cout << "array length is zero" << std::endl;
  }
}

int main() {
  int A[] = {2, -1, -3, 7, 10,  7, 10};
  int n = 6;
  bubblesort(A, n);
  return 0;
}


