#include <iostream>
#include <cstdlib>

using namespace std;

/*
1. 运算符重载使得用户自定义的类型以一种更简洁的方式工作。
    运算符重载只是对运算符作出了新的解释，原有基本语义基本不变，
    - 不改变运算符的优先级；
    - 不改变运算符的结合性；
    - 不改变运算符所需要的操作数；
    - 不创建新的运算符。

2. 实现方式：
    成员函数
    全局函数
    友元函数
    1. 定义友元是为了访问类的私有成员。
    2. 友员函数没有 this 指针，所需操作数都必须在参数表显式声明。

3. 操作符重载的结果是一个函数，重载步骤：
    函数名称：operator{运算符}
    函数参数：操作数
    函数返回值：引用/指针/值


4. 重载++/-- 的注意事项
    后置++和后置--，增加一个伪参数int来标识


5. 重载<< 和链式编程
    函数返回值充当左值 需要返回一个引用

6. 案例：自己实现复数类，并重载 + /- /<< /++ /-- 运算符
*/

class Complex {

public:
    Complex(int re = 0, int im = 0) {
        this->real = re;
        this->imag = im;
    }
    ~Complex(){ }

    // 重载+运算符（成员函数）
    Complex operator+ (const Complex& other) {
        return Complex(this->real + other.real, this->imag + other.imag);
    }

    // 重载+运算符（友元函数）
    friend Complex operator- (Complex &c1, Complex &c2);

    // 重载<<运算符（友元函数）
    friend ostream& operator<< (ostream& out, Complex& c) {
        out << "< real=" << c.real << " imag=" << c.imag << " >";
        return out; 
    }

    // 重载前置++运算符
    Complex& operator++ () {
        this->real++;
        this->imag++;
        return *this;
    }

    // 重载后置++运算符 int标识
    Complex& operator++ (int) {
        Complex c(this->real, this->imag);
        this->real--;
        this->imag--;
        return c;
    }

private:
    int real;
    int imag;
};

// 重载-操作符（全局函数）
Complex operator- (Complex &c1, Complex &c2) {
    Complex c(c1.real - c2.real, c1.imag - c2.imag);
    return c;
}

int main()
{
    Complex c1(2, 3), c2(2, 2);
    Complex c3 = c1 + c2;
    cout << "c3 =>" << c3 << endl;

    c3++;
    cout << "c3++ =>" << c3 << endl;

    ++c3;
    cout << "++c3 =>" << c3 << endl;

    system("pause");
    return 0;
}