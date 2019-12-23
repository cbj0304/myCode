#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cstdio>

using namespace std;

// c++11统一初始化方式
/*
1. 格式：大括号{}
2. 适用于：数组、stl容器（vector/list/string/set/deque...）、类构造
3. 实现原理：
编译器看到 {t1,t2... tn}时便会做出一个initializer_list<T>,它关联至一个array<T,n>。
调用构造函数时（构造函数接受initializer_list<T>类型的参数），该array内的元素可被编译器分解逐一赋值给函数。
举例说明：
vector<string> cities {"Beijing", "New York", "London","Berlin"};
编译器遇到{}，生成一个initializer_list<string>,背后有个array<string, 4>，
调用vector<string>构造函数时，编译器找到其中一个构造函数接受initializer_list<string>。


例如：
vector(initializer_list<value_type> __I){...}
vector& operator=(initializer_list<value_type> __I){...}
void insert(iterator __position, initializer_list<value_type> __I){...}
void assign(initializer_list<value_type> __I){...}
min(initializer_list<value_type> __I){...}
max(initializer_list<value_type> __I){...}
根本原因：这些容器的构造函数有一个接受initializer_list<value_type>类型参数的构造函数！！！

4. initializer_list不仅可以用于构造函数的参数，还可以用于自定义函数的参数，用于处理一组相同类型的参数。

*/

void printV(string s) { cout << s << " ";}

// 自定义参数列表
void print(std::initializer_list<int> vals){
    for(auto p=vals.begin(); p!=vals.end(); ++p){
        cout << *p << endl;
    }
}

int main(){
    // 复习c++的初始化方式（等号、小括号、大括号、构造函数等）
    int i1 = 5;
    int i2 = int(5);
    int i3[3] = {3, 5, 7};
    cout << i1 << i2 << i3[0] << endl; 

    // c++11统一初始化(大括号)
    int a[4] = {1, 2, 3, 4};
    int *b = new int[3]{11, 22, 33};
    vector<string> vec = {"hello", "word"};
    map<string, int> m = {{"you", 10}, {"I", 20}};

    // c++11以后，以下stl中定义的函数均支持传initializer_list<T>作为参数
    vector<int> v1 = {100, 200, 300};
    vector<int> v2 {400, 500, 600};
    vector<int> v3 ({700, 800, 900});
    v3.insert(v3.end(), {1000, 1100});
    cout << max({string("aa"), string("cc"), string("bb")}) << endl;

    int i{};  // 初始化为0
    int *p{}; // 初始化为空指针

    // 自定义参数列表
    print({11,22,33,44,55,66});

    system("pause");
    return 0;
}