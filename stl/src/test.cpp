#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iterator>     // ostream_iterator

using namespace std;

int main(){
    vector<int> vi {23, 100, 5, 100, 33, -10};          // size=6
    std::vector<int>::iterator it = remove(vi.begin(), vi.end(), 100);  
    // 此时size=6, it指向有效元素的下一个元素的位置，即指向第5个位置
    vi.erase(it, vi.end());                // 删除无效数据区间
    copy(vi.begin(), vi.end(), ostream_iterator<int>(cout, " ")); // 23 5 33 -10 size=4
    cout << vi.size() << endl;

    

    system("pause");
    return 0;
}