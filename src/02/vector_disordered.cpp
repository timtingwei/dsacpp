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
  // 缩容空间
  void shrunk();
  // 寻秩访问
  T& operator[](Rank r) const;
  // 测试寻秩访问
  T t;
  // 按秩插入
  void insert(const Rank r, T const &e);
  // 删除区间元素
  int remove(Rank lo, Rank hi);
  // 查找e在区间[lo,hi)内
  Rank find(Rank lo, Rank hi, T const &e) const;
  // 测试find()
  T t_f = 8;
  // 删除单元素的操作
  T& remove(Rank r);
  // 唯一化
  int deduplicate();
  // 重载++操作符
  // 测试++操作符
  t_f++;


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

template <typename T>
void Vector<T>::shrunk() {
  if (_size > (_capacity/4)) return;   // 规模大于1/2不必缩容
  _capacity = std::max(_capacity, DEAFAULT_CAPACITY);
  // 储存一份旧元素, 创建新的数据空间
  T* old_elem = _elem; _elem = new T[_capacity >>= 1];
  for (Rank r = 0; r < _size; r++) {
    _elem[r] = old_elem[r];
  }
  // 删除旧元素的内存空间
  delete [] old_elem;
}

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
void Vector<T>::remove(const Rank lo, const Rank hi) {
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
int Vector<T>::remove(Rank lo, Rank hi) {
  // 处理退化情况
  if (lo == hi) return 0;
  const int length = hi - lo;
  // 自前向后的迁移操作
  while (lo < _size) {
    if (hi < _capacity) {_elem[lo++] = _elem[hi++];
    } else {_elem[lo++] = 0;}   // 处理hi++超出_capacityg容量的情况
  }
  // 更新规模或者缩容
  _size -= length;
  shrunk();
  // 返回被删除元素的数目
  return hi-lo;
}
/*
// 规模仍旧不变? 删除一段区间, 这里可以不改变规模, 相当于后面留空? 改进成改变size的版本用于shrunk
// _elem[hi++]能够被一直索引到? 超过_capacity时, 返回未定义的值
// _elem[hi++]为什么不清空? 把_capacity的剩余空间对应元素赋值给它的方法清空
// 看出移动操作过程中, 变量的同步性
// 缩容不光光是改变_capacity的值, 仍旧要释放空间
*/

// 查找
/* my test code
template <typename T>
int Vector<T>::find(Rank lo, Rank hi, T const &e) const {
  // 查找e在区间[lo,hi)内
  // 从右往左查找
  while (hi >= lo) {
    if (_elem[hi] == e) {return hi;
    }
    hi--;
  }
  // 没有在while循环中返回, 不存在匹配元素
  return -1;
}
*/

template <typename T>
Rank Vector<T>::find(Rank lo, Rank hi, T const &e) const {
  // O(hi - lo) = O(n), 在命中多个元素时可返回秩最大者
  while (lo < hi-- && e != _elem[hi]) {}   // 逆向查找
  return hi;   // hi < lo失败; 否则hi即命中元素的秩
}
// 利用while本身的条件语句；后置递增的特性
// 返回hi? 将判断是否成功, 交给上层的调用者;以及成功后被上层算法进一步利用

// 删除单个元素
/* my test code
template <typename T>
void Vector<T>::remove(Rank r) {
  // 单元素的删除操作, 视为区间操作的特例 [r, r+1)
  remove(r, r+1);
}
*/
template <typename T>     // 删除向量中秩为r的元素, 0 <= r < size
T& Vector<T>::remove(Rank r) {  // O(n-r)
  T& old_t = _elem[r];    // 备份被删除的元素
  remove(r, r+1);         // 调用区间删除算法
  return old_t;           // 返回被删除元素
}

// 唯一化
/*
template <typename T>
void Vector<T>::deduplicate(Rank lo, Rank hi) {
  // 对向量中的元素遍历,
  for (Rank i = lo; i < hi; i++) {
    // find右往左查, 返回lo-1代表失败
    // 删除当前元素, 不再对后续元素查找
    if (find(lo, i, _elem[i]) != lo-1) {remove(i); break;}
    if (find(i+1, hi, _elem[i]) != i) { remove(i);}
  }
}
*/

template <typename T>
int Vector<T>::deduplicate() {
  int old_size = _size;
  Rank i = 1;
  while (i < _size) {
    find(0, i, _elem[i]) < 0 ?
                             i++  // 小于0说明无雷同, 继续查找
                             : remove(i);    // 删除雷同者(至多一个?!)
  }
  return  old_size - _size;      // 返回规模的变化量
}

/*
template <typename T>
struct Increase {
  virtual void operator()(T &e) {e++;}
};
*/



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
  // std::cout << "-- ------test Vector class----- --" << std::endl;
  int vi = 5;
  Rank vr = vi;
  // std::cout << "vi = " << vi << '\n'
  //           << "vr = " << vr << std::endl;

  Rank lo = 0, hi = 5;
  int iarr[] = {1, 3, 5, 7, 9};
  // std::cout << "*iarr = " << *iarr << std::endl;
  Vector<int> v(iarr, lo, hi);

  // -- ----test operator[] ---------- --
  // std::cout << "-- ------test operator----- --" << std::endl;
  // std::cout << "v[2] = " << v[2] << std::endl;
  v.t = v[2] + v[3];  // 寻秩访问返回值作为右值
  Vector<int> vi2(iarr, lo+2, hi);
  vi2[2] = v.t;       // 寻秩访问返回值作为左值
  // std::cout << "v.t = " << v.t << std::endl;
  // std::cout << "vi2[2] = " << vi2[2] << std::endl;
  // v.print_vector();

  // -- ----tesr insert() ----------- --
  // std::cout << "-- ----tesr insert() ----------- --" << std::endl;
  int insertValue = 12;
  Rank insertRank = 3;
  // v.insert(insertValue, insertRank);
  // v.print_vector();
  int insertCount = 2;
  while (insertCount--) {
    v.insert(insertRank, insertValue);
    // v.print_vector();
  }

  // -- -------test remove() ---------------- --
  std::cout << "-- -------test remove() ---------------- --" << std::endl;
  Rank del_lo = 0, del_hi = 2;
  v.remove(del_lo, del_hi);
  v.print_vector();

  // -- -------test find() --------------- --
  std::cout << "-- -------test find() --------------- --" << std::endl;
  v.insert(4, 5);
  Rank find_lo = 0, find_hi = 7;
  std::cout << "v.t_f index = " << v.find(find_lo, find_hi, v.t_f) <<std::endl;
  v.print_vector();
  // -- -------test remove() -------------- --
  std::cout << "-- -------test remove() -------------- --" << std::endl;
  Rank remove_r = 3;
  std::cout << "v.remove(remove_r) = " << v.remove(remove_r) << std::endl;
  v.print_vector();
  // -- -------test deduplicate() ----------------- --
  std::cout << "-- -------test deduplicate() ----------------- --" << std::endl;
  Rank set_lo = 0, set_hi = 4;
  v.deduplicate();
  v.print_vector();
  return 0;
}


