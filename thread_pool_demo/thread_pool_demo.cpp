#include "limonp/ThreadPool.hpp"
#include "limonp/StdExtension.hpp"
#include <unistd.h> // for function: usleep

using namespace std;

const size_t THREAD_NUM = 4;

class Foo {
public:
    // 多个线程会调用Append，对chars这个成员变量进行写操作，所以需要加锁保证线程安全
    void Append(char c) {
        limonp::MutexLockGuard lock(mutex_);
        chars.push_back(c);
        usleep(10 * 1000); // just for make chars more disorder
    }

    string chars;                   // 多线程共享的对象
    limonp::MutexLock mutex_;       // 线程锁
};

void DemoClassFunction()
{
    Foo foo;
    cout << foo.chars << endl;
    limonp::ThreadPool thread_pool(THREAD_NUM);       // 初始化一个线程池。
    thread_pool.Start();                              // 启动线程池
    for (size_t i = 0; i < 20; i++) {
        char c = i % 10 + '0';
        // 使用 NewClosure 绑定 foo 对象和 Append 函数和对应参数，构造一个闭包扔进线程池中运行
        // Closure 对象被扔进线程池之后，其实是进入了一个队列中。 
        // 然后线程池的多个线程去从队列中获取Closure指针，然后调用该 Run() 函数。
        // 类的对象指针，成员函数指针，函数的参数，都作为 ObjClosure1 的类成员变量存储着。 然后在函数 Run() 里面再用起来。
        // 闭包：能够保存函数运行状态
        thread_pool.Add(limonp::NewClosure(&foo, &Foo::Append, c));
    }
    // 等待所有线程工作（工作是指NewClosure生成的闭包函数）都完成，然后停止所有线程。
    thread_pool.Stop();
    cout << foo.chars << endl;
}

int main()
{
    DemoClassFunction();
    return 0;
}
