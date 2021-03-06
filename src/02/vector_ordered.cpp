/*  ------------------------------
    Copyright <2018> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:vector_ordered.cpp
   Date:Thu Jan 11 19:51:31 CST 2018
   -----------------------------
*/
/*
  定义有序向量
 */

#include <iostream>
#include <vector>
#include <cassert>

typedef int Rank;             // 秩
#define DEAFAULT_CAPACITY 3   // 默认初始容量

template <typename T>
class Vector {   // 向量模板类
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
  // 寻秩访问, 重载[]运算符
  T& operator[](Rank r) const;
  // 重载前置++操作符
  T& operator++();
  // 重载后置++操作符
  T* operator++(int);
  // 测试++操作符
  // t_f++;
  // 重载前置--操作符
  T& operator--();
  // 重载后置--操作符
  T* operator--(int i);
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

  template <typename VST> void traverse(VST visit);
  // template <typename VST> virtual void traverse(VST visit, T* e);
  template <typename VST> T& traverse(VST visit, T* e);
  // 输出Vector对应容量位置上的所有元素
  void print_vector() const;
  // ==================== 有序向量 ==============================
  // 逆序程度
  int disordered() const;
  // 唯一化(低效)
  int deduplicate_lower(int rm_arr[]);
  // 为了定义 外部数组大小, 而定义的返回私有数据的函数
  int get_size() const {return _size;}  // 外部大小数组不能用变量定义
  // 唯一化所依赖的通过索引数组一次性remove函数
  void remove(int rm_arr[], int n);
  // int deduplicate_lower(int rm_arr[]);

