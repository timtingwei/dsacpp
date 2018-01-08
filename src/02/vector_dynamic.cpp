/*  ------------------------------
    Copyright <2018> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:vector_dynamic.cpp
   Date:Mon Jan  8 10:44:43 CST 2018
   -----------------------------
*/
/*
  在即将发生上溢时，适当的扩大数组内部容量
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
  // 拷贝函数
  void copyFrom(T* const A, Rank lo, Rank hi);
  // 扩容空间
  void expand();
  // /* ... 构造函数 */
  Vector(int c = DEAFAULT_CAPACITY)
  {_elem = new T[_capacity = c]; _size = 0;}     // 默认
  Vector(T* const A, Rank lo, Rank hi)          // 数组区间复制
  {copyFrom(A, lo, hi);}
  Vector(Vector<T> const& V, Rank lo, Rank hi)   // 向量区间复制
  {copyFrom(V, lo, hi);}
  Vector(Vector<T> const& V)                     // 向量整体复制
  {copyFrom(V._elem, 0, V._size);}

  // /* ... 析构函数
  ~Vector() {delete [] _elem;}                   // 释放内部空间
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

/* my test code
template <typename T>
void Vector<T>::expand() {
  if (_size == _capacity) {   // 规模到达最大容量时
    // 创建一个容量更大的数组
    T* _new_elem = new T[_capacity *= 1.2];
    Rank _tmp_size = _size;
    _size = 0;
    // 复制原数组到新数组的对应位置
    copyFrom(this->_elem, 0, _tmp_size);
    // 释放原数组的对应空间，归还系统
    delete [] _elem;
  }
}
*/

template <typename T>
void Vector<T>::expand() {
  if (_size < _capacity) return;    // 容量未到达不必扩容
  _capacity = max(_capacity, DEAFAULT_CAPACITY);    // 不小于最小容量
  // 存储旧元素, 新数组容量扩大
  T* old_elem = _elem; _elem = new T[_capacity <<= 1];
  for (int i = 0; i < _size; i++) {
    _elem[i] = old_elem[i];   // 复制原数组到新数组的对应位置
  }
  delete [] old_elem;    // 释放原数组的对应空间，归还系统
}

/* 上述expand()中, new一个数组储存旧元素, 下面new一个数组, 作为扩容数组
template <typename T>
void Vector<T>::expand() {
  if (_size < _capacity) return;    // 容量未到达不必扩容
  _capacity = max(_capacity, DEAFAULT_CAPACITY);    // 不小于最小容量
  // 存储旧元素, 新数组容量扩大
  T* new_elem = new T[_capacity <<= 1];
  for (int i = 0; i < _size; i++) {
    new_elem[i] = _elem[i];   // 复制原数组到新数组的对应位置
  }
  // ERROR:不能直接赋值, 需要copyFrom(), 这里对_elem的更新不直接, 先新后旧的原则
  _elem = new_elem;      // 当前数组元素更新为新数组元素
  delete [] new_elem;    // 释放临时数组的对应空间，归还系统
}
*/


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


