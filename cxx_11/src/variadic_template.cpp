#include <iostream>
#include <cstdio>
using namespace std;

/*
场景：
variadic_template(可变参数个数的模板)
泛型编程、类模板/函数模板：
原来模板参数可以使类和函数的  "参数类型任意化"，此处的variadic_template可以让 "参数个数任意化"
目标：类和函数的复用性
实现：...表示 包
利用参数个数逐一递减的特性，实现递归函数调用。
*/

void print() { }
 
template <typename T, typename... Types> //...出现在这表示模板参数包
void print(const T& firstArg, const Types&... args)    //...函数参数类型包
 {
    // 1. 处理第一个参数
	cout << firstArg << endl;
    // 2.  递归处理剩余的参数
	print(args...);    //...函数参数包
}
 
int main()
{
	print(7.5,"hello","what",42);
    system("pause");
	return 0;
}