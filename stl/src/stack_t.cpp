#include <stack>
#include <cassert>
#include <cstdlib>

using namespace std;

/*
stack: 容器适配器 - 栈
    1. LIFO后进先出；
    2. 不支持迭代器，不提供遍历方法；
    3. 不是容器，不能直接用统一初始化列表进行初始化，-> 能不能用取决于源码有没有实现这个接口！！！
    但是在使用拷贝构造函数时，既可以用初始化列表，也可以用圆括号，如下：
        list<double> values {1.414, 3.14159265, 2.71828};
        stack<double, list<double>> my_stack(values);      // 可以用底层容器构造，注意是()
        stack<double, list<double>> copy_stack {my_stack};  // 可以拷贝现有的stack容器

方法：
插入和删除：push() / pop()
访问：top()
容量：size() /empty()
*/

int main() {
    // 容器适配器：LIFO后进先出，不支持迭代器，不能直接用统一初始化列表
    // 基本操作：入栈、出栈、取栈顶、判空
    stack<int> c;
    c.push(100);
    c.push(200);
    c.push(300);               // 插入
    c.pop();                   // 删除
    assert(c.top() == 200);    // 访问
    assert(c.size() == 2);
    assert(c.empty() == false); 

    system("pause");
    return 0;
}