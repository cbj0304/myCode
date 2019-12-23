#include <iostream>
#include <vector>
#include <functional>    // std::minus
#include <numeric>       // std::accumulate
#include "common.h"
#include <algorithm>
#include <cassert>
#include <iterator>    // std::ostream_iterator

using namespace std;

/*
STL算法部分：
    #include <algorithm>     // 大量的算法函数
    #include <numeric>       // 定义了一些数值算法
    #include <functional>    // 定义了一些模板类，用于声明函数对象

常用算法举例：
查找[algorithm]：
    count/count_if：统计等于某个值/符合某个判断条件的元素个数。
    find/find_if: 查找，返回指向该元素的迭代器。
    equal_range: 查找，返回一对iterator（lower_bound和upper_bound）。
    search: 查找一个子序列第一次出现的位置。
    search_n: 查找val出现n次的子序列。
    binary_search: 在有序序列中查找value，找到返回true。

排序[algorithm]：
    sort: 升序排序
    stable_sort: 与sort类似，不过保留相等元素之间的顺序关系（稳定）。
    reverse: 将指定范围内元素重新反序排序。
    merge: 合并两个有序序列，存放到另一个序列。
    random_shuffle: 对指定范围内的元素随机调整次序。
    nth_element: 将范围内的序列重新排序，使所有小于第n个元素的元素都出现在它前面，而大于它的都出现在后面。

删除和替换[numeric]：
    copy: 复制序列。
    copy_backward: 与copy相同，不过元素是以相反顺序被拷贝。
    remove/remove_if: 删除范围内所有等于指定元素的元素（不是真的删除，可能是移动到尾部）。
    remove_copy/remove_copy_if: 将所有不匹配元素复制到一个指定容器。
    replace/replace_if: 将范围内指定值(满足指定条件)的元素用新值代替。
    replace_copy/replace_copy_if:同上，不过将结果拷贝到另一个容器。
    swap: 交换存储在两个容器中的元素。
    swap_range: 将指定范围内的元素与另一个序列元素值进行交换。
    unique/unique_copy: 清除序列中重复元素，和remove类似，它也不能真正删除元素。

排列组合[algorithm]：
    next_permutation:
    prev_permutation:

数值算法[numeric]:
    accumulate: 累计到某一初始值（默认是加法）。
    partial_sum: 创建一个新序列，其中每个元素值代表指定范围内该位置前所有元素之和。
    inner_product: 计算内积(对应元素相乘，再求和)。
    adjacent_difference: 创建一个新序列，新序列中每个新值代表当前元素与上一个元素的差。

生成和变异算法[algorithm]：
    fill/fill_n: 将输入值赋给标志范围内的元素。
    for_each：用指定函数依次对范围内所有元素进行迭代访问。
    generate/generate_n: 连续调用输入的函数来填充指定的范围。
    transform: 将输入的操作作用于范围内的每个元素，并产生一个新的序列。

关系算法[algorithm]：
    equal: 如果两个序列在标志范围内元素都相等，返回true。
    max: 返回两个元素中较大一个。
    min: 返回两个元素中较小一个。
    max_element: 返回一个ForwardIterator，指出序列中最大的元素。
    min_element: 返回一个ForwardIterator，指出序列中最小的元素。
    mismatch: 并行比较两个序列，指出第一个不匹配的位置，返回一对iterator，标志第一个不匹配元素位置。

集合算法[algorithm]：
    set_union: 两个升序的容器 计算并集。
    set_intersection: 两个升序的容器 计算交集。
    set_difference: 两个升序的容器 计算差集。
    set_symmetric_difference: 两个升序的容器 计算对称差集。(并集-交集)。

堆算法[algorithm]：
    make_heap: 把指定范围内的元素生成一个堆。
    pop_heap: 并不真正把最大元素从堆中弹出，而是重新排序堆。
        它把first和last-1交换，然后重新生成一个堆。
        可使用容器的back来访问被"弹出"的元素或者使用pop_back进行真正的删除。
    push_heap: 假设first到last-1是一个有效堆，要被加入到堆的元素存放在位置last-1，重新生成堆。
        要先在容器中加入数据，再调用push_heap()
    sort_heap：堆排序，时间复杂o(nlogn)

小结：
    *_if: 自定义判定函数；
    *_copy: 将输出结果拷贝到另一个容器中； 
    *_n: 作用于iterator开始的n个元素

举例说明：
    replace:
        1. 范围内等于old_value者都以new_value取代（原址替换）
        replace(ForwardIter first, ForwardIter last, const Tp& old_val, const Tp& new_val);
        2. 范围内满足Pred()为true的元素都以new_value取代（原址替换）
        replace_if(ForwardIter first, ForwardIter last, Predicate pred, const Tp& new_value);
        3. 范围内等于old_value者都以new_value放入新区间，不符合者原值放入新区间。
        replace_copy(InputIter first, InputIter last, OutputIter result, const Tp& old_val, const Tp& new_val);
        4. 范围内满足Pred()为true的元素都以new_value放入新区间，不符合者原值放入新区间。
        replace_copy_if(InputIter first, InputIter last, OutputIter result, Predicate pred, const Tp& new_val); 

    count:
        1. 统计范围内等于value的元素个数；
        count(InputIter first, InputIter last, const Tp& value);
        2. 统计范围内使得Predicate仿函数为true的元素的个数； 
        count_if(InputIter first, InputIter last, Predicate pred);

    find:
        1. 返回值等于val的第一个元素的迭代器；
        InputIter find(InputIter first, InputIter last, const Tp& val);
        2. 返回使得预测仿函数为true的第一个元素的迭代器；
        InputIter find_if(InputIte first, InputIter last, Predicate pred);

    sort:
        list、forward_list: 容器自身带sort()成员函数；
        array、vector、deque: 不带sort()成员函数；
        set、map、multiset、multimap：容器内自动排序，遍历即为排序态。
    全局sort函数：
        // 使用默认比较函数 默认按照从小到大排序。
        void sort(RandomAccessIterator first, RandomAccessIterator last);
        // 自定义比较函数  param1<param2时返回true，则按照从小到大排序。
        sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);   

    lower_bound/ upper_bound/ binary_search:
        1. 返回大于等于val的第一个元素：
        ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const Tp& val);
        2. 返回大于val的第一个元素：
        ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const Tp& val);
        2. 二分查找val是否存在：
        bool binary_search(ForwardIterator first, ForwardIterator last, const Tp& val);

    函数适配器：binder1st/binder2nd/not1/bind
    ** 仿函数可以被适配的条件：
    继承自unary_function或者binary_function函数模板的函数对象，并重载了()操作符。

    ** unary_function：一元函数对象的基类，可以回答argument_type、result_type的问题，可以被适配。
    template <class Arg, class Result>
    struct unary_function {
        typedef Arg argument_type;
        typedef Result result_type;
    };
    ** binary_function是二元函数的基类，可以回答first_argument_type、second_argument_type、result_type的问题，可以被适配。
    template <class Arg1, class Arg2, class Result>
    struct binary_function {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };

    ** 举例说明：
    template <typename T>
    struct less: public binary_function<T, T, bool> {
        bool operator() (const T& x, const T& y) const {
            return x < y;
        }
    };
    函数对象继承自binary_function，于是便有了三个typedef，于是能回答三个问题了，first_argument_type、second_argument_type、result_type，
    这三个问题需要在适配器处理的时候使用，所以就可以被类似binder2nd/not1/bind的函数适配。
    c++11(2.0)以后，bind1st/bind2nd被列为过时函数，将被bind取代。
*/

