#include <queue>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cassert>

using namespace std;

/*
queue:容器适配器-队列
    方法：
        插入删除：push() / pop()
        访问：front() / back()
        容量：empty() / size()


priority_queue：容器适配器-优先级队列
    方法：
        插入删除：push() / pop()
        访问：top()
        容量：empty() / size()

priority_queue和queue的区别和联系 
    (1) 二者都定义在头文件#include<queue>中，都是先进先出(FIFO)的容器适配器，不提供迭代器，不提供遍历方法，不提供clear()接口。
    (2) priority_queue支持自定义数据的优先级，让优先级高的排在前面，优先出队；
    (3) priority_queue默认底层容器是vector实现的大顶堆heap；默认比较函数是 less<int>，降序排序;
        queue默认的底层容器是deque，也可以用list。
    (4) priority_queue 通过 top() 函数来访问队首（堆顶）元素；queue可以通过front()和back()访问队首/队尾元素。
*/

int main() {
    // 1. 适配器：先进先出，不支持迭代器，不能用统一初始化列表
    // 基本操作：入队列、出队列、访问队首、队尾、判空
    queue<int> c;
    for(int i : {100, 200, 300, 400}) {
        c.push(i);                  // 插入
    }  
    c.pop();                        // 删除

    assert(c.front() == 200);       // 访问第一个元素
    assert(c.back() == 400);        // 访问最后一个元素

    // 2. 适配器，优先级队列
    priority_queue<int, vector<int>, greater<int>> q;       // 升序队列
    for (int n : {3, 5, 7, 2, 1, 10}) {
        q.push(n);
    }
    assert(q.top() == 1);           // 访问
    q.pop();                        // 删除
    assert(q.top() == 2);

    system("pause");
    return 0;
}

