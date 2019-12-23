#include <map>
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>

using namespace std;

/*
方法：
    插入/删除：erase() / insert() / clear() / swap()
    查找：count() / find() / equal_range() / lower_bound() / upper_bound()
    （说明：由于是排序的，所以有lower_bound()和upper_bound()方法，unordered容器无此方法。）

1. set / map / multiset / multimap 的共同点：
    (1) 以红黑树为底层容器，所有元素都会被自动排序；
    (2) 不能通过迭代器改变键值（set/multiset的值不能改；map/multimap的键值key不能改，可以改变value的值）

2. set 和 map 的区别：
    set只有key，没有value（或者说value就是key），map的元素是key-value的键值对；

3. set 和 multiset 的区别：
    set/map不允许键值(key)重复；multiset/multimap允许键值重复；

4. set 和 unordered_set 的区别：
    (1) set基于红黑树实现，有自动排序的功能，查找/插入/删除 的时间复杂度o(logN);
    (2) unordered_set基于哈希表，查找/插入/删除 的时间复杂度o(1); 而代价是消耗比较多的内存，无自动排序功能。
    底层实现上，使用一个下标范围比较大的数组来存储元素，形成很多的桶，利用hash函数对key进行映射到不同区域进行保存。
*/

int main() {
    // map和set的区别：
    // set的key和value合而为一了。
    map<string, int> c = {{"zs", 90}, {"ls", 80}, {"ww", 100}};
    c.insert({{"cbj", 100}, {"ll", 66}});

    assert(c.count("ww") == 1);
    assert(c.at("ls") == 80);
    auto it  = c.find("zs");       // 迭代器返回的是一个pair
    if(it != c.end()) {
        cout << "find=>" << it->first << ", " << it->second << endl;
    }

    map<int, int> c2 = {{90, 90}, {80, 80}, {100, 100}};
    map<int, int>::iterator it1 = c2.lower_bound(90);  // 返回第一个大于等于val的迭代器，这里指向90
    map<int, int>::iterator it2 = c2.upper_bound(90);  // 返回第一个大于val的迭代器，这里指向100（右开区间）

    cout << "<*it1, *it2>=" << it1->first << ", " <<  it2->first << endl;

    // multimap
    multimap<string, int> mm = {{"zs", 90}, {"ls", 80}, {"ww", 100}};
    mm.insert({{"zs", 90}, {"zs", 90}});
    assert(mm.count("zs") == 3);

    system("pause");
    return 0;
}