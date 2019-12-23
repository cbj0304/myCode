#include <iostream>
#include <cstdlib>
using namespace std;

/*
1. 左值和右值：
左值:可以出现在等号的左边。
右值：只能出现在等号的右边。
int a=10;
int b=a;
a = a + b;
变量a、b是左值，表达式a+b是右值。
临时对象是右值，因为他没有名字。
2. 左值引用和右值引用：
左值引用：常规引用。
右值引用：必须绑定到右值的引用，通过&&获取，
         右值引用只能绑定到一个将要被销毁的对象上，因此可以自由的移动（偷盗）其资源。

3. std::forward和std::move的联系和区别
（1）std::move是无条件转换，不管它的参数是左值还是右值，都会被强制转换成右值。
（2）std::forward是有条件转换。它的参数绑定到一个右值时，则转换到一个右值。当参数绑定到左值时，转换后仍为左值。
（3）std::move和std::forward在运行期都没有做任何事情。
4. 不完美转交：
临时对象是右值，因为他没有名字。
但是右值在多层传递中，在实参中有了命名，变成了一个左值，接下来会调用左值版本，造成深拷贝浪费。
c++11通过forward函数实现完美转发，做原来是右值，则经过forward转换一直是右值。
*/

// 左值引用版本(传入左值会调用左值引用版本)
void process(int& i) {
    cout << "process(int&) " << i << endl;
}
// 右值引用版本(重载版本，传入右值调用右值引用版本)
void process(int&& i) {
    cout << "process(int&&) " << i << endl;
}

// 不完美转交
void myprocess(int&& i) {
    cout << "myprocess(int&&) " << i << endl;
    process(i);
}

// 完美转交
void myprocess2(int&& i) {
    cout << "myprocess2(int&&) " << i << endl;
    process(std::forward<int>(i));
}

int main(){

    int a = 0;
    process(a);   // a是左值，调用左值版本

    process(1);   // 常量表达式1是右值，调用右值版本

    process(std::move(a));  // move函数将a强转为右值，调用右值版本

    myprocess(2);   // 不完美转交：常量2是右值，经由myprocess传给另一个函数变成了左值（原因是传输过程中它变成了一个named object，不是临时对象了）

    myprocess(move(a)); // 不完美转交：a经由myprocess传给另一个函数变成了左值

    myprocess2(2); // 完美转交

    // myprocess(a);   // 无左值版本，调用失败

    const int& b = 1;
    // process(b);  // 左值引用 无const版本 process(const int&)
    // process(move(b));  // 无参数匹配的版本

    system("pause");
    return 0;
}