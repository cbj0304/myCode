#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <typeinfo>
#include <cstdlib>
using namespace std;

double sum(double a, double b){
    return a + b;
}

int main(){
    // 基本类型推导
    auto i = 60;
    auto c = sum(1.2, 3.4);
    cout << "c=" << c << ", type=" << typeid(c).name() << endl;

    // 类型较复杂时：迭代器
    vector<list<string>> v;
    auto pos = v.begin();
    cout << (*pos).size() << endl;

    // 类型较复杂时：lambda函数
    auto f = [](int x)->bool { cout << "x+10=" << x+10 << endl; return true;};
    cout << f(22) << endl;

    system("pause");
    return 0;
}