#include <iostream>
#include <string>

using namespace std;

// 自定义比较函数
// 典型比较函数定义格式如下，返回值为int，两参数类型为const void*
// 如果是升序，a>b返回正值，相等返回0
int compareLongs(const void* a, const void* b) {
    return (*(long*)a - *(long*)b);
}

int compareStrings(const void* a, const void* b) {
    if (*(string*)a > *(string*)b) {
        return 1;
    } else if (*(string*)a < *(string*)b) {
        return -1;
    } else {
        return 0;
    }
    
}

template<typename T>
void show_item(const T& t) {
    cout << t << " ";
}

