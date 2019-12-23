#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

/*
说明
    元素为非基础类型，需要自定义哈希函数。

方法
    插入/删除：erase() / insert() / clear() / swap()
    查找：count() / find() / equal_range() / at()
*/

int main() {
    unordered_map<string, int> m = {{"a", 80}, {"b", 100}, {"c", 90}};
    m.insert({"b", 200});       // 此条数据插入无效
    m.erase("c");
    assert(m.count("b") == 1);

    auto it = m.find("b");
    if (it != m.end()) {
        cout << it->first << ", " << it->second << endl;     // b 100
    }
    cout << "m.at(\"a\")=" << m.at("a") << endl;
    try {
        cout << m.at("c") << endl;
    } catch (exception & e) {
        cout << e.what() << endl;      // 捕获越界异常
    }

    // unordered_multimap
    // 根据key 插入/统计/删除/查找。
    unordered_multimap<string, int> um {{"a", 300}, {"a", 500}};
    um.insert({{"a", 100}, {"b", 200}, {"c", 300}});

    assert(um.count("a") == 3);
    
    auto it1 = um.find("a");
    if (it1 != um.end()) {
        cout << "find=>" << it1->first << ", " << it1->second << endl;         // a 100
    }
    
    // 范围查找
    pair<unordered_multimap<string, int>::iterator, unordered_multimap<string, int>::iterator> ret;
    ret = um.equal_range("a");
    for(auto it = ret.first; it != ret.second; it++) {
        cout << "equal_range=>" << it->first << ", " << it->second << endl;
    }

    system("pause");
    return 0;
}
