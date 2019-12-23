#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*

lambda函数的语法定义：（采用了追踪返回类型的方式声明其返回值)
格式：
   [capture-list](parameters-list) -> return-type{function-body;}

    capture-list ：捕捉列表，捕捉上下文中的变量以供lambda函数使用（必选）
    -- []    表示  空捕捉
    -- [=]   表示值传递方式捕捉所有父作用域的变量(包括this)
    -- [&]   表示引用传递方式捕捉所有父作用域的变量(包括this)
    -- [var] 表示值传递方式捕捉变量var
    -- [&var]表示引用传递方式捕捉变量var  
    -- [this]表示值传递方式捕捉当前this指针 (this。函数体内可以使用Lambda所在类中的成员变量。)
    -- 其它组合形式：

    parameters-list : 参数列表（可选）
    return-type : 返回类型（可选）
    function-body : 函数体（必选）
*/
class Test{
public:
    Test(int a, int b): m_a(a),m_b(b){}
    void f1(int t){
        auto f = [this] {return m_a + m_b;}; // 省略参数列表，返回值由编译器推断为int
        cout <<__FILE__<< __LINE__ << "\t"  << f() + t <<endl;
    }
    int m_a;
    int m_b;
};

class func{
public:
    func(int x, int y): m_x(x), m_y(y) {} 
    bool operator () (int item) {
        return (item > m_x && item < m_y);
    }
private:
    int m_x;
    int m_y;
};
 
int main()
{
    [] {};  // 最简lambda函数（必须有捕获列表和函数体）
    int a = 3;
    int b = 4;

    // [=]
    auto c = [=] {return a + b;}; // 省略参数列表，返回值由编译器推断为int
    cout <<__FILE__<< __LINE__ << "\t"  << c() << endl;


    // [&]
    auto d = [&] {b += 2; return a + b;}; // 省略参数列表，返回值由编译器推断为int
    cout <<__FILE__<< __LINE__ << "\t"  << d()  << "\t" << d() << endl;


    // 组合
    auto mytest = [=, &b] (const string& str) -> decltype(a+b) {
        b = 100; 
        cout << str << endl; 
        return a+b;
    };
    cout << mytest("my test=>") << endl;

    // mutable / read-only
    auto ia = 30;
    auto f1 = [ia] () mutable { ia += 1; return ia + 100;};
    // error: assignment of read-only variable 'ia'
    // auto f2 = [ia] () { ia += 1; return ia + 100;};
    auto f3 = [&ia] {ia += 1; return ia + 100;};

    cout << "f1=" << f1() << endl;
    // cout << "f2=" << f2() << endl;
    cout << "f3=" << f3() << endl;

    // [this]
    Test t(1,2);
    t.f1(9);

    // 和std算法一起用，功能和函数对象类似
    vector<int> vec {10, 20, 30, 40, 50, 60};
    int x = 30, y = 60;
    // 匿名函数
    vec.erase(remove_if(vec.begin(), vec.end(), 
               [x, y] (int item) -> bool {return (item > x && item < 60);})
               , vec.end());
    // 函数对象
    vec.erase(remove_if(vec.begin(), vec.end(), 
              func(x, y))
              , vec.end());
    for(auto ii : vec){
        cout << ii << endl;
    }

    system("pause");
    return 0;
}