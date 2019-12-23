#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

/*
1. variadic_template(可变参数个数模板)的应用：自己实现一个tuple容器
第一种方式：通过类的继承实现递归（本例）
第二种方式：通过类的组合实现递归

2. 全特化与偏特化
偏特化：如果模板有多种类型，那么只限定其中的一部分。
全特化：限定死模板实现的具体类型。
// 类模板声明
template<typename T1, typename T2>
class Test {...}
// 全特化版本
template<>
class Test<int , char> {... }
// 偏特化版本
template <typename T2>
class Test<char, T2> {... }
*/


// 类模板声明
template<typename... val>
class mytuple;

// 特化版本 (递归结束条件)
template<>
class mytuple<> {};

// 偏特化版本(递归继承自身)
template<typename Head, typename... Tail>
class mytuple<Head, Tail...> : private mytuple<Tail...> {
protected:
    typedef mytuple<Tail...> inherited;
    Head m_head;   

public:
    mytuple(){}
    mytuple(Head v, Tail... vtail) : m_head(v), inherited(vtail...){ }

    Head head() {return m_head;}

    // 此处返回基类的引用，c++多态性，可以把派生类的引用赋值给基类的引用！！！
    inherited& tail() {return *this;}  // *取引用操作符，返回左值引用 

};

int main(){
    /*
    mytuple<int, string, double>  继承自 mytuple<string, double>，里边有一个int和一个指向父类的引用
    mytuple<string, double> 继承自 mytuple<double>，里边有一个string和一个指向父类的应用
    mytuple<double> 继承自 mytuple<>, 里边有一个指针和一个指向父类的引用
    mytuple<>
    */
    mytuple<int, string, double> tu(42, "hello", 1.35);
    cout << sizeof(tu) << endl;
    cout << tu.head() << endl; 
    cout << tu.tail().head() << endl;
    cout << tu.tail().tail().head() << endl;
    system("pause");
    return 0;
}