#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

/*
1. 智能指针的作用：
（1）处理内存泄露的问题（申请了内存，没有释放）
（2）处理空悬指针（野指针）的问题，野指针不是nullptr，它会指向垃圾内存，给程序造成隐患。
（3）处理比较隐晦的由异常造成的资源泄露的问题（如异常导致程序退出，但是申请的内存没有释放）

2. c++11的智能指针模板
shared_ptr（共享式）: 
多个智能指针可以指向相同对象，
该对象和其相关资源会在“最后一个引用（reference）被销毁”时候释放。

unique_ptr（独占式）:
同一时间内只有一个智能指针可以指向该对象。
它对于避免资源泄露（resourece leak）——例如“以new创建对象后因为发生异常而忘记调用delete”——特别有用。
*/

shared_ptr<int> fun(shared_ptr<string> str) {
    cout << *str << endl;
    return shared_ptr<int>(new int(1));
}

class mydata {
private:
    int m_data;
public:
    mydata(int data):m_data(data) {};
    ~mydata() {};
    void show() {
        cout << "data=" << m_data << endl;
    }
};


int main() {
    // shared_ptr
    shared_ptr<string> pstr1(new string("hello"));
    shared_ptr<int> pint(new int(100));

    vector<shared_ptr<string>> vec;
    vec.push_back(pstr1);

    for(auto p : vec) {
        cout << *p << endl;
    }

    cout << *fun(pstr1) << endl;

    // 调用智能指针本身的类成员函数用'.',调用智能指针指向对象的方法用'->'
    shared_ptr<mydata> pdata = make_shared<mydata>(100);
    pdata.reset(new mydata(200));   // 指针重置，指向新的mydata实例
    pdata->show(); 
    shared_ptr<mydata> pdata2(new mydata(300));
    pdata.swap(pdata2);   // 修改指向
    pdata->show(); 
    cout << pdata.use_count() << endl;  // pdata所指对象的引用计数


    // unique_ptr
    unique_ptr<mydata> up(new mydata(101));
    mydata *pda = up.release();  // 返回一个指向被管理对象的指针，并释放所有权
    pda->show();
    assert (up.get() == nullptr);
    // reset swap和上边类似

    unique_ptr<int> pi = make_unique<int>(5);
    cout << *pi << endl;

    if (pi) {
        cout << "before reset pi=" << *pi << endl;
    } 
    pi.reset();
    if (pi) {  // false
        cout << "after reset pi=" << *pi << endl;
    } 

    system("pause");
    return 0;
}