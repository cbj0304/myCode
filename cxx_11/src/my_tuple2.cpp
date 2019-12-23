#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

/*
1. variadic_template(可变参数个数模板)的应用：自己实现一个tuple容器
第一种方式：通过类的继承实现递归
第二种方式：通过类的组合实现递归（本例）
*/

// 模板类的声明
template<typename... Value> 
class mytuple;

// 全特化版本(递归结束条件))
template<>
class mytuple<> {};

// 偏特化版本
template<typename Head, typename... Tail>
class mytuple<Head, Tail...> {
protected:
    typedef mytuple<Tail...> composited;
    Head m_head;
    composited m_tail;
public:
    mytuple() {}
    mytuple(Head v, Tail... tail): m_head(v), m_tail(tail...){}

    Head head(){
        return m_head;
    }

    composited& tail() {
        return m_tail;
    }
};

int main(){

    mytuple<int, string, double> tu(12, "hello", 1.2);
    cout << tu.head() << endl;
    cout << tu.tail().head() << endl;
    cout << tu.tail().tail().head() << endl;
    system("pause");
    return 0;
}