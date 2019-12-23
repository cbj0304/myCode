#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cstdlib>

using namespace std;

/*
## STL六大部件

容器（Containers）
分配器（Allocators）
算法（Algorithms）
迭代器（Iterators）
适配器（Adapters）
仿函数（Functors）

vector -- 容器
allocator -- 分配器
count_if -- 算法
not1 -- 函数适配器
bind2nd -- 函数适配器
less -- 函数对象（仿函数）：重载了()运算符的类的实例，使用起来就和函数一样。
*/

int main()
{
    int ia[6] = {27, 40, 43, 56, 47, 12};
    vector<int, allocator<int>> vi(ia, ia+6);

    // 统计小于40的元素的个数
    cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)));

    system("pause");
    return 0;
}
