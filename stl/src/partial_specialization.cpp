#include <iostream>
#include <cstdlib>

using namespace std;

/*
1. 模板与特化：
    类模板和函数模板都必须定义在.h文件中，特例化版本必须与模板定义在同一个.h头文件中；
    模板的实例化类型确定是在编译期间；
    特化/偏特化 主要的用途都是对于特定的类型，指定特定的处理方式，
    编译阶段确定如果是某个特化类型，就用特化的模板；如果都不是，就用最一般的模板。
    特例化本质上是我们顶替了编译器的工作，我们帮编译器做了类型推导，
    全特化本质上是一个实例，而偏特化本质上还是一个模板，只是原来模板的一个子集。

2. 偏特化在STL中的应用：
    应用1：使迭代器既可以萃取出值类型，又可以包容原生指针
        (1) 在每个迭代器中都定义了value_type值类型的类型成员，这样直接通过迭代器的value_type类型成员就可以知道值类型。
        (2) 但是迭代器必须兼容原生态的指针，而原生指针很难被重新定义(如在原生指针的类中添加value_type的值类型的类型成员),
        这时候，靠的就是类模板的偏特化了,新添加一层iterator_traits类，专门萃取迭代器的属性，
        然后再对iterator_traits类设计原生指针与原生引用的偏特化版本，就解决了这个棘手的问题。
    应用2：type_traits类型萃取，对待特殊类型，特殊处理，提高效率
        举例：比如copy函数，如果传递的对象是一个复杂类型，那么可能只能采取最保守的处理方式，一个一个的构造；
        如果是内置类型，这样显然太低效，使用memcpy()可能会好一些。

3. typename的用法：
    1. 声明模板参数，可以替换为class。
    template <typename T>
    2. 声明后边所指是一个类型。
    template<typename C>
    void print2nd(const C& container){
        if(container.size() >= 2){
            C::const_iterator it(container.begin());
            ++it;
            int value = *it;  
            cout<<value;
        }
    }

    模板被解析时，C的类型还不确定，所以编译器不知道const_iterator是个类型，万一它是个变量呢？
    需要这样声明才可以： typename C::const_iterator it(container.begin());
*/

// 其中一种迭代器，可以有多种，内部需定义value_type
template <typename T>
class myIterator {
public:
    typedef T value_type;
};

// 泛化版本
template <typename T>
class Traits {
public:
    typedef typename T::value_type value_type; 
};

// 特化版本(原生态指针会优先调用此版本)
template <typename T>
class Traits<T*> {
public:
    typedef T value_type;
};

// 实现一个简单的算法类，既支持迭代器，又支持原生态指针
template <typename I>   // I可以是任意定义了value_type的迭代器，或者原生态指针
typename Traits<I>::value_type Fool(I i) {
    // TODO
}

int main() {
    int *p;
    int i = Fool(p);

    myIterator<char> it;
    Fool(it);

    system("pause");
    return 0;
}