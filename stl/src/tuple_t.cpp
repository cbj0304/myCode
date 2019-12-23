#include <tuple>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cmath>

using namespace std;

const double EPS = 1e-6;

int main() {
    auto c2 = make_tuple("zs", 12.34);
    // 取值和赋值
    get<1>(c2) = 88.8;
    assert(fabs(get<1>(c2) - 88.8) < EPS);
    assert(get<0>(c2) == "zs");

    tuple<string, int, char> c = {"cbj", 80, 'y'};    // 统一初始化列表
    string s;
    int i;
    tie(s, i, std::ignore) = c;          // unpack elements (with ignore) 任何类型都可以用std::ignore占位
    assert(s == get<0>(c));
    assert(i == get<1>(c));

    system("pause");
    return 0;
}