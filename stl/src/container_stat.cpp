#include <iostream>
#include <cstdlib>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int main() {
    // 测试一个指针占8个字节
    cout << sizeof(int*) << endl; 

    // vector类的栈空间有三个指针（指向当前空间的头尾和可用空间的尾部 3*8=24byte）
    // sizeof计算的是实例化这个类型的对象，需要开辟多大的空间，所以是恒量24byte，解释见size_of_t.cpp
    cout << sizeof(vector<int>) << endl; 

    // 向vector灌入大量数据，由于数据是在堆上开辟空间，所以栈空间一直是24byte
    vector<int> vi = {12, 34, 5, 15, 100};
    cout << sizeof(vi) << endl;            // 24 byte
    vi.push_back(200);
    cout << sizeof(vi) << endl;            // 24 byte

    // *************测试各种容器占用的栈空间的大小*****************
    cout << "sizeof(array<int, 100>)=" << sizeof(array<int, 100>) << endl;
    cout << "sizeof(vector<int>)=" << sizeof(vector<int>) << endl;
    cout << "sizeof(list<int>)=" << sizeof(list<int>) << endl;
    cout << "sizeof(forward_list<int>)=" << sizeof(forward_list<int>) << endl;
    cout << "sizeof(deque<int>)=" << sizeof(deque<int>) << endl;
    cout << "sizeof(stack<int>)=" << sizeof(stack<int>) << endl;
    cout << "sizeof(queue<int>)=" << sizeof(queue<int>) << endl;
    cout << "sizeof(set<int>)=" << sizeof(set<int>) << endl;
    cout << "sizeof(map<int, int>)=" << sizeof(map<int, int>) << endl;
    cout << "sizeof(multiset<int>)=" << sizeof(multiset<int>) << endl;
    cout << "sizeof(multimap<int, int>)=" << sizeof(multimap<int, int>) << endl;
    cout << "sizeof(unordered_set<int>)=" << sizeof(unordered_set<int>) << endl;
    cout << "sizeof(unordered_map<int, int>)=" << sizeof(unordered_map<int, int>) << endl;
    cout << "sizeof(unordered_multiset<int>)=" << sizeof(unordered_set<int>) << endl;
    cout << "sizeof(unordered_multimap<int, int>)=" << sizeof(unordered_map<int, int>) << endl;

    // *************测试各种迭代器占用的栈空间的大小*****************
    cout << "sizeof(array<int, 100>::iterator)=" << sizeof(array<int, 100>::iterator) << endl;
    cout << "sizeof(vector<int>::iterator)=" << sizeof(vector<int>::iterator) << endl;
    cout << "sizeof(list<int>::iterator)=" << sizeof(list<int>::iterator) << endl;
    cout << "sizeof(forward_list<int>::iterator)=" << sizeof(forward_list<int>::iterator) << endl;
    cout << "sizeof(deque<int>::iterator)=" << sizeof(deque<int>::iterator) << endl;
    // cout << "sizeof(deque<int>::iterator)=" << sizeof(stack<int>::iterator) << endl;  // error stack不提供迭代器
    // cout << "sizeof(deque<int>::iterator)=" << sizeof(queue<int>::iterator) << endl;  // error queue不提供迭代器
    cout << "sizeof(set<int>::iterator)=" << sizeof(set<int>::iterator) << endl;
    cout << "sizeof(map<int, int>::iterator)=" << sizeof(map<int, int>::iterator) << endl;
    cout << "sizeof(multiset<int>::iterator)=" << sizeof(multiset<int>::iterator) << endl;
    cout << "sizeof(multimap<int, int>::iterator)=" << sizeof(multimap<int, int>::iterator) << endl;
    cout << "sizeof(unordered_set<int>::iterator)=" << sizeof(unordered_set<int>::iterator) << endl;
    cout << "sizeof(unordered_map<int, int>::iterator)=" << sizeof(unordered_map<int, int>::iterator) << endl;
    cout << "sizeof(unordered_multiset<int>::iterator)=" << sizeof(unordered_multiset<int>::iterator) << endl;
    cout << "sizeof(unordered_multimap<int, int>::iterator)=" << sizeof(unordered_multimap<int, int>::iterator) << endl;
    
    // *************测试各种容器的迭代器的类型*****************
    cout << "iterator_tag array=" << 
        typeid(iterator_traits<array<int, 100>::iterator>::iterator_category).name() << endl;
    cout << "iterator_tag vector=" << 
        typeid(iterator_traits<vector<int>::iterator>::iterator_category).name() << endl;
    cout << "iterator_tag list=" << 
        typeid(iterator_traits<list<int>::iterator>::iterator_category).name() << endl;
    cout << "iterator_tag forward_list=" << 
        typeid(iterator_traits<forward_list<int>::iterator>::iterator_category).name() << endl;
    cout << "iterator_tag deque=" << 
        typeid(iterator_traits<deque<int>::iterator>::iterator_category).name() << endl;
    // cout << "iterator_tag stack=" << 
    //     typeid(iterator_traits<stack<int>::iterator>::iterator_category).name() << endl;  // error stack不提供迭代器
    // cout << "iterator_tag queue=" << 
    //     typeid(iterator_traits<queue<int>::iterator>::iterator_category).name() << endl;  // error queue不提供迭代器
    cout << "iterator_tag set=" << 
        typeid(iterator_traits<set<int>::iterator>::iterator_category).name() << endl;
    cout << "iterator_tag map=" << 
        typeid(iterator_traits<map<int, int>::iterator>::iterator_category).name() << endl;
    cout << "iterator_tag multiset=" << 
        typeid(iterator_traits<multiset<int>::iterator>::iterator_category).name() << endl;
    cout << "iterator_tag multimap=" << 
        typeid(iterator_traits<multimap<int, int>::iterator>::iterator_category).name() << endl;
    cout << "iterator_tag unordered_set=" << 
        typeid(iterator_traits<unordered_set<int>::iterator>::iterator_category).name() << endl;
    cout << "iterator_tag unordered_map=" << 
        typeid(iterator_traits<unordered_map<int, int>::iterator>::iterator_category).name() << endl;
    cout << "iterator_tag unordered_multiset=" << 
        typeid(iterator_traits<unordered_multiset<int>::iterator>::iterator_category).name() << endl;
    cout << "iterator_tag unordered_multimap=" << 
        typeid(iterator_traits<unordered_multimap<int, int>::iterator>::iterator_category).name() << endl;

    system("pause");
    return 0;
}

