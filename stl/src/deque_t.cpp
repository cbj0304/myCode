#include <iostream>
#include <cassert>
#include <cstdlib>
#include <deque>
#include <algorithm>
#include "common.h"

using namespace std;

/*
迭代器：
    random_access_iterator_tag（随机访问迭代器）

特点：
    1. 支持随机访问at/[], 性能略差于vector；
    2. 在两端插入和删除很高效，也支持在任意位置的插入和删除操作，但性能不及list；

和vector操作上的区别：
    1. deque不提供容量操作 capacity() / reserve()；
    2. deque提供push_front() / pop_front()函数直接操作头部；
    3. 对deque的排序在性能上不高效，可以把deque中的元素移到vector进行排序，在移回来；
*/

int main() {

    // *********** 赋值
    deque<int> c {10, 20};
    c.assign({30, 40, 50});
    c.push_front(60);
    c.push_back(70);
    c.pop_back();
    c.pop_front();                       // 1. 在收尾插入删除
    // 还有右值版本： c.emplace(), c.emplace_front(), c.emplace_back()
    c[1] = 80;                           // 2. 通过迭代器或者下标覆盖赋值
    auto it = c.begin();
    c.insert(it, {90, 100});             // 3. 在任意位置插入元素 

    it = c.end();
    it--;
    c.erase(it);                         // 4.在任意位置删除元素  

    for_each(c.begin(), c.end(), show_item<int>);               // 90 100 30 80
    cout << endl;
    
    // ********* 随机访问
    assert(c.at(1) == 100);         // 有越界检查
    assert(c[1] == 100);            // 高效，但是没有越界检查
    assert(c.front() == 90);
    assert(c.back() == 80);

    // ********* 容量 （不支持reserve和capacity）
    cout << "deque.size()=" << c.size() << endl;
    cout << "deque.max_size()=" << c.max_size() << endl;
    c.resize(3);                // 截断成3个元素 90 100 30

    // ************  算法
    deque<int> d {100, 200};
    c.swap(d);                     // 交换两个容器的内容
    for_each(c.begin(), c.end(), show_item<int>); 
    cout << endl;

    system("pause");
    return 0;
}