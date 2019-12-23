#include <forward_list>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include "common.h"

using namespace std;

/*
迭代器：
  forward_iterator_tag（前向迭代）

特点：
  支持单向顺序访问；
  不支持反向迭代器rbegin()等；
  不提供size()成员函数；
  没有指向尾部元素的游标，所以没有back()/push_back()/pop_back()等操作。

方法：
  push_front()
  pop_front()
  front()

  insert_after()
  erase_after()
  remove()
*/

int main() {
    forward_list<int> c;

    for(size_t i = 0; i < 10; i++) {
        c.push_front(i);           // 9 8 7 6 5 4 3 2 1 0
    }
    c.pop_front();                 // 8 7 6 5 4 3 2 1 0 

    // 在迭代器it之后插入和删除操作
    forward_list<int>::iterator it = c.begin();
    advance(it, 3);
    c.insert_after(it, 888);     // 8 7 6 5 888 4 3 2 1 0
    it = c.begin();
    advance(it, 5);
    c.erase_after(it);           // 8 7 6 5 888 4 2 1 0
    c.remove(7);                 // 8 6 5 888 4 2 1 0
    
    assert(c.front() == 8);

    for_each(c.begin(), c.end(), show_item<int>);

    system("pause");
    return 0;
}