  // 有序向量唯一化(低效版)
  int uniquify();
  // 有序向量唯一化(高效版)
  int uniquify_faster();




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
  if (_size > (_capacity/2)) return;   // 规模大于1/2不必缩容
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


// 重载前置++操作符
template <typename T>
T& Vector<T>::operator++() {
  // 所有元素都+1
  for (Rank i = 0; i < _size; i++)
    _elem[i]++;
  return *_elem;     // 返回+1后的数据
}

// 重载后置++操作符
template <typename T>
T* Vector<T>::operator++(int i) {
  T* e = _elem;      // 备份当前元素
  // for (Rank i = 0; i < _size; i++)
  //   _elem[i]++;   // 循环递增所有元素
  ++*this;           // 调用前置递增++, 递增所有元素
  return e;          // 返回递增前的元素
}


// 单个T类型元素加1的类
template <typename T>
struct Increase {
  virtual void operator()(T &e) {e++;}    // Increase<T>()实现函数功能  
};

template <typename T> template <typename VST>
void Vector<T>::traverse(VST visit) {       // 函数对象, 全局修改 
  for (int i = 0; i < _size; i++) visit(_elem[i]);
}


template <typename T>
void increase(Vector<T> & V) {
  V.traverse(Increase<T>());
}


template <typename T>
T& Vector<T>::operator--() {          // 重载前置--操作符
  for (int i = 0; i < _size; i++)
    _elem[i]--;                    // 对每个元素-1
  return *_elem;                    // 返回当前 *this or *_elem
}

// 为什么返回*_elem 而不是 *this??
// 递减运算符重载函数的返回类型, 的返回类型是int&
  //, *this的类型为Vector<int>, 而*_elem 的类型是int


// 运用函数对象机制遍历减一Vector中的元素
template <typename T>
T* Vector<T>::operator--(int i) {          // 重载后置--操作符
  T* e = _elem;
  --*this;                         // 调用前置递减
  return e;
}


// 遍历运用函数对象机制，对各个元素减1
/* my test code
// 单个T类型元素减1的类
template <typename T>
Vector<T>::struct Decrease {
  virtual void operator() {T &e--;}     // 重载()操作, 类对象当作函数来用
};

template <typename T>
void decrease(Vector<T>& V) {
  V.traverse(Decrease<T>());
}
// 泛型模板在调用的时候都要带<type>
*/

template <typename T>
struct Decrease {
  virtual void operator()(T &e) {e--;}
};

/*
// 为什么不是Vector<T>::struct Decrease?
// Decrease对象, 不需要声明在vector类内, 这是借用函数对象作为traverse的参数, traverse声明在类内, 这个参数的类型是VST, 即函数对象。
// 为什么需要virtual
// void operator()(T &e)?
// 第一个括号是代表重载运算符是(), 第二个是该重载函数的参数列表
*/

template <typename T>
void decrease(Vector<T> & V) {
  V.traverse(Decrease<T>());
}

// 在类的外部定义decrease函数, 它具有泛型T, 参数为Vector<T>& 类型
// 函数内部, 实例V调用traverse方法, 通过多次调用这个函数对象去遍历所有元素

// 终极问题: 为什么需要函数对象or 函数指针,  为什么不直接调用函数呢?


// 用于traverse的加倍函数对象
template <typename T>
struct Double_value {
  virtual void operator()(T& e) {e *= 2;}   // 函数对象对元素翻倍
};

template <typename T>
void double_value(Vector<T>& V) {
  V.traverse(Double_value<T>());      // 函数对象作为遍历函数的参数
}

// 用于traverse的求和函数对象
template <typename T>
struct Sum {
  virtual void operator()(const T& e, T* sumPtr) {(*sumPtr) += e;}
};


template <typename T> template <typename VST>
T& Vector<T>::traverse(VST visit, T* e) {
  // 重载traverse(), 对Sum对象函数传入保存求和结果的指针
  for (int i = 1; i < _size; i++) visit(_elem[i], e);   // 从第二个值开始累加
  return *e;       // 返回求和结果
}


template <typename T>
void sum_ptr(Vector<T>& V) {
  T sum_init = V[0];              // 创建一个副本, 避免通过指针修改V[0]
  T* sumPtr = &(sum_init);        // 别定义空指针, 该指针指向副本
  T sum = V.traverse(Sum<T>(), sumPtr);     // 调用并赋值
  std::cout << "sum = " << sum << std::endl;
}

// 通过类内static求和的函数对象
template <typename T>
struct Sum_static {
  static T sum_t;     // 内部声明存放求和结果的static变量
  virtual void operator()(T& e) {
    sum_t += e; std::cout << "revise static sum_t, sum_t = "
                          << sum_t << std::endl;    // 当心全局变量出错
  }
};

template <typename T>
T Sum_static<T>::sum_t = 0;   // 外部定义静态数据成员

template <typename T>
void sum_static(Vector<T> V) {
  Sum_static<T> sumstc;           // 实例化模板别忘记<type>
  V.traverse(Sum_static<T>());
  T sum = sumstc.sum_t;
  std::cout << "in sum_static, sum = " << sum << std::endl;
}

// 逆序程度
/* my test code 
template <typename T>
int Vector<T>::disordered() const {
  int count = 0;
  for (int i = 0; i < _size - 1; i++)
    if (_elem[i] != _elem[i+1]) count++;  // ERROR: 逆序:前个元素大于后一元素
  return count;
}
*/

template <typename T>
int Vector<T>::disordered() const {
  int count = 0;   // 计数器
  for (int i = i; i < _size; i++)
    count += (_elem[i-1] > _elem[i]);    // 逆序对则计数+1, bool和int的隐式转换
  return count;
}

template <typename T>
int Vector<T>::deduplicate_lower(int rm_arr[]) {
  // 删除有序向量重复的元素, rm_arr是保存删除对象索引数组, 返回被删除元素的数量
  assert(!disordered());   // 当前为有序向量
  Rank n = 0;            // 数组当前插入位置
  Rank r1 = 0, r2 = 1;   // 创建两个索引值线性扫描
  while (r2 < _size) {
    if (_elem[r1] == _elem[r2]) {   // r2指向的元素和r1对应元素重复
      rm_arr[n++] = r2;     // 索引数组中加入r2
      // remove(r2);
    } else { r1 = r2;}
    r2++;    // 递增r2
  }
  remove(rm_arr, n);   // 一次性删除索引对应的元素
  return n;            // 返回删除元素数量
}




// 有序向量唯一化所依赖的通过索引数组一次性remove函数
template <typename T>
void Vector<T>::remove(int rm_arr[], int n) {
  // 删除索引除外的索引对应元素保留, 从左向右扫描
  int i_n = 0;     // 指向rm_arr中的元素
  int new_i = 0;   // 保留索引
  T* old_elem = _elem;    // 备份一份当前元素
  _elem = new T[_capacity = _capacity];
  for (int i = 0; i < _size; i++) {
    if (i != rm_arr[i_n]) {     // 当前索引不在表中
      _elem[new_i++] = old_elem[i];   // 当前索引对应元素赋值给当前元素的新位置
    } else {     // 当前索引在删除索引的表中
      i_n++;     // 指向下一个rm_arr中的元素
    }
  }
  _size -= n;
  delete [] old_elem;
}

// 有序向量唯一化
template <typename T>
int Vector<T>::uniquify() {
  int old_size = _size; int i = 0;
  while (i < _size - 1) {
    (_elem[i+1] == _elem[i]) ? remove(i+1) : i++;
  }    // _size的改变由remove隐式完成
  return old_size - _size;
}

// 有序向量唯一化高效版本
/* my test code
template <typename T>
int Vector<T>::uniquify_faster() {
  int i = 0, j = 1;   // i指向首位置
  int old_size = _size; T* old_elem = _elem;  // 备份原有元素
  _elem = new T[_capacity = _capacity];
  _elem[0] = old_elem[0]; int n = 1;   // 存入首元素, 索引指向第二位
  while (i < old_size - 1)
    if (old_elem[i] != old_elem[j]) {
      _elem[n++] = old_elem[j]; i = j++;
    } else {j++; _size--;}
  delete [] old_elem;
  return old_size - n;
}
*/

template <typename T>
int Vector<T>::uniquify_faster() {
  int i = 0, j = 0;   // 两个计数都指向首元素
  while (++j < _size) {   // j扫描到末尾
    if (_elem[i] != _elem[j]) {_elem[++i] = _elem[j];}  // j指向元素移到i后
  }
  _size = ++i; shrunk();      // 改变_size数值后, 缩容
  return j - i;    // 注意j扫到尾端的特性
}     // 依赖shrink();

/*
// 为什么不要另外的n作为索引计数?
当j移动至i后, 计数i也增加, 重新指向移动位置后的j, 不需要对原有那份的拷贝即可完成索引操作。记录位置只用i。算法设计时，也考虑一个操作是否必要。一份复制是否必要。
// 为什么不在uniquify中进行new 和 delete?
接口分离的体现, 在函数中改变_size, 通过_size的改变, 再由shrunk/expand对空间进行操作。
*/


// ============================ split line ==========================
template <typename T>
void f_disordered(Vector<T> v) {
  std::cout << "-- ------test Vector disordered() ----- --\n";
  std::cout << "v.disordered()::count = " << v.disordered() << std::endl;
  v.print_vector();
}


template <typename T>
void f_dedepulicate_lower(Vector<T> v) {
  std::cout << "-- ------test Vecto::dedepulicate_lower() ----- --\n";
  // int i = v.get_size();
  Rank rm_arr[50]= {};
  // Vector<int> rm_arr;
  v.print_vector();
  int rm_count = v.deduplicate_lower(rm_arr);
  std::cout << "remove count = " << rm_count << std::endl;
  v.print_vector();
}

template <typename T>
void f_uniquify(Vector<T> v) {
  std::cout << "-- ------test Vecto::uniquify() ----- --\n";
  v.print_vector();
  int rm_count = v.uniquify();
  std::cout << "remove count = " << rm_count << std::endl;
  v.print_vector();
}

template <typename T>
void f_uniquify_faster(Vector<T> v) {
  std::cout << "-- ------test Vecto::uniquify_faster() ----- --\n";
  v.print_vector();
  int rm_count = v.uniquify_faster();
  std::cout << "remove count = " << rm_count << std::endl;
  v.print_vector();
}

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
  // int vi = 5;
  // Rank vr = vi;
  // std::cout << "vi = " << vi << '\n'
  //           << "vr = " << vr << std::endl;

