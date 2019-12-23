#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <algorithm>
#include "common.h"

using namespace std;

/*
迭代器：
  bidirectional_iterator_tag（双向迭代器）

赋值：
双向链表可以在任意位置高效的插入和删除元素：
  push_back()
  push_front()
  pop_back()
  pop_front()
  insert()
  erase()  // erase和insert配对，通过游标操作，彻底的擦除元素
  remove() // list成员函数中的remove可以移除指定值的节点，并释放资源。
          // vector没有remove成员函数，调用的是算法库中的remove，不会真正删除，见vector示例代码

访问：
  双向迭代器只能访问收尾元素，或者双向顺序访问,不支持随机访问。
  front()
  back()

方法：
  size()
  max_size()
  empty()
  reserve()
  resize()
  uniq()
  sort()

vector和list的区别：
  vector是一块连续的内存，支持下标随机访问，但是插入和删除操作会导致大量内存拷贝，效率较低。
  list是双向链表，只能顺序访问，不支持随机访问，但是任何位置插入或删除非常迅速。
  结论：
  1. 如果需要高效的随机存取，不在乎插入删除效率，用vector；
  2. 如果需要大量的插入删除，而不在乎随机存取，用list；
  3. 如果既需要随机存取，又关系两端数据的插入删除，用deque；
*/

int main() {

    // *********** 赋值
    // 1. 统一初始化列表
    list<string> c = {"you", "and", "me"};
    c.assign({"hate", "and", "and", "hate", "like",  "and", "hate", "like", "like"});

    // 2. 在任意位置插入删除元素
    c.pop_front();
    c.pop_back();
    c.push_back("you");
    c.push_front("me");       // 支持收尾插入
    c.emplace_front("hate");
    c.emplace_back("like");   // push_back/push_front的右值引用版本（高效）
    c.insert(++begin(c), "inserter");  // 在第二个位置插入
    auto iit = c.begin();
    advance(iit, 5);
    c.insert(iit, 3, "100");           // 游标向前移动5个位置，插入3个"100"

    iit = c.begin();
    c.erase(iit);
    c.remove("hate");         // erase是删除迭代器所指位置(范围)的元素，remove是删除指定取值的元素。

    for_each(c.begin(), c.end(), show_item<string>);
    cout << endl;

    // *********** 访问
    cout << "list.front()=" << c.front() << endl;
    cout << "list.back()=" << c.back() << endl;

    // *********** 容量
    cout << "list.size()=" << c.size() << endl;                 // 元素个数
    cout << "list.max_size()=" << c.max_size() << endl;         // 容器允许的最大元素数,跟平台有关
    // resize(Container::size_type n) 
    // reserve(Container::size_type n) 

    // *********** 算法
    c.sort();        // 排序
    for_each(c.begin(), c.end(), show_item<string>);
    cout << endl;

    c.unique();      // 去重
    for_each(c.begin(), c.end(), show_item<string>);
    cout << endl;

    c.remove("like");   // 删除
    c.remove("me");
    for_each(c.begin(), c.end(), show_item<string>);
    cout << endl;

    system("pause");
    return 0;
}