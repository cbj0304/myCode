#include <set>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include "common.h"

using namespace std;

/*
关联容器set：
1. 迭代器：
    bidirectional_iterator_tag（双向迭代器）

2. 底层结构是红黑树，默认比较函数是less<int>, 升序排序。
   插入：
   insert()，只能插入具体元素，指定在特定位置处插入无效，因为内部会自动排序。 
   删除：
   只有erase()，没有remove()(这个和顺序容器有区别)，erase的作用是把符合要求的元素都删掉：
   (1) void erase (iterator position);                   // 删除指定位置
   (2) size_type erase (const value_type& val);          // 删除等于指定值，类似顺序容器的remove
   (3) void erase (iterator first, iterator last);       // 删除指定范围
   查找：
   set/map的优势是支持高效查找，时间复杂度logN:
   count() / find() / equal_range() / lower_bound() / upper_bound()
*/

int main() {
    // 底层结构是红黑树，默认比较函数是less<int>, 升序排序
    set<int> c {11, 12, 34, 22, 1};

    c.insert(100);
    c.insert(100);              // set插入重复的元素不会生效
    c.insert({0, 200});         // 插入

    set<int> ci {1000, 2000};
    c.insert(ci.begin(), ci.end());  // 指定范围插入

    c.erase(22);                // 删除值等于22的
    auto it = c.begin(); 
    advance(it, 3);
    c.erase(c.begin(), it);     // 范围删除

    for_each(c.begin(), c.end(), show_item<int>); 
    cout << endl;                   // 12 34 100 200

    // 查找
    assert(c.count(100) == 1);
    it = c.find(34);
    if(it != c.end()) {
        cout << "find=>" << *it << endl;
    }
    
    set<int, greater<int>> c2 {2, 4, 1, 5};       // 自定义排序函数
    for_each(c2.begin(), c2.end(), show_item<int>); 
    cout << endl;                                 // 5 4 2 1

    // multiset和set的区别是：
    // multiset可以插入重复的元素。
    multiset<int> mc {1, 2, 2, 5, 5, 5, 4, 3, 2};
    assert(mc.count(2) == 3);
    assert(mc.size() == 9);
    it = mc.find(5);
    if(it != mc.end()) {
        cout << "find=>" << *it << endl;
    }
    // 范围查找
    pair<multiset<int>::iterator, multiset<int>::iterator> ret;
    ret = mc.equal_range(5);
    cout << *(ret.first) << endl;      // 第一个大于等于该元素的值
    cout << *(ret.second) << endl;     // 第一个大于该元素的值
    for (auto it = ret.first; it != ret.second; it++) {
        cout << *it << endl;           // 遍历范围查询结果
    }
    // 说明:set中由于没有重复元素，所以equal_range和find的作用是一样的，
    // 全局范围查找函数std::equal_range(forward_iter_begin, forward_iter_end, val),
    // 可以用于其他最低具备前向迭代器的容器的范围查找。
    
    system("pause");
    return 0;
}