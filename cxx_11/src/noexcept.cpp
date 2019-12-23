#include <iostream>
#include <cstdlib>

using namespace std;

/*
1. c++异常处理机制：
   throw... try... catch...

   throw  表达式（异常是一个表达式可以是基本类型，也可以是类）;

   try {
    语句组 
   } catch(异常类型) {
    异常处理代码
   }

2. c++11异常处理：
   a. 可以抛出任意异常 （和之前默认版本一样）
   b. 不可以抛出异常 （使用关键词 noexcept）
       b1. 该关键字告诉编译器，函数中不会发生异常,这有利于编译器对程序做更多的优化。
       b2. 如果在运行时，noexecpt函数向外抛出了异常,程序会直接终止 std::abort()
*/

void cxx_try_catch_test()
{
    int age;
    cout << "input your age: ";
    cin >> age;
    if (age < 0) {
        cout << "age cannot be negative！" << endl;
        throw - 1;
    }
}

// 第一种情况：noexcept 告诉程序员此函数不会抛出异常，
// 不必深入所有的调用层自己去确认函数是否会剖出异常
void cxx11_try_catch_test1() noexcept
{
    try {
        cxx_try_catch_test();
    } catch (int e){
        cerr << "err=" << e << endl;  
    }
}

// 第二种情况：noexcept 表示即使是抛出了异常，在main函数中通过try...catch也无法捕获异常
void cxx11_try_catch_test2() noexcept
{
    cxx_try_catch_test();
}

int main()
{
    // c++中的try...catch
    try {
        cxx_try_catch_test();
    } catch (int e) {
        // 打印错误并处理异常
        cerr << "err=" << e << endl;
    }

    // 函数不会抛出异常，内部已捕获了
    cxx11_try_catch_test1();

    // 函数即使抛出异常，也捕获不到，直接终止
    try {
        cxx11_try_catch_test2();
    } catch (int e) {
        // 打印错误并处理异常
        cerr << "err_cxx11=" << e << endl;   // 捕获失效
    }
    system("pause");
    return 0;
}