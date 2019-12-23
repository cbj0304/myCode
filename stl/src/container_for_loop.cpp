#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <iterator>  // ostream_iterator
#include "common.h"

using namespace std;

int main()
{
    // vector的那种遍历方法 ,支持随机访问迭代器的容器都可用类似的方法
    vector<int> vi = {3, 5, 7, 10};
    // 第一种: c++11的 for_loop
    for (auto v : vi) { cout << v << endl;}
    for (auto& v : vi) { v *= 10; cout << v << endl;}

    // 第二种: 迭代器访问
    vector<int>::iterator it = vi.begin();
    for (; it != vi.end(); it++) { cout << *it << endl; }
    for (auto it1 = vi.begin(); it1 != vi.end(); ++it1) { cout << *it1 << endl; }

    // 第三种: 下标访问
    for (int i = 0; i < vi.size(); i++) { cout << vi[i] << " " << vi.at(i) << endl; }

    // 第四种: stl中for_each算法，此处匿名函数可以换成仿函数、函数指针、函数模板等
    for_each(vi.begin(), vi.end(), [](const int& val)->void {cout << val << endl;});
    for_each(vi.begin(), vi.end(), show_item<int>);

    // 第五种：copy到标准输出流
    // ostream_iterator (ostream_type& s, const char_type* delimiter);
    copy(begin(vi), end(vi), ostream_iterator<int> {std::cout, " "});
    copy(vi.begin(), vi.end(), ostream_iterator<int>(cout, " "));

    system("pause");
    return 0;
}