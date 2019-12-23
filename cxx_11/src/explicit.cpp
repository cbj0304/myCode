#include <iostream>
#include <cstdio>

using namespace std;

/*
1. c++03以前的版本中 explicit关键词：
条件：单个参数的构造函数（因为无参数构造函数和多参数构造函数总是显示调用，explicit无意义）
作用：阻止对象构造时 隐式类型转换，只能显示的调用构造函数
例如：
构造函数： explicit A(bool flag){...}
不能这样调用： A=false;

2. c++11扩展：c++11中由于可以通过"初始化参数列表"构造对象,所以可以修饰多参数的构造函数
作用：阻止通过参数列表构造，只能显示的通过调用构造函数构造对象。
*/

class Complex{
public:
    explicit
    Complex(int re, int im=0):real(re), imag(im) { }

    Complex operator+(const Complex& x){
        return Complex(real + x.real, imag + x.imag);
    }
    // 重载输出运算符
    friend ostream& operator<< (ostream &out, Complex& x){
        out << "re=" << x.real << ", im=" << x.imag << endl;
        return out;
    }
private:
    int real;
    int imag;
};

class P {
public:
    explicit
    P(int a, int b, int c):m_a(a), m_b(b), m_c(c){
    }

    // 重载输出运算符
    friend ostream& operator<< (ostream &out, P& x){
        out << x.m_a << x.m_b << x.m_c << endl;
        return out;
    }
private:
    int m_a;
    int m_b;
    int m_c;
};

int main(){
    Complex c1(12, 4);
    // Complex c2 = c1 + 5;  // 报错,隐式转换失败
    Complex c2 = c1 + Complex(5);  // 显示的调用构造函数没有问题
    cout << c2 << endl;

    // P p = {1, 3, 4};   // 报错，隐式转换
    P p(1,2,4);      // 显示的调用构造函数没有问题   
    cout << p << endl;
    system("pause");
    return 0;
}