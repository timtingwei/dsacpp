/*  ------------------------------
    Copyright <2018> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:vector_disordered.cpp
   Date:Mon Jan  8 22:16:15 CST 2018
   -----------------------------
*/
/*
  定义无序向量, 没有顺序, 甚至不可能有顺序
  - 寻秩访问
 */

#include <iostream>
#include <vector>
#include <cassert>

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
  // 寻秩访问
  T& operator[](Rank r) const;
  // 测试寻秩访问
  T t;
  // 按秩插入
  void insert(const Rank r, T const &e);
  // 删除区间元素
  int del(Rank lo, Rank hi);
  // 输出Vector对应容量位置上的所有元素
  void print_vector() const;

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

template <typename T>
void Vector<T>::expand() {
  if (_size < _capacity) return;    // 容量未到达不必扩容
  _capacity = std::max(_capacity, DEAFAULT_CAPACITY);    // 不小于最小容量
  // 存储旧元素, 新数组容量扩大一倍
  T* old_elem = _elem; _elem = new T[_capacity <<= 1];
  for (Rank i = 0; i < _size; i++) {
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

// 寻秩访问
/* // my test
template <typename T>
T& Vector<T>::operator[](std::size_t n) {    // 这个类 Vector<T>
  assert(n < _size);
  return _elem[n];
}
*/

template <typename T>
T& Vector<T>::operator[](Rank r) const {   // 不改变数据成员, 定义成常量成员函数
  // 在vector内部, 定义了秩的类型, 统一用Rank
  assert(r < _size);   // 对下标秩进行溢出检测
  return _elem[r];
}

// 插入
/* my test
template <typename T>
void Vector<T>::insert(const Rank r, const int value) {
  // 检查移动后是否需要扩容
  if (++_size > _capacity) expand();
  // 将秩为r后的所有元素后移一位
  for (Rank i = _size-2; i >= r; i--) {     // 为了不覆盖数据, 从尾部开始移动
    _elem[i+1] = _elem[i];     // 向后移动一位
  }
  // 在r秩位置上填入要插入的值
  _elem[r] = value;
}
*/
template <typename T>
void Vector<T>::insert(const Rank r, T const &e) {
  // value不应该是某一中特点的类型, 而应该利用template的特性
  assert(0<= r && r < _size);
  expand();  // 若有必要扩容  结合expand()中, _size < _capacity的定义
  for (int i = _size; i > r; i--)  // 习惯把改变后的值的索引设置成i
    _elem[i] = _elem[i-1];     // 后继元素顺次后移一个单元
  _elem[r] = e; _size++;
}

template <typename T>
void Vector<T>::print_vector() const {
  std::cout << "-- --------print_vector--------- --\n"
            << "_size = " << _size << '\n'
            << "_capacity = " << _capacity << std::endl;
  for (int i = 0; i < _capacity; i++)
    std::cout << i << ':' << _elem[i] << std::endl;
}


// 删除操作
/* my test code
template <typename T>
void Vector<T>::del(const Rank lo, const Rank hi) {
  for (Rank i = lo; i < _size; i++) {
    // 清空区间元素
    if (i < hi) { _elem[i] = 0;
    } else {
      // 将元素整体前移
      _elem[i - (hi-lo)] = _elem[i];
      // 前移后元素清空
       _elem[i] = 0;
    }
  }
  // 缩短规模和空间容量
  _size -= hi-lo; _capacity -= hi-lo;
}
*/


template <typename T>
int Vector<T>::del(Rank lo, Rank hi) {
  // 处理退化情况
  if (lo == hi) return 0;
  // 自前向后的迁移操作
  while (lo < _size) {
    if (hi < _capacity) {_elem[lo++] = _elem[hi++];
    } else {_elem[lo++] = 0;}   // 处理hi++超出_capacityg容量的情况
  }
  // 更新规模或者缩容
  _size = lo;
  // 返回被删除元素的数目
  return hi-lo;
}
// 规模仍旧不变? 删除一段区间, 这里可以不改变规模, 相当于后面留空?
// _elem[hi++]能够被一直索引到? 超过_capacity时, 返回未定义的值
// _elem[hi++]为什么不清空? 把_capacity的剩余空间对应元素赋值给它的方法清空
// 看出移动操作过程中, 变量的同步性
// 缩容不光光是改变_capacity的值, 仍旧要释放空间





int main() {
  // ...
  /*
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
  */
  // -- ------test Vector class----- --
  int vi = 5;
  Rank vr = vi;
  std::cout << "vi = " << vi << '\n'
            << "vr = " << vr << std::endl;

  Rank lo = 0, hi = 5;
  int iarr[] = {1, 3, 5, 7, 9};
  std::cout << "*iarr = " << *iarr << std::endl;
  Vector<int> v(iarr, lo, hi);

  // -- ----test operator[] ---------- --
  std::cout << "v[2] = " << v[2] << std::endl;
  v.t = v[2] + v[3];  // 寻秩访问返回值作为右值
  Vector<int> vi2(iarr, lo+2, hi);
  vi2[2] = v.t;       // 寻秩访问返回值作为左值
  std::cout << "v.t = " << v.t << std::endl;
  std::cout << "vi2[2] = " << vi2[2] << std::endl;
  v.print_vector();

  // -- ----tesr insert() ----------- --
  std::cout << "-- ----tesr insert() ----------- --" << std::endl;
  int insertValue = 12;
  Rank insertRank = 3;
  // v.insert(insertValue, insertRank);
  // v.print_vector();
  int insertCount = 2;
  while (insertCount--) {
    v.insert(insertRank, insertValue);
    v.print_vector();
  }

  // -- -------test del() ---------------- --
  std::cout << "-- -------test del() ---------------- --" << std::endl;
  Rank del_lo = 0, del_hi = 4;
  v.del(del_lo, del_hi);
  v.print_vector();
  return 0;
}


