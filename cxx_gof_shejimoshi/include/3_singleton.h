#include <iostream>

using namespace std;

// c++单例模式分为两种：懒汉模式和饿汉模式
// 懒汉模式：第一次用的时候才会创建，线程不安全
// 饿汉模式：一开始就加载，空间换时间，每次用的时候直接返回，线程安全
// 还有一种方式是在懒汉基础上加锁、double-check的方式，这中方式由于cpu指令reorder会导致不可预知的问题，不推荐


// 懒汉（线程不安全）
class Singleton_ {
private:
    Singleton_() {}
    static Singleton_ *single_;
public:
    static Singleton_* GetInstance() {
        if (single_ == NULL) {
            single_ = new Singleton_();
        }
        return single_;
    }

    void print(int data) {
        cout << "Singleton_ print => " << data << endl;
    }
};

// Singleton_ * Singleton_::single_ = NULL;




// 饿汉（线程安全）

class Singleton {
private:
    // 构造函数私有化
    Singleton() {}
    static Singleton *single;

public:
    static Singleton* GetInstance() {
        return single;
    }

    void print(int data) {
        cout << "Singleton_ print => " << data << endl;
    }
};

// Singleton *Singleton::single = new Singleton();