/*
输出结果：
# 容器类占用栈空间大小（64位系统测试结果）：
    sizeof(array<int, 100>)=400     // 内部维护一个定长的栈数组 -> sizeof(int)*100=400 
    sizeof(vector<int>)=24          // 当前使用节点的头尾指针，可用空间的尾指针 -> 3*8=24
    sizeof(list<int>)=24            // 指向链表首节点的指针（节点包含：int类型的data，前向指针，后向指针）
    sizeof(forward_list<int>)=8     // 指向链表首节点的指针（节点包含：int类型的data，一个前向指针）
    sizeof(deque<int>)=80           // 中控节点map的首地址(8)、map的长度(8)、指向首数据段的iterator(4*8)、指向尾数据段的iterator(4*8)
    sizeof(stack<int>)=80           // deque的封装
    sizeof(queue<int>)=80           // deque的封装
    sizeof(set<int>)=48             // 内部维护一课红黑树，
    sizeof(map<int, int>)=48        // 红黑树的一个节点(4*8=32)（颜色枚举、指向父节点的指针、指向左右孩子的指针）,节点数量(8)，指向root节点的指针(8)
    sizeof(multiset<int>)=48        // 类似map
    sizeof(multimap<int, int>)=48   // 类似map
    sizeof(unordered_set<int>)=56   // 内部维护一个vector类型的buckets(24),元素个数(sizeof(size_t)=8)，用于控制什么时候rehashing，
                                    // 三个空的函数对象（获取key，key的比较，hash函数），各占一个1 byte, 3+8+24=40, 4字节对齐，调整为40
                                    // 由于不同c++库里实现方式不一样，可能还有其他的栈对象，我在64位windows下测试是56，具体的看源码。
    sizeof(unordered_map<int, int>)=56
    sizeof(unordered_multiset<int>)=56
    sizeof(unordered_multimap<int, int>)=56

#  迭代器类占用栈空间大小（64位系统测试结果）：
    sizeof(array<int, 100>::iterator)=8
    sizeof(vector<int>::iterator)=8
    sizeof(list<int>::iterator)=8
    sizeof(forward_list<int>::iterator)=8
    sizeof(deque<int>::iterator)=32
    sizeof(set<int>::iterator)=8
    sizeof(map<int, int>::iterator)=8
    sizeof(multiset<int>::iterator)=8
    sizeof(multimap<int, int>::iterator)=8
    sizeof(unordered_set<int>::iterator)=8
    sizeof(unordered_map<int, int>::iterator)=8
    sizeof(unordered_multiset<int>::iterator)=8
    sizeof(unordered_multimap<int, int>::iterator)=8

# 容器的迭代器类型
    iterator_category array=random_access_iterator_tag
    iterator_category vector=random_access_iterator_tag
    iterator_category list=bidirectional_iterator_tag
    iterator_category forward_list=forward_iterator_tag
    iterator_category deque=random_access_iterator_tag
    iterator_category set=bidirectional_iterator_tag
    iterator_category map=bidirectional_iterator_tag
    iterator_category multiset=bidirectional_iterator_tag
    iterator_category multimap=bidirectional_iterator_tag
    iterator_category unordered_set=forward_iterator_tag
    iterator_category unordered_map=forward_iterator_tag
    iterator_category unordered_multiset=forward_iterator_tag
    iterator_category unordered_multimap=forward_iterator_tag
*/