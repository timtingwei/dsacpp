/*  ------------------------------
    Copyright <2018> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:vector.cpp
   Date:Sat Jan  6 08:41:27 CST 2018
   -----------------------------
*/

#include <iostream>
#include <vector>

typedef int Rank;             // 秩
#define DEAFAULT_CAPACITY 3   // 默认初始容量

template <typename T> class Vector {   // 向量模板类
 private:
  Rank _size; int _capacity; T* _elem;   // 规模, 容量, 数据区
 protected:
  /* ... 内部函数*/
 public:
  // /* ... 构造函数
  void copyFrom(T* const A, Rank lo, Rank hi);
  Vector(int c = DEAFAULT_CAPACITY)
  {_elem = new T[_capacity = c]; _size = 0;}     // 默认
  Vector(T* const A, Rank lo, Rank hi)          // 数组区间复制
  {copyFrom(A, lo, hi);}
  Vector(Vector<T> const& V, Rank lo, Rank hi)   // 向量区间复制
  {copyFrom(V, lo, hi);}
  Vector(Vector<T> const& V)                     // 向量整体复制
  {copyFrom(V._elem, 0, V._size);}
  //  */
  // /* ... 析构函数
  ~Vector() {delete [] _elem;}                   // 释放内部空间
  // */
  /* ... 只读函数*/
  /* ... 可写函数*/
  /* ... 遍历函数*/
};

template <typename T>
void Vector<T>::copyFrom(T* const A, Rank lo, Rank hi) {
  _elem = new T[_capacity = 2*(hi- lo)];      // 分配空间
  _size = 0;  // 清零规模
  while (lo < hi)   // A[lo, hi)中的元素逐一
    _elem[_size++] = A[lo++];
}

int main() {
  // ...
  std::vector<int> vec;
  // vec.insert(0, 9, 2);
  // vec.put(1, 2);
  // vec.get(2);
  // vec.remove(3);
  vec.size();
  // vec.disordered();
  // vec.find(9);
  // vec.sort();
  // vec.search();
  // vec.uniquify();
  // print vector;
  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << std::endl;
  }
  // ---test array---
  // int i;
  // int arr[i = 5] = {};
  // -- ------test Vector class----- --
  int vi = 5;
  Rank vr = vi;
  std::cout << "vi = " << vi << '\n'
            << "vr = " << vr << std::endl;

  Rank lo = 0, hi = 5;
  int iarr[] = {1, 3, 5, 7, 2};
  std::cout << "iarr = " << iarr << std::endl;
  Vector<int> v(iarr, lo, hi);
  return 0;
}


