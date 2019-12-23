#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <iterator>
#include <cstdio>
#include <cstdint>

using namespace std;

/*
 c++11 关键词 using
1.类型别名的三种方式 (type alias)
   基本类型别名：
  使用关键字 typedef => typedef unsigned short  uint16_t;
  使用预编译宏 #define => #define uint16_t unsigned short;
  c++11使用using定义别名 => using uint16_t = unsigned short;

  函数指针类型别名(类型的别名可增加可读性，没有产生新类型)：
  typedef void (*func)(int, int); <=> using func = void (*)(int, int); 

2. 模板别名 (template alias)
   template <typename T>
   using Vec = std::vector<T, MyAlloc<T>>;

   Vec<int> col;
   等价于：
   template <typename T>
   std::vector<int, MyAlloc<int>> col;
*/


// 第一种方式：容器的iterator能够回答value_type这个问题
template<typename Container>
void test_moveable(Container c){
    typedef typename iterator_traits<typename Container::iterator>::value_type valtype;

    for(long i=0; i < 10;++i){
        c.insert(c.end(), valtype());
    }
    
    Container c1(c);
    Container c2(std::move(c));
    c1.swap(c2);  
}

// 第二种方式：使用模板别名
// 模板作为模板参数！！！
template<typename T, template<class> class Container>
class XCls
{
private:
    Container<T> c;
public:
    XCls(){
        for(long i=0;i<10;i++){
            c.insert(c.end(),T());
        }
        Container<T> c1(c);
        Container<T> c2(std::move(c));
        c1.swap(c2);
    }
};

template<typename T>
using Vec = vector<T, allocator<T>>;

template<typename T>
using Lst = list<T, allocator<T>>;

template<typename T>
using Deq = deque<T, allocator<T>>;

// 函数别名,义了一种函数指针 类型
int max(int a, int b){
    return a > b ? a : b; 
}
int min(int a, int b){
    return a > b ? b : a; 
}
using FUNC = int (*)(int, int);

int main(){
    // 1.测试iterator_traits
    test_moveable(list<string>());

    // 2.测试模板别名
    XCls<string, Vec> c1;

    // 3.测试函数别名
    FUNC f;
    f=min;
    cout << "min(3,4)=" << f(3, 4) << endl;
    f=max;
    cout << "max(3,4)=" << f(3, 4) << endl;

    system("pause");
    return 0;
}