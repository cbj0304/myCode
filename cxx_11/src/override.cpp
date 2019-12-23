#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

/*
override(重写): 
c++11中，子类重写父类的(纯)虚函数时，如果函数声明后边加上override,编译器就会对非法的重写操作校验并报错。
1. 父类中无此函数，或父类中的函数并不是虚函数，编译器会报错。
2. 父类和子类中成员函数的 返回类型、异常规格、函数名、形参类型、常量属性、引用限定符等不一致，编译器会报错。


c++公有继承：
纯虚函数  => 继承的是：接口
虚函数    => 继承的是：接口+缺省实现（子类可以重写(覆盖)父类的实现） -- 多态、动态绑定
非虚函数  => 继承的是：接口+强制实现            -- 静态绑定
*/

class Shape {
public:
    virtual void Draw() const = 0;    // 纯虚函数
    virtual void Error(const string& msg) {
        cout << "Shape Error" << endl;
    };  // 虚函数
    int ObjectID() const;         // 非虚函数
};

class Rectangle: public Shape {
public:
    virtual void Draw() const override {
        cout << "Draw Rectangle..." << endl;
    }
    virtual void Error(const string& msg) override {
        cout << "Rectangle Error " << msg << endl;
    }

};

class Ellipse : public Shape {
public:
    // 纯虚函数必须重写，虚函数如果子类没有重写则继承父类默认的
    virtual void Draw() const override {
        cout << "Draw Ellipse" << endl;
    }
};


int main(){
    // 动态绑定，调用子类的重写的虚函数和纯虚函数的实现
    Shape *rec = new Rectangle();
    rec->Draw(); 
    rec->Error("rec error");       

    Shape *el = new Ellipse();
    el->Draw();
    el->Error("el error");   // 子类没有重写父类的虚函数，则调用父类默认的实现

    el->Shape::Error("shape error");  // 子类通过作用域符号::调用父类的虚函数实现

    system("pause");
    return 0;
}