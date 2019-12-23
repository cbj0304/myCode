#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <iterator>        // ostream_iterator
#include "common.h"

using namespace std;

/*
迭代器：
  random_access_iterator_tag（随机访问迭代器）

赋值：
1. 在尾部插入删除：
  push_back();
  pop_back();
2. 修改已添加的元素值：
  通过迭代器或者下标[]
3. 在任意位置插入删除（需要大量移动元素，不如list高效）：
  insert()
  erase()  // erase和insert配对，通过游标操作，彻底的擦除元素
  remove() // 算法库中的remove是将指定元素移动到容器的尾部并不减少vector的size,
           // vector需要用remove和erase配合使用彻底的擦除指定元素,
           // 为什么这样？因为不同元素的删除方式不一样，不能做出通用性的删除动作

访问：
  随机访问迭代器可以访问任意位置的元素：
  front()
  back()
  at()
  []

方法：
  size()
  max_size()
  capacity()
  empty()
  data()
  reserve()
  resize()
  swap()
*/

int main() {
    // ********** 赋值
    vector<string> c {"hello", "world"};         // 1.统一出初始化列表

    char buf[10];
    for (size_t i = 0; i < 100; i++) {
        snprintf(buf, 10, "%d", i);
        c.push_back(string(buf));
    }
    c.pop_back();                  // 2.插入->只能在元素尾部插入删除 push_back/pop_back
    c[2] = "inserter";             // 3.覆盖赋值->通过随机迭代器的iterator和下标[]
    
    for_each(c.begin(), c.end(), show_item<string>);
    cout << endl;

    // ********** 访问
    cout << "vector.front()=" << c.front() << endl;           
    cout << "vector.back()=" << c.back() << endl;              // front/back: 返回首尾元素的引用
    cout << "*(c.begin())=" << *(c.begin()) << endl;
    assert(*(--c.end()) == c.at(c.size() - 1));                 // begin/end: 返回首尾元素的迭代器,前闭后开

    // ********** 方法
    cout << "vector.size()=" << c.size() << endl;              // 元素个数
    cout << "vector.capacity()=" << c.capacity() << endl;      // 当前申请的空间可容纳元素的个数
    cout << "vector.max_size()=" << c.max_size() << endl;      // 最多可添加的元素个数
    assert(sizeof(c) == sizeof(vector<int>));                  // 实例化vector需要的字节数  24byte
    cout << "vector.data()=" << c.data() << endl;              // 首地址                  
    assert(c.empty() == false);                                // 判空

    // resize和reserve:
    // resize(Container::size_type n) : 
    // n小于当前容量时，尾部多余元素被截断销毁，n大于当前容量时，新默认构造元素添加到尾部，也会发生重新分配。
    // reserve(Container::size_type n) n不小于当前大小，扩容到指定大小，预先空间分配，一般定义容器时调用。

    // ********* 算法
    // 查找
    auto fit = find(c.begin(), c.end(), "45");
    if (fit != c.end()) {
        cout << "find, " << *fit << endl;
    } else {
        cout << "not find" << endl;
    }
    // 交换
    vector<string> c2 {"hello", "china"};
    c.swap(c2);
    
    // remove/erase配合彻底删除指定元素
    vector<int> vi {23, 100, 5, 100, 33, -10};          // size=6
    std::vector<int>::iterator it = remove(vi.begin(), vi.end(), 100);  
    // 此时size=6, it指向有效元素的下一个元素的位置，即指向第5个位置
    vi.erase(it, vi.end());                // 删除无效数据区间
    copy(vi.begin(), vi.end(), ostream_iterator<int>(cout, " ")); // 23 5 33 -10 size=4

    system("pause");
    return 0;
}