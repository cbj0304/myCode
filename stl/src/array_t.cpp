#include <array>
#include <iostream>
#include <ctime>
#include <cstdlib>  // qsort bsearch NULL
#include <algorithm>
#include <cassert>
#include "common.h"

using namespace std;

/*
迭代器：
    random_access_iterator_tag（随机访问迭代器）

赋值：
    统一初始化列表 {}；
    通过下标或者迭代器；
    fill()；

访问：
    随机访问迭代器可以访问任意位置的元素：
    front()
    back()
    at()
    []

方法：
    data()
    size()
    max_size()
    empty()
    swap()
*/

const size_t ASIZE = 100;

int main(){
    // ********** 赋值
    array<long, ASIZE> c {1, 2};    // 1.统一初始化列表，未初始化的默认为0 

    c.fill(-1);     // 2.批量赋值

    for(size_t i = 0; i < ASIZE; i++) {
        c[i] = rand();    // 3.通过下标赋值
    }

    // ********** 访问   
    cout << "array.front()=" << c.front() << endl;
    cout << "array.back()=" << c.back() << endl;        // 获取首尾元素
    assert(c.at(5) == c[5]);                            // at()有越界检查的功能，[]没有越界检查，但是效率更高
    
    cout << "array.size()=" << c.size() << endl;          // 元素个数
    cout << "array.max_size()=" << c.max_size() << endl;  // 最多能容纳的元素个数
    cout << "array.data()=" << c.data() << endl;          // 数组首地址，类似c数组的数组名
    assert(c.empty() == false);                           // 判空

    // ********** 算法
    // 快速排序
    qsort(c.data(), ASIZE, sizeof(long), compareLongs);
    for_each(c.begin(), c.end(), show_item<long>);
    cout << endl;
    
    // 二分查找
    long data = 17421;
    long* pItem = (long *)bsearch(&data, c.data(), ASIZE, sizeof(long), compareLongs);
    if (pItem != NULL) {
        cout << "found: " << *pItem << endl;
    } else {
        cout << "Not found" << endl;
    }

    // 交换
    array<long, 100> c2 {1, 2, 3};
    c.swap(c2);                      // 交换两个容器中的元素，两容器对象定义必须一致 array<long, 100>

    system("pause");
}