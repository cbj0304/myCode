#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <typeinfo>

using namespace std;

/*
auto和decltype的区别：
auto用法：
场景：编译器根据表达式的值推导变量类型，auto定义变量必须有初始值，才能推导。
举例：
  auto a = i,&b = i,*c = &i;//正确: a初始化为i的副本,b初始化为i的引用,c为i的指针。
  auto item = val_1 + val_2;

decltype的用法：
场景：
以下场景auto就显得无能为力了。
1. 推断表达式中的类型，用于定义表达式/变量。
2. 推断函数的返回值的类型，用于定义表达式/变量。
以上过程中编译器只是分析表达式类型，并不计算表达式的值。
*/

template <typename T>
auto sum(T x, T y) -> decltype(x+y) {
  return x+y;
}

auto max(int x, int y) {
    cout << "test" << endl;  // 推导函数返回类型时，函数体并不会被执行
    return x > y ? x : y;
}

int main(){
    map<string,float>::value_type elem1;
    map<string,float> col;
    col = {std::pair<string,float>("a1",1.1),std::pair<string,float>("a2",1.2)};  // 统一初始化列表
    col.insert(std::pair<string,float>("a",1.1));
    for (decltype(col)::value_type elem2 : col){
        cout << elem2.first << "," << elem2.second << endl;
    }

    int data = 1000;
    int *p = new int();
    decltype(*p) p1 = data;   // decltype作用于接引用(*)操作，推导的结果是引用 int&

    int i = 42;
    decltype(i) ia = 100;    // 推导出来是 int
    decltype((i)) ib = data; // 推导出来是 int& => 加括号，变表达式，变量是一个可以作为左值的特殊表达式
    decltype(i = 50) ic = data; // 推导出来是 int&  => 赋值运算符返回的是左值引用
    cout << "i=" << i << endl;  // decltype只作类型推导，并不实际计算，所以i还是42

    cout << sum(3, 4) << endl;

    decltype(max(5,6)) idata = 100;
    cout << typeid(idata).name() << endl;

    system("pause");
    return 0;
}