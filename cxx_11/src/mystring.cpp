#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

/*
1. c++11右值引用：
c++11以后的容器，拷贝构造/拷贝赋值/insert/push_back等函数都增加了右值引用版本，
右值引用的本质是浅拷贝，相比深拷贝（左值引用版本）有更大的性能优势。
浅拷贝不需要重新分配空间和赋值操作，只是拷贝指针指向，也就是偷盗源端（左值）的东西。
浅拷贝后，右值(一般是临时对象）一般不能再用了，否则会出问题，
所以临时对象的指针会赋值为NULL,保证临时对象消失调用析构函数的时候不会释放对应的内存空间,
配合析构函数中类似 if (ptr != NULL) { // 执行内存释放...} 的写法。

2. 举例1：
容器中，insert()、push_back()等函数都有两个版本：
insert(..., & x)     // 左值引用版本
insert(..., && x)    // 右值引用版本
编译器遇到临时对象，一定把它当做右值，然后调用右值参数的版本，
因此不真正发生指针深拷贝，而是偷临时对象的东西（把指针指向临时变量的位置就好了，即指针浅拷贝），
指针浅拷贝可能有风险，被move之后，原临时对象就不能再用了，原临时对象的指针要设置为NULL。

3. 深拷贝和浅拷贝：
浅拷贝只是对指针的拷贝，拷贝后两个指针指向同一个内存空间；
深拷贝不但对指针进行拷贝，而且对指针指向的内容进行拷贝，经深拷贝后的指针是指向两个不同地址的指针。
浅拷贝可能导致一块内存空间被释放两次，导致内存泄露，程序崩溃。可使用智能指针解决类似的问题。

4. 自己实现string类，完成big five 特殊函数。
构造函数的特点：名称和类名相同，没有返回类型。
*/

class MyString{
private:
    char* _data;
    size_t _len;

public:
    // 默认构造函数
    MyString():_data(NULL), _len(0) {}
    
    MyString(char* data) {
        cout << "MyString(char* data)" << endl;
        _len = strlen(data);
        _data = new char[_len+1];
        memcpy(_data, data, _len);
        _data[_len] = '\0';
    }

    // 拷贝构造函数(深拷贝)
    MyString(const MyString& str) {
        cout << "MyString(const MyString& str)" << endl;
        _len = str._len;
        _data = new char[_len+1];
        memcpy(_data, str._data, _len);
        _data[_len] = '\0';
    }

    // 拷贝赋值函数(深拷贝)
    MyString& operator=(const MyString& str) {
        cout << "MyString& operator=(const MyString& str)" << endl;
        // 自己赋值给自己不需任何操作，别人赋值给自己，需要先清空自己
        if (this != &str) {
            if (_data) { delete _data;}
            _len = str._len;
            _data = new char[_len+1];
            memcpy(_data, str._data, _len);
            _data[_len] = '\0';
        }
        return *this;
    }

    // move版本的拷贝构造函数（浅拷贝）
    MyString(MyString&& str) noexcept {
        cout << "MyString(MyString&& str) noexcept" << endl;
        _len = str._len;
        _data = str._data;  // 浅拷贝 move操作
        str._len = 0;
        str._data = NULL;  // 重要，和析构函数配合，防止内存释放两边导致内存泄露
    }

    // move版本的拷贝赋值构造函数（浅拷贝）
    MyString& operator= (MyString&& str) {
        cout << "MyString& operator= (MyString&& str)" << endl;
        if(this != &str) {
            if(_data) { delete _data;}
            _data = str._data;
            _len = str._len;    // 浅拷贝 move操作
            str._len = 0;
            str._data = NULL;   // 重要，防止内存泄露
        }
    }

    virtual ~MyString(){
        cout << "virtual ~MyString()" << endl;
        if (_data != NULL) {
            delete _data;
        }
    }

    void show(){
        if (_len > 0) {
            cout << "data=" << _data << endl;
        }
    }

};

int main(){
    MyString ms1;
    char str[] = "hello";
    cout << "sizeof=" << sizeof(str) << endl;   // 输出6. 字符串一共占多少字节，包括'\0'
    cout << "strlen=" << strlen(str) << endl;   // 输出5. 以 '\0' 为结束符号
    MyString ms2(str);
    ms1 = ms2;
    ms1.show();

    // 调用右值构造函数
    MyString ms3(std::move(ms2));
    ms3.show();
    system("pause");
    return 0;
}