#include <iostream>

using namespace std;

// 代理模式：为其他对象提供一种代理以控制对这个对象的访问。这样实现了业务和核心功能分离。
// 代理对象和真实对象有相同的接口，可以操作真实对象，也可以附加业务逻辑，对真实对象进行了封装和隔离。
// 应用：远程代理(如rpc)、安全代理（控制真实对象的访问权限）、智能指针（可以处理真实指针外的一些事情）

// 抽象接口
class Subject {
public:
    virtual void Request() = 0;
    virtual ~Subject(){}
};

// 真实对象
class RealSubject : public Subject { 
public:
    void Request() { cout << "RealSubject" << endl; }
};

// 代理对象
class Proxy : public Subject { 
private:
    RealSubject* realSubject;
public:
    void Request() {
        if (realSubject == NULL) realSubject = new RealSubject();
        // 可以在此处增加对真实对象的特殊处理或复杂的业务规则
        realSubject->Request();
    }
};

int main() {
    Subject* p = new Proxy();
    p->Request(); // RealSubject

    delete p;
    return 0;
}
