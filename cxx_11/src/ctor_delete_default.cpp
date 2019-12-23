#include <iostream>
#include <cstdio>
using namespace std;

/*
1. c++11 构造函数和析构函数（big five）
- 构造
- 拷贝
- 赋值
- 右值拷贝
- 右值赋值
- 析构函数：
2. 以上特殊的成员函数，如果用户未显示定义，则编译器会隐式的生成一个对应的默认成员函数。

3. =default =delete
"=default"  ---  自动生成函数体
函数特性仅适用于类的特殊成员函数（以上5个），且该特殊成员函数没有默认参数。编译器为显示声明的"=default"函数自动生成函数体。
"=delete"  --- 禁用某个函数
让程序员显式的禁用某个函数。可以禁用以上特殊成员函数，还可以禁用某些转换函数、自定义new操作符等
*/

class Zoo {
public:
    // 构造函数
    Zoo(int i1, int i2):d1(i1),d2(i2){}
    // 拷贝
    Zoo(const Zoo&)=delete;
    // 赋值
    Zoo& operator=(const Zoo&)=default;
    // 右值拷贝
    Zoo(Zoo&&)=default;
    // 右值赋值
    Zoo& operator=(const Zoo&&)=delete;
    virtual ~Zoo() {}
private:
    int d1,d2;
};

class X{
public:
    // 禁用某些用户自定义的类的 new 操作符，从而避免在自由存储区创建类的对象
    void *operator new(size_t) = delete;
    void *operator new[](size_t) = delete;
};

int main(){
    X X1 = new X;   // 报错，new操作符被禁用
    Zoo z(1,2);
    Zoo z1(z);      // 报错，拷贝构造函数被禁用
    system("pause");
    return 0;
}