int myfun1(int x, int y) {
    return x + 2 * y;
}

struct myfun2 {
    int operator() (int x, int y) {
        return x + 2 * y;
    }
};

struct predFun {
    bool operator() (int a) {
        return (a >= 100);
    }
};

// 测试bind一个函数，函数对象类似，如 std::divides<double> my_divide;
double my_divide(double x, double y) {
    return x / y;
}

// 测试bind类的成员变量和成员函数
struct MyPair {
    double a, b;
    double multiply() { return a * b; }
};

int main() {

    int init = 100;
    int nums[] = {10, 20, 30};
    // 累计
    cout << accumulate(nums, nums+3, init) << endl;           // 累计（默认加法）100+10+20+30=160
    cout << accumulate(nums, nums+3, init, minus<int>()) << endl;   // 累计，减法 100-10-20-30=40
    // 自定义函数对象（仿函数）、函数指针
    cout << accumulate(nums, nums+3, init, myfun1) << endl;  // init=myfun1(init, *it) 220
    cout << accumulate(nums, nums+3, init, myfun2()) << endl;  // init=myfun2(init, *it) 220

    //replace/ replace_if/ replace_copy/ replace_copy_if
    vector<int> vi {1, 120, -1, 30, -1, 35, 7};
    replace(vi.begin(), vi.end(), -1, 100);
    replace_if(vi.begin(), vi.end(), predFun(), 20);

    // count/ count_if
    cout << count(vi.begin(), vi.end(), 20) << endl;
    cout << count_if(vi.begin(), vi.end(), predFun()) << endl;

    // find/ find_if
    auto it = find_if(vi.begin(), vi.end(), predFun());
    if (it != vi.end()) {
        cout << "find it=>" << *it << endl;
    }

    // sort
    sort(vi.begin(), vi.end());        // 1 7 20 20 30 35
    for_each(vi.begin(), vi.end(), show_item<int>); cout << endl;

    // lower_bound/ upper_bound/ binary_search
    auto it_low = lower_bound(vi.begin(), vi.end(), 20);   // 指向第一个20的位置
    auto it_upper = upper_bound(vi.begin(), vi.end(), 20);   // 指向第一个大于20的位置，也就是30所在的位置
    size_t count1 = it_upper - it_low;              // 随机访问迭代器支持减法
    size_t count2 = distance(it_low, it_upper);     // 可以计算任意两个迭代器之间的元素个数，计算结果和count1相同
    cout << "counts of val=20 is: " << count1 << ", " << count2 << endl;
    assert(binary_search(vi.begin(), vi.end(), 20) == true);
    assert(binary_search(vi.begin(), vi.end(), 200) == false);

    // bind2nd
    // 允许把函数对象less<int>()的第二个参数绑定为40，
    // 本来是二元函数x<y返回true，这里绑定后x<40返回true。
    // bind2nd是一个函数适配器，是为了修饰仿函数，返回一个仿函数，且继承自unary_functon，还可以继续被适配；
    // not1也是一个函数适配器，修饰完，返回的也还是一个仿函数。
    size_t n = count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 20)));   // 不小于20，输出5

    // bind：可以绑定函数、函数对象、成员函数、成员变量
    // _1 _2 _3... 占位符, 占位：表示预留着，调用的时候通过参数传递。
    using namespace std::placeholders;             // _1 _2 等占位符可见

    auto b1 = bind(less<int>(), _1, _2);          // 绑定函数名，参数1，参数2预留，通过实参传递
    cout << b1(10, 12) << endl;

    auto fn_five = bind(my_divide, 10, 2);         // 绑定函数名，参数1，参数2
    cout << fn_five() << endl;

    auto fn_half = bind(my_divide, _1, 2);         // 参数1预留，通过实参传递
    cout << fn_half(10) << endl;

    auto fn_invert = bind(my_divide, _2, _1);       // 预留参数1、参数2，通过实参传递，但位置颠倒
    cout << fn_invert(2, 10) << endl;

    auto fn_toint = bind<int> (my_divide, _1, _2);  // 支持传一个模板参数，这个模板参数是函数返回值类型，
    cout << fn_toint(10, 3) << endl;                // 不传的话，直接返回函数本来的类型。

    MyPair ten_two {10, 2};        // c++11后支持以统一初始化列表给成员对象赋值

    // 绑定成员函数和成员变量时，有一个参数，就是*this，类对象。
    // 绑定类成员函数首地址，参数1(*this)预留，可通过实参传递。
    // 注意类成员函数指针的语法： &类名::函数名
    // 静态函数指针： int (*pFunA)(int, int) = &MyClass::FunA;  pFunA(1, 2);
    // 普通成员函数指针：void (MyClass::*pFunB)() = &MyClass::FunB;  (obj->*pFunB)();
    auto b_memfn = bind(&MyPair::multiply, _1);    
    cout << b_memfn(ten_two) << endl;

    auto b_memdata = bind(&MyPair::a, ten_two);    // 绑定类成员变量首地址，参数1。调用时不需要传参数了
    cout << b_memdata() << endl;

    auto b_memdata2 = bind(&MyPair::a, _1);
    cout << b_memdata2(ten_two) << endl;

    // count_if(vi.begin(), vi.end(), bind2nd(less<int>(), 20)) 改写为：
    cout << count_if(vi.begin(), vi.end(), bind(less<int>(), _1, 20)) << endl;


    // heap（调用算法实现堆排序）
    // 第一种方法：创建堆、堆排序
    make_heap(vi.begin(), vi.end()); 
    sort_heap(vi.begin(), vi.end());
    copy(vi.begin(), vi.end(), ostream_iterator<int>(cout, " ")); cout << endl;

    // 方法二：不停的创建堆，并弹出堆顶元素
    while(vi.size() > 0) {
        make_heap(vi.begin(), vi.end());   // 创建大根堆 first最大
        pop_heap(vi.begin(), vi.end());    // first和last-1交换
        cout << vi.back() << " " << endl;  // 弹出堆顶元素
        vi.pop_back();
    }

    system("pause");
    return 0;
}