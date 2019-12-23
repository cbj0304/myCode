# 学习目标

* c++标准库（c++ Standard Library）
* STL标准模板库（Standard Template Llibrary）

## 重要网站

<https://zh.cppreference.com/>
<http://www.cplusplus.com/>
<https://gcc.gnu.org/> (libstdc++)

## STL六大部件

容器（Containers）
分配器（Allocators）
算法（Algorithms）
迭代器（Iterators）
适配器（Adapters）
仿函式（Functors）

## 容器分类

序列式容器：
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>

适配器：
#include <queue>   // 基于deque(list)的queue; 基于vector->heap的priority_queue;
#include <stack>   // 基于deque(list/vector)的stack;

关联式容器：
#include <set>                // set multiset
#include <map>                // map multimap
#include <unordered_set>      // unordered_set unordered_multiset
#include <unordered_map>      // unordered_map unordered_multimap

## stl使用的是堆内存还是栈内存？

1. array定长数组，占用栈内存。
2. 其他大部分容器:基础变量结构(类似一个头部信息)，会存放在栈上，大量的数据会存放在堆上(allocator调用new/delete操作符进行批量的内存分配)。
例如：vector内部会维护三个指针类型（64位系统上每个指针占8byte），分别指向目前使用空间的头部、尾部以及可用空间的尾部，所以sizeof(vector<int>)=8*3=24byte，但是实际存储的大量数据是通过new在堆上创建的，sizeof只会计算类中栈空间大小，也就是定义vector这个结构需要的空间大小，所以动态增加元素时，sizeof(vector<int>)=24byte。
说明：一个指针所占的字节数跟系统的寻址能力有关，16位系统，指针占2个字节；32位系统指针占4个字节；64位系统，指针占8个字节。

## STL各种容器、迭代器汇总

1. 容器类型占栈空间大小。
2. 容器的迭代器类型。
3. 容器迭代器类型占栈空间的大小。
（说明：占空间大小会受到平台源码实现、系统寻址能力等的影响。）

## 容器的各种遍历方式


## STL容器的使用

* array/vector -- 顺序容器、连续空间
* list/forward_list -- 顺序容器，非连续空间
* deque -- 顺序容器，分段连续空间(模拟连续空间)
* stack/queue/priority_queue -- 容器适配器
  * priority_queue底层是通过vector实现的一个大根堆；
  * stack底层是deque，支持一端插入删除，也可以用list和vector实现；
  * queue底层是deque，支持一端插入，一端删除，也可以用list实现。
* set/map/multiset/multimap -- 基于红黑树、key有序的关联容器
* unordered_set/unordered_map/unordered_multiset/unordered_multimap  -- 基于hashtable，key无序的关联容器

## 友元、模板

友元分类（friend）：
    友元类；
    友元函数；
    友元成员函数；
模板分类（template）：
    类模板；
    函数模板；
    成员模板；

## 全特化与偏特化

类模板：全特化/偏特化
函数模板：只能全特化，偏特化通过函数重载实现。
案例：iterator_traits

## 常见算法

accumulate
for_each
replace/replace_if/replace_copy
count/count_if
find/find_if
sort
binary_search
函数适配器：binder2nd/not1/bind
其他常用算法

## B站学习视频

https://www.bilibili.com/video/av59131050
https://www.bilibili.com/video/av45108908（c++11新增容器）