  Rank lo = 0, hi = 8;
  int iarr[] = {1, 3, 3, 3, 5, 7, 9, 9};
  // int iarr[] = {1, 1, 1, 1, 1, 1, 1, 1};
  Vector<int> v(iarr, lo, hi);

  // // -- ----test operator[] ---------- --
  // // std::cout << "-- ------test operator----- --" << std::endl;
  // // std::cout << "v[2] = " << v[2] << std::endl;
  // // v.t = v[2] + v[3];  // 寻秩访问返回值作为右值
  // // Vector<int> vi2(iarr, lo+2, hi);
  // // vi2[2] = v.t;       // 寻秩访问返回值作为左值
  // // std::cout << "v.t = " << v.t << std::endl;
  // // std::cout << "vi2[2] = " << vi2[2] << std::endl;
  // // v.print_vector();

  // // -- ----tesr insert() ----------- --
  // // std::cout << "-- ----tesr insert() ----------- --" << std::endl;
  // // int insertValue = 12;
  // // Rank insertRank = 3;
  // // v.insert(insertValue, insertRank);
  // // v.print_vector();
  // // int insertCount = 2;
  // // while (insertCount--) {
  // //   v.insert(insertRank, insertValue);
  //   // v.print_vector();
  // // }

  // // -- -------test remove() ---------------- --
  // // std::cout << "-- -------test remove() ---------------- --" << std::endl;
  // // Rank del_lo = 0, del_hi = 2;
  // // v.remove(del_lo, del_hi);
  // // v.print_vector();

