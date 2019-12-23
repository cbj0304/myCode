#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

/*
c++标准库的sort方法：
1. 使用：
    #include <algorithm>
    using namespace std;
2. 使用的排序方法类似于快速排序，时间复杂度为 logN。
3. 默认采用从小到大排序，也支持自定义排序函数（仿函数、函数指针、模板函数指针、匿名函数）。
    (1) 如果待排序元素本身支持<运算符，或者重载的<运算符，不传第三个参数的情况下，采用从小到大排序。
    (2) 自定义比较函数，控制排序：
        比较函数两个参数(a, b), 如果a < b， 则返回true；->  从小到大排序（同默认情况）
        比较函数两个参数(a, b), 如果a > b， 则返回true；->  从大到小排序
4. 只有支持RandomAccessIterator的容器才能用此方法，所以list的排序不能使用该算法。
*/

// 自定义类
struct Student
{
    Student(string n, int s):name(n), score(s) {}
    string name;
    int score;

    // 重载小于运算符
    bool operator < (Student other) const {
        return this->score < other.score;
    }

    // 重载标准输出
    friend ostream& operator<<(ostream &out, Student &s) {
        out << "name=" << s.name << " score=" << s.score;
        return out;
    }
};

// 自定义比较函数
struct myCompStu
{
    bool operator() (const Student &a, const Student &b) const {
        return a.score > b.score;
    }
};

int main()
{
    cout << "TEST INNER CLASS..." << endl;
    // 容器使用sort，从小到大排序
    vector<int> vi = { 23, 45, 12, 6, 200};
    std::sort(vi.begin(), vi.end());       // 默认使用的是小于
    for (auto v : vi) { cout << v << endl; }
    // 可以直接使用内置仿函数，实现从大到小排序
    std::sort(vi.begin(), vi.end(), greater<int>());
    for (auto v : vi) { cout << v << endl; }

    cout << "TEST CUSTOMIZED CLASS..." << endl;
    // 自定义仿函数
    vector<Student> ss = {Student("zs", 80), Student("ls", 78), Student("ww", 100)};
    std::sort(begin(ss), end(ss));          // 重载了<, 就可以支持从小到大排序了。
    for(auto s : ss) { cout << s << endl; }
    // 自定义比较函数，实现从大到小排序
    std::sort(begin(ss), end(ss), myCompStu());
    for(auto s : ss) { cout << s << endl; }

    system("pause");
    return 0;
}