#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <cstdlib>

using namespace std;

#define FUNC std::function<void*(void)>     // 定义一个函数对象

class Reflector
{
private:
    map<std::string, FUNC> objectMap;       // 类名字符串，构造函数指针
    static shared_ptr<Reflector> ptr;       // 单例对象

public:
    void* CreateObject(const string &str) {
        for (auto & x : objectMap) {
            if(x.first == str)
                return x.second(); // 利用构造函数构造对象实例并返回
        }
        return nullptr;
    }

    void Register(const string &class_name, FUNC && generator) {
        objectMap[class_name] = generator;
    }


    // 单例的get方法
    static shared_ptr<Reflector> Instance() {
        if(ptr == nullptr) {
            ptr.reset(new Reflector());
        }

        return ptr;
    }

};

shared_ptr<Reflector> Reflector::ptr = nullptr;    // 全局、单例

class RegisterAction
{
public:
    RegisterAction(const string &class_name, FUNC && generator) {
        Reflector::Instance()->Register(class_name, forward<FUNC>(generator));
    }
};

// lambda表达式返回一个对象指针
// 通过类名和对象指针构造一个RegisterAction对象实例，
// 同时在RegisterAction对象构造函数中完成了"注册"(即在main函数前完成了注册)
// 宏定义中的##表示把字符串连接起来。#表示将其变为字符串。
#define REGISTER(CLASS_NAME) \
RegisterAction g_register_action_##CLASS_NAME( #CLASS_NAME, [](){return new CLASS_NAME();} );\

class Base
{
public:
    explicit Base() = default;
    virtual void Print() {
        cout << "Base" << endl;
    }
};
REGISTER(Base);

class DeriveA : public Base
{
public:
    void Print() override {
        cout << "DeriveA" << endl;
    }
};
REGISTER(DeriveA);

class DeriveB : public Base
{
public:
    void Print() override {
        cout << "DeriveB" << endl;
    }
};
REGISTER(DeriveB);

int main()
{
    shared_ptr<Base> p1((Base*)Reflector::Instance()->CreateObject("Base"));
    p1->Print();

    shared_ptr<Base> p2((Base*)Reflector::Instance()->CreateObject("DeriveA"));
    p2->Print();

    shared_ptr<Base> p3((Base*)Reflector::Instance()->CreateObject("DeriveB"));
    p3->Print();

    system("pause");
    return 0;
}
