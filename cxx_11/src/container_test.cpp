#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <algorithm>
using namespace std;

/*
c++11新增容器类型：
-------- array
1. 为什么要引入 std::array 而不是直接使用 std::vector？
std::vecotr 太强大了，以至于我们没有必要为了去敲碎一个鸡蛋而用一个钉锤。
使用 std::array 保存在栈内存中，相比堆内存中的 std::vector，我们就能够灵活的访问这里面的元素，从而获得更高的性能；

2. 已经有了传统数组，为什么要用 std::array?
(1)代码更现代化，操作更方便 fill size at(i) ...
(2)越界检查（安全）
(3)和内置数组占用相同的内存，但是写入效率较低（低效换来了安全和便利）
(4)更方便的使用标准库的容器算法，如std::sort

-------- forward_list
std::list是双向循环链表
std::forward_list是单向链表，插入操作o(1),没有size()方法，比list空间利用率更高，操作方法和list类似。


-------- unordered_set/unordered_map
std::set/std::map内部实现是红黑树，插入和搜索时间复杂度是o(logN),输出元素有序。
unordered_set/unordered_map内部通过哈希表实现，插入和搜索时间复杂度o(1),无序，性能有提升。用法与set/map类似。


-------- tuple
用于存放不同类型的数据。

-------- begin/end 
*/
int main(){
    // array
    array<string,6> strArr;
    strArr.fill("test");
    for (string s : strArr) {
        cout << s << " ";
    }
    cout << strArr.size() << endl;

    array<int,6> arr {12,45,23,1};
    std::sort(arr.begin(), arr.end());
    for(auto it = arr.begin(); it !=arr.end(); it += 2){
        cout << *it << endl;
    }

    // forward_list
    forward_list<int> fl;
    fl.push_front(10);
    fl.push_front(20);
    fl.push_front(30);
    fl.pop_front();
    cout << fl.front() << endl;

    // unordered_set/unordered_map
    unordered_map<int, string> mymap = {{1, "aaa"}, {2, "bbb"}, {3, "ccc"}};
    for(const auto& m : mymap){
        cout << m.first << ", "  << m.second << endl;
    } 
    unordered_set<string> myset;
    cout << myset.bucket_size(myset.size()-1) << endl;  // 返回下标为 n 的桶中的元素数
    myset.insert("hello");
    myset.insert({"world", "aaa", "ccc"});
    for(const auto & s : myset) {
        cout << s.data() << endl;
    }

    //tuple
    tuple<string, int, char> student = make_tuple("zhangsan", 18, 'A');
    cout << get<0>(student) << ","
         << get<1>(student) << ","
         << get<2>(student) << endl;
    // 元组拆包
    string name("");
    int age = 0;
    char level = 0;
    tie(name, age, level) = student;
    cout << "name=" << name << " age=" << age << " level=" << level << endl;

    // begin/end
    vector<int> v {1,2,3,4,5};
    auto b = begin(v);
    auto e = end(v); e--;     // 左开右闭的特性
    cout << "begin=" << *b << " end=" << *e;
    
    system("pause");
    return 0;
}