  // // -- -------test find() --------------- --
  // // std::cout << "-- -------test find() --------------- --" << std::endl;
  // // v.insert(4, 5);
  // // Rank find_lo = 0, find_hi = 7;
  // std::cout << "v.t_f index = "
  //           << v.find(find_lo, find_hi, v.t_f) <<std::endl;
  // v.print_vector();
  // // -- -------test remove() -------------- --
  // std::cout << "-- -------test remove() -------------- --" << std::endl;
  // Rank remove_r = 3;
  // std::cout << "v.remove(remove_r) = " << v.remove(remove_r) << std::endl;
  // v.print_vector();
  // // -- -------test deduplicate() ----------------- --
  // std::cout << "-- -------test deduplicate() ------------ --" << std::endl;
  // Rank set_lo = 0, set_hi = 4;
  // v.deduplicate();
  // v.print_vector();
  // // -- -------test increment ++ ------------------ --
  // std::cout << "-- -------test increment ++ ----------- --" << std::endl;
  // ++v;
  // v.print_vector();
  // v++;
  // v.print_vector();

  // // -- ------test traverse() increase()--------------------- --
  // std::cout << "-- ------test traverse() increase()------- --" << std::endl;
  // increase(v);
  // v.print_vector();

  // // -- ------test decrement -- ------------------ --
  // std::cout << "-- ------test decrement -- ---------- --" << std::endl;
  // --v;
  // v.print_vector();
  // v--;
  // v.print_vector();
  // // -- ------test traverse() decrease()--------------------- --
  // std::cout << "-- ------test traverse() decrease()------- --" << std::endl;
  // decrease(v);
  // v.print_vector();
  // // -- ------test traverse() double_value()--------------------- --
  // std::cout << "-- ------test traverse() double_value()--- --" << std::endl;
  // double_value(v);
  // v.print_vector();
  // // -- ------test traverse() Sum()--------------------- --
  // std::cout << "-- ------test traverse() Sum()------- --" << std::endl;
  // sum_ptr(v);
  // v.print_vector();
  // // -- ------test traverse() Sum_static()--------------------- --
  // std::cout << "-- ------test traverse() Sum_static()---- --" << std::endl;
  // sum_static(v);
  // // v.print_vector();

  // f_disordered(v);
  // f_dedepulicate_lower(v);
  // f_uniquify(v);
  f_uniquify_faster(v);


  return 0;
}


