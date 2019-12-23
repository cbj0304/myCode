#include <unordered_set>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <vector>
#include "common.h"

using namespace std;

/*
set 和 unordered_set：
    如果元素为非基础类型，需要自定义哈希函数，具体使用和set类似；

方法：
    插入/删除：erase() / insert() / clear() / swap()
    查找：count() / find() / equal_range()
*/

// 自定义hash函数（仿函数）
struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

int main() {
    unordered_set<vector<int>, VectorHash> s;
    s.insert({1, 2});
    s.insert({1, 3});
    s.insert({1, 2});

    vector<int> i = {1, 2};
    auto it = s.find(i);
    if (it != s.end()) {
        vector<int> tmp = *it;
        for_each(tmp.begin(), tmp.end(), show_item<int>);
    }
    
    system("pause");
    return 0;
}