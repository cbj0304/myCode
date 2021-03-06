# c++11概述
<br/>
## c++11新特性
* 标准库
* 语言

<br/>
## c++11标准库头文件
	头文件不带.h
	#include <array>
	#include <forward_list>
	#include <tuple>
	#include <regex>
	#include <thread>
	#include <unordered_set>
	#include <type_traits>
	using namespace std;

<br/>
## 参考资料
* 各种编译器对c++11（c++2.0）的支持
	* https://isocpp.org/blog/2014/03/compiler-support-for-c11-and-c14
* c++资源网站
 * http://www.cplusplus.com
 * https://zh.cppreference.com
 * https://gcc.gnu.org/
* 参考书籍
 * Effective Modern C++
* GNU什么意思
 gnu=GNU's Not Unix! 类似unix的自由操作系统。gnu计划是实现unix系统的标准接口，目标创建是一套完全自由的操作系统。

<br />
#语言部分

<br />
## Variadic Templates
概念：可变参数个数模板
<br/>
>**第一种实现：函数递归调用**
基本思想：把n个（任意个）参数分成1和n-1个，每次可以只处理1个，剩下的n-1个递归执行，很好地借用了递归思想从而极大地增大了代码的复用性。

	#include <iostream>
	#include <cstdio>
	using namespace std;

	/*
	场景：
	variadic_template(可变参数个数的模板)
	泛型编程、类模板/函数模板：
	原来模板参数可以使类和函数的  "参数类型任意化"，此处的variadic_template可以让 "参数个数任意化"
	目标：类和函数的复用性
	实现：...表示 包
	利用参数个数逐一递减的特性，实现递归函数调用。
	*/
	
	void print() { }
	 
	template <typename T, typename... Types> //...出现在这表示模板参数包
	void print(const T& firstArg, const Types&... args)    //...函数参数类型包
	 {
	    // 1. 处理第一个参数
		cout << firstArg << endl;
	    // 2.  递归处理剩余的参数
		print(args...);    //...函数参数包
	}
	 
	int main()
	{
		print(7.5,"hello","what",42);
	    system("pause");
		return 0;
	}

<br/>
>**第二种实现：类继承实现递归**
典型案例：C++11中tuple（元组）的实现，它是把任意个数任意指定类型的东西形成的一个块或者对象。

	#include <iostream>
	#include <string>
	#include <cstdlib>
	using namespace std;
	
	/*
	1. variadic_template(可变参数个数模板)的应用：自己实现一个tuple容器
	第一种方式：通过类的继承实现递归（本例）
	第二种方式：通过类的组合实现递归
	
	2. 全特化与偏特化
	偏特化：如果模板有多种类型，那么只限定其中的一部分。
	全特化：限定死模板实现的具体类型。
	// 类模板声明
	template<typename T1, typename T2>
	class Test {...}
	// 全特化版本
	template<>
	class Test<int , char> {... }
	// 偏特化版本
	template <typename T2>
	class Test<char, T2> {... }
	*/
	
	
	// 类模板声明
	template<typename... val>
	class mytuple;
	
	// 特化版本 (递归结束条件)
	template<>
	class mytuple<> {};
	
	// 偏特化版本(递归继承自身)
	template<typename Head, typename... Tail>
	class mytuple<Head, Tail...> : private mytuple<Tail...> {
	protected:
	    typedef mytuple<Tail...> inherited;
	    Head m_head;   
	
	public:
	    mytuple(){}
	    mytuple(Head v, Tail... vtail) : m_head(v), inherited(vtail...){ }
	
	    Head head() {return m_head;}
	
	    // 此处返回基类的引用，c++多态性，可以把派生类的引用赋值给基类的引用！！！
	    inherited& tail() {return *this;}  // *取引用操作符，返回左值引用 
	
	};
	
	int main(){
	    /*
	    mytuple<int, string, double>  继承自 mytuple<string, double>，里边有一个int和一个指向父类的引用
	    mytuple<string, double> 继承自 mytuple<double>，里边有一个string和一个指向父类的应用
	    mytuple<double> 继承自 mytuple<>, 里边有一个指针和一个指向父类的引用
	    mytuple<>
	    */
	    mytuple<int, string, double> tu(42, "hello", 1.35);
	    cout << sizeof(tu) << endl;
	    cout << tu.head() << endl; 
	    cout << tu.tail().head() << endl;
	    cout << tu.tail().tail().head() << endl;
	    system("pause");
	    return 0;
	}

<br/>
>**第三种实现：类组合实现递归**

	#include <iostream>
	#include <string>
	#include <cstdlib>
	using namespace std;
	
	/*
	1. variadic_template(可变参数个数模板)的应用：自己实现一个tuple容器
	第一种方式：通过类的继承实现递归
	第二种方式：通过类的组合实现递归（本例）
	*/
	
	// 模板类的声明
	template<typename... Value> 
	class mytuple;
	
	// 全特化版本(递归结束条件))
	template<>
	class mytuple<> {};
	
	// 偏特化版本
	template<typename Head, typename... Tail>
	class mytuple<Head, Tail...> {
	protected:
	    typedef mytuple<Tail...> composited;
	    Head m_head;
	    composited m_tail;
	public:
	    mytuple() {}
	    mytuple(Head v, Tail... tail): m_head(v), m_tail(tail...){}
	
	    Head head(){
	        return m_head;
	    }
	
	    composited& tail() {
	        return m_tail;
	    }
	};
	
	int main(){
	
	    mytuple<int, string, double> tu(12, "hello", 1.2);
	    cout << tu.head() << endl;
	    cout << tu.tail().head() << endl;
	    cout << tu.tail().tail().head() << endl;
	    system("pause");
	    return 0;
	}



<br/>
## 连续两个>符号
> vector<list<int> >  // 以前版本两个>之间要有空格
 vector<list<int>>   // ok since c++11

<br/>
## 空指针
c++11中用关键词nullptr取代之前版本的0或者NULL,避免避免空指针和0混用的误会。

> void f(int);
 void(void *);
 f(NULL)->之前版本，会调用f(int);
 f(nullptr)->c++11以后，会调用f(void *)

<br/> 
## auto/decltype
> **自动类型推导：auto / decltype**
* auto用法：
场景：编译器根据表达式的值推导变量类型，auto定义变量必须有初始值，才能推导。
举例：
  auto a = i,&b = i,*c = &i;//正确: a初始化为i的副本,b初始化为i的引用,c为i的指针。
  auto item = val_1 + val_2;
* decltype的用法：
场景：
以下场景auto就显得无能为力了。
 * 推断表达式中的类型，用于定义表达式/变量。
 * 推断函数的返回值的类型，用于定义表达式/变量。
以上过程中编译器只是分析表达式类型，并不计算表达式的值。

<br/>
**第一部分：auto自动类型推导**

	#include <iostream>
	#include <vector>
	#include <list>
	#include <string>
	#include <typeinfo>
	#include <cstdlib>
	using namespace std;
	
	double sum(double a, double b){
	    return a + b;
	}
	
	int main(){
	    // 基本类型推导
	    auto i = 60;
	    auto c = sum(1.2, 3.4);
	    cout << "c=" << c << ", type=" << typeid(c).name() << endl;
	
	    // 类型较复杂时：迭代器
	    vector<list<string>> v;
	    auto pos = v.begin();
	    cout << (*pos).size() << endl;
	
	    // 类型较复杂时：lambda函数
	    auto f = [](int x)->bool { cout << "x+10=" << x+10 << endl; return true;};
	    cout << f(22) << endl;
	
	    system("pause");
	    return 0;
	}

<br/>
**第二部分：decltype自动类型推导**
	#include <iostream>
	#include <map>
	#include <string>
	#include <cstdlib>
	#include <typeinfo>
	using namespace std;
	
	
	template <typename T>
	auto sum(T x, T y) -> decltype(x+y) {
	  return x+y;
	}
	
	auto max(int x, int y) {
	    cout << "test" << endl;  // 推导函数返回类型时，函数体并不会被执行
	    return x > y ? x : y;
	}
	
	int main(){
	    map<string,float>::value_type elem1;
	    map<string,float> col;
	    col = {std::pair<string,float>("a1",1.1),std::pair<string,float>("a2",1.2)};  // 统一初始化列表
	    col.insert(std::pair<string,float>("a",1.1));
	    for (decltype(col)::value_type elem2 : col){
	        cout << elem2.first << "," << elem2.second << endl;
	    }
	
	    int data = 1000;
	    int *p = new int();
	    decltype(*p) p1 = data;   // decltype作用于接引用(*)操作，推导的结果是引用 int&
	
	    int i = 42;
	    decltype(i) ia = 100;    // 推导出来是 int
	    decltype((i)) ib = data; // 推导出来是 int& => 加括号，变表达式，变量是一个可以作为左值的特殊表达式
	    decltype(i = 50) ic = data; // 推导出来是 int&  => 赋值运算符返回的是左值引用
	    cout << "i=" << i << endl;  // decltype只作类型推导，并不实际计算，所以i还是42
	
	    cout << sum(3, 4) << endl;
	
	    decltype(max(5,6)) idata = 100;
	    cout << typeid(idata).name() << endl;
	
	    system("pause");
	    return 0;
	}

## 类型别名和模板别名
>c++11新增关键词 using 表示别名。
说明：类型的别名可增加可读性，没有产生新类型。
* 类型别名(type alias)
  * 基本类型别名(三种方式)：
    使用关键字 typedef => typedef unsigned short  uint16_t;
    使用预编译宏 #define => #define uint16_t unsigned short;
    c++11使用using定义别名 => using uint16_t = unsigned short;
  * 函数指针类型别名：
    typedef void (*func)(int, int); <=> using func = void (*)(int, int); 
<br/>
* 模板别名(template alias)
  template <typename T>
  using Vec = std::vector<T, MyAlloc<T>>;
  
>  Vec<int> col;
  等价于：
  template <typename T>
  std::vector<int, MyAlloc<int>> col;

	#include <iostream>
	#include <list>
	#include <deque>
	#include <vector>
	#include <iterator>
	#include <cstdio>
	#include <cstdint>	
	using namespace std;
	
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


<br/>
## 关键字 
### delete/default
>* c++11 构造函数和析构函数（big five）
 * 构造
 * 拷贝
 * 赋值
 * 右值拷贝
 * 右值赋值
 * 析构函数
以上特殊的成员函数，如果用户未显示定义，则编译器会隐式的生成一个对应的默认成员函数。
<br/>
* =default =delete
 * "=default"  ---  自动生成函数体
函数特性仅适用于类的特殊成员函数（以上5个），且该特殊成员函数没有默认参数。编译器为显示声明的"=default"函数自动生成函数体。
 * "=delete"  --- 禁用某个函数
让程序员显式的禁用某个函数。可以禁用以上特殊成员函数，还可以禁用某些转换函数、自定义new操作符等

	#include <iostream>
	#include <cstdio>
	using namespace std;
	
	class Zoo {
	public:
	    // 构造函数
	    Zoo(int i1, int i2):d1(i1),d2(i2){}
	    // 拷贝
	    Zoo(const Zoo&)=delete;
	    // 赋值
	    Zoo& operator=(const Zoo&)=default;
	    // 右值拷贝
	    Zoo(Zoo&&)=default;
	    // 右值赋值
	    Zoo& operator=(const Zoo&&)=delete;
	    virtual ~Zoo() {}
	private:
	    int d1,d2;
	};
	
	class X{
	public:
	    // 禁用某些用户自定义的类的 new 操作符，从而避免在自由存储区创建类的对象
	    void *operator new(size_t) = delete;
	    void *operator new[](size_t) = delete;
	};
	
	int main(){
	    X X1 = new X;   // 报错，new操作符被禁用
	    Zoo z(1,2);
	    Zoo z1(z);      // 报错，拷贝构造函数被禁用
	    system("pause");
	    return 0;
	}

<br/>
### final/override
>c++11 final 关键字：禁止继承和重写

	#include <iostream>
	#include <cstdlib>
	using namespace std;
	
	// 例1：基类禁止被继承
	// Error: a 'final' class type cannot be used as a base class
	class Shape final {
	    // ...
	};
	
	class Rectangle : public Shape {      // 异常（不能将final类类型作为基类）
	    // ...
	};
	
	// 例2：虚函数禁止被重写(覆盖)
	// Error： cannot override 'final' function "Shape1::Draw" (declared at line 23)
	class Shape1 {
	public:
	    virtual void Draw() final {
	        cout << "Shap1 Draw..." << endl;
	    }
	};
	
	class Rectangle1 : public Shape1 {
	public:
	    void Draw() override {        // 异常（不能重写final类型的函数）
	        cout << "Rectangle1 Draw..." << endl;
	    }
	};
	
	int main(){
	    system("pause");
	    return 0;
	}

<br/>
>* override(重写): 
c++11中，子类重写父类的(纯)虚函数时，如果函数声明后边加上override,编译器就会对非法的重写操作校验并报错。
 * 父类中无此函数，或父类中的函数并不是虚函数，编译器会报错。
 * 父类和子类中成员函数的 返回类型、异常规格、函数名、形参类型、常量属性、引用限定符等不一致，编译器会报错。
<br/>
* 补充知识：c++公有继承：
 * 纯虚函数  => 继承的是：接口
 * 虚函数   => 继承的是：接口+缺省实现（子类可以重写(覆盖)父类的实现） -- 多态、动态绑定
 * 非虚函数  => 继承的是：接口+强制实现   -- 静态绑定

	#include <iostream>
	#include <string>
	#include <cstdlib>
	using namespace std;
	
	class Shape {
	public:
	    virtual void Draw() const = 0;    // 纯虚函数
	    virtual void Error(const string& msg) {
	        cout << "Shape Error" << endl;
	    };  // 虚函数
	    int ObjectID() const;         // 非虚函数
	};
	
	class Rectangle: public Shape {
	public:
	    virtual void Draw() const override {
	        cout << "Draw Rectangle..." << endl;
	    }
	    virtual void Error(const string& msg) override {
	        cout << "Rectangle Error " << msg << endl;
	    }
	
	};
	
	class Ellipse : public Shape {
	public:
	    // 纯虚函数必须重写，虚函数如果子类没有重写则继承父类默认的
	    virtual void Draw() const override {
	        cout << "Draw Ellipse" << endl;
	    }
	};
	
	
	int main(){
	    // 动态绑定，调用子类的重写的虚函数和纯虚函数的实现
	    Shape *rec = new Rectangle();
	    rec->Draw(); 
	    rec->Error("rec error");       
	
	    Shape *el = new Ellipse();
	    el->Draw();
	    el->Error("el error");   // 子类没有重写父类的虚函数，则调用父类默认的实现
	
	    el->Shape::Error("shape error");  // 子类通过作用域符号::调用父类的虚函数实现
	
	    system("pause");
	    return 0;
	}

### explicit
>* c++03以前的版本中 explicit关键词：
条件：单个参数的构造函数（因为无参数构造函数和多参数构造函数总是显示调用，explicit无意义）
作用：阻止对象构造时 隐式类型转换，只能显示的调用构造函数
例如：
构造函数： explicit A(bool flag){...}
不能这样调用： A=false;
<br/>
* c++11扩展：c++11中由于可以通过"初始化参数列表"构造对象,所以可以修饰多参数的构造函数
作用：阻止通过参数列表构造，只能显示的通过调用构造函数构造对象。

	#include <iostream>
	#include <cstdio>
	using namespace std;
	
	class Complex{
	public:
	    explicit
	    Complex(int re, int im=0):real(re), imag(im) { }
	
	    Complex operator+(const Complex& x){
	        return Complex(real + x.real, imag + x.imag);
	    }
	    // 重载输出运算符
	    friend ostream& operator<< (ostream &out, Complex& x){
	        out << "re=" << x.real << ", im=" << x.imag << endl;
	        return out;
	    }
	private:
	    int real;
	    int imag;
	};
	
	class P {
	public:
	    explicit
	    P(int a, int b, int c):m_a(a), m_b(b), m_c(c){
	    }
	
	    // 重载输出运算符
	    friend ostream& operator<< (ostream &out, P& x){
	        out << x.m_a << x.m_b << x.m_c << endl;
	        return out;
	    }
	private:
	    int m_a;
	    int m_b;
	    int m_c;
	};
	
	int main(){
	    Complex c1(12, 4);
	    // Complex c2 = c1 + 5;  // 报错,隐式转换失败
	    Complex c2 = c1 + Complex(5);  // 显示的调用构造函数没有问题
	    cout << c2 << endl;
	
	    // P p = {1, 3, 4};   // 报错，隐式转换
	    P p(1,2,4);      // 显示的调用构造函数没有问题   
	    cout << p << endl;
	    system("pause");
	    return 0;
	}

### noexcept
>* c++异常处理机制：
   throw... try... catch...

>   throw  表达式（异常是一个表达式可以是基本类型，也可以是类）;

>   try {
    语句组 
   } catch(异常类型) {
    异常处理代码
   }
<br.>
* c++11异常处理：
   * 可以抛出任意异常 （和之前默认版本一样）
   * 不可以抛出异常 （使用关键词 noexcept）
     * 该关键字告诉编译器，函数中不会发生异常,这有利于编译器对程序做更多的优化。
     * 如果在运行时，noexecpt函数向外抛出了异常,程序会直接终止 std::abort()

	#include <iostream>
	#include <cstdlib>
	using namespace std;
	
	void cxx_try_catch_test()
	{
	    int age;
	    cout << "input your age: ";
	    cin >> age;
	    if (age < 0) {
	        cout << "age cannot be negative！" << endl;
	        throw - 1;
	    }
	}
	
	// 第一种情况：noexcept 告诉程序员此函数不会抛出异常，
	// 不必深入所有的调用层自己去确认函数是否会剖出异常
	void cxx11_try_catch_test1() noexcept
	{
	    try {
	        cxx_try_catch_test();
	    } catch (int e){
	        cerr << "err=" << e << endl;  
	    }
	}
	
	// 第二种情况：noexcept 表示即使是抛出了异常，在main函数中通过try...catch也无法捕获异常
	void cxx11_try_catch_test2() noexcept
	{
	    cxx_try_catch_test();
	}
	
	int main()
	{
	    // c++中的try...catch
	    try {
	        cxx_try_catch_test();
	    } catch (int e) {
	        // 打印错误并处理异常
	        cerr << "err=" << e << endl;
	    }
	
	    // 函数不会抛出异常，内部已捕获了
	    cxx11_try_catch_test1();
	
	    // 函数即使抛出异常，也捕获不到，直接终止
	    try {
	        cxx11_try_catch_test2();
	    } catch (int e) {
	        // 打印错误并处理异常
	        cerr << "err_cxx11=" << e << endl;   // 捕获失效
	    }
	    system("pause");
	    return 0;
	}
<br/>
## for循环

	#include <iostream>
	#include <vector>
	#include <string>
	#include <algorithm>
	#include <cstdio>
	
	using namespace std;
	
	void show(string& s) {cout << s << endl;}
	
	int main(){
	    vector<string> v {"hello", "you", "and", "me"};
	    // 值拷贝（副本）
	    for(string elem : v){
	        cout << elem << " ";
	    }
	
	    // 引用（可以修改原值）
	    for(string& elem1 : v){
	        elem1 += "haha";
	    }
	
	    for(const string& elem2 : v){
	        cout << elem2 << " ";
	    }
	
	    for_each(v.begin(), v.end(), show);
	    
	    system("pause");
	    return 0;
	}

<br/>
## lambda函数

>* 语法定义：（采用了追踪返回类型的方式声明其返回值)
* 格式：
    [capture-list](parameters-list) -> return-type{function-body;}
* 说明：
    * capture-list ：捕捉列表，捕捉上下文中的变量以供lambda函数使用（必选）
    -- []    表示  空捕捉
    -- [=]   表示值传递方式捕捉所有父作用域的变量(包括this)
    -- [&]   表示引用传递方式捕捉所有父作用域的变量(包括this)
    -- [var] 表示值传递方式捕捉变量var
    -- [&var]表示引用传递方式捕捉变量var  
    -- [this]表示值传递方式捕捉当前this指针 (this。函数体内可以使用Lambda所在类中的成员变量。)
    -- 其它组合形式：
    * parameters-list : 参数列表（可选）
    * return-type : 返回类型（可选）
    * function-body : 函数体（必选）

	#include <iostream>
	#include <cstdlib>
	#include <string>
	#include <vector>
	#include <algorithm>
	using namespace std;
	
	class Test{
	public:
	    Test(int a, int b): m_a(a),m_b(b){}
	    void f1(int t){
	        auto f = [this] {return m_a + m_b;}; // 省略参数列表，返回值由编译器推断为int
	        cout <<__FILE__<< __LINE__ << "\t"  << f() + t <<endl;
	    }
	    int m_a;
	    int m_b;
	};
	
	class func{
	public:
	    func(int x, int y): m_x(x), m_y(y) {} 
	    bool operator () (int item) {
	        return (item > m_x && item < m_y);
	    }
	private:
	    int m_x;
	    int m_y;
	};
	 
	int main()
	{
	    [] {};  // 最简lambda函数（必须有捕获列表和函数体）
	    int a = 3;
	    int b = 4;
	
	    // [=]
	    auto c = [=] {return a + b;}; // 省略参数列表，返回值由编译器推断为int
	    cout <<__FILE__<< __LINE__ << "\t"  << c() << endl;
	
	
	    // [&]
	    auto d = [&] {b += 2; return a + b;}; // 省略参数列表，返回值由编译器推断为int
	    cout <<__FILE__<< __LINE__ << "\t"  << d()  << "\t" << d() << endl;
	
	
	    // 组合
	    auto mytest = [=, &b] (const string& str) -> decltype(a+b) {
	        b = 100; 
	        cout << str << endl; 
	        return a+b;
	    };
	    cout << mytest("my test=>") << endl;
	
	    // mutable / read-only
	    auto ia = 30;
	    auto f1 = [ia] () mutable { ia += 1; return ia + 100;};
	    // error: assignment of read-only variable 'ia'
	    // auto f2 = [ia] () { ia += 1; return ia + 100;};
	    auto f3 = [&ia] {ia += 1; return ia + 100;};
	
	    cout << "f1=" << f1() << endl;
	    // cout << "f2=" << f2() << endl;
	    cout << "f3=" << f3() << endl;
	
	    // [this]
	    Test t(1,2);
	    t.f1(9);
	
	    // 和std算法一起用，功能和函数对象类似
	    vector<int> vec {10, 20, 30, 40, 50, 60};
	    int x = 30, y = 60;
	    // 匿名函数
	    vec.erase(remove_if(vec.begin(), vec.end(), 
	               [x, y] (int item) -> bool {return (item > x && item < 60);})
	               , vec.end());
	    // 函数对象
	    vec.erase(remove_if(vec.begin(), vec.end(), 
	              func(x, y))
	              , vec.end());
	    for(auto ii : vec){
	        cout << ii << endl;
	    }
	
	    system("pause");
	    return 0;
	}

<br/>
## 统一初始化列表
>* 格式：大括号{...}
* 适用于：数组、stl容器（vector/list/string/set/deque...）、类构造
* 实现原理：
编译器看到 {t1,t2... tn}时便会做出一个initializer_list<T>,它关联至一个array<T,n>。
调用构造函数时（构造函数接受initializer_list<T>类型的参数），该array内的元素可被编译器分解逐一赋值给函数。
举例说明：
vector<string> cities {"Beijing", "New York", "London","Berlin"};
编译器遇到{}，生成一个initializer_list<string>,背后有个array<string, 4>，
调用vector<string>构造函数时，编译器找到其中一个构造函数接受initializer_list<string>。
例如：
vector(initializer_list<value_type> __I){...}
vector& operator=(initializer_list<value_type> __I){...}
void insert(iterator __position, initializer_list<value_type> __I){...}
void assign(initializer_list<value_type> __I){...}
min(initializer_list<value_type> __I){...}
max(initializer_list<value_type> __I){...}
根本原因：这些容器的构造函数有一个接受initializer_list<value_type>类型参数的构造函数！！！
* initializer_list不仅可以用于构造函数的参数，还可以用于自定义函数的参数，用于处理一组相同类型的参数。

	#include <iostream>
	#include <vector>
	#include <string>
	#include <map>
	#include <algorithm>
	#include <cstdio>
	using namespace std;
	
	void printV(string s) { cout << s << " ";}
	
	// 自定义参数列表
	void print(std::initializer_list<int> vals){
	    for(auto p=vals.begin(); p!=vals.end(); ++p){
	        cout << *p << endl;
	    }
	}
	
	int main(){
	    // 复习c++的初始化方式（等号、小括号、大括号、构造函数等）
	    int i1 = 5;
	    int i2 = int(5);
	    int i3[3] = {3, 5, 7};
	    cout << i1 << i2 << i3[0] << endl; 
	
	    // c++11统一初始化(大括号)
	    int a[4] = {1, 2, 3, 4};
	    int *b = new int[3]{11, 22, 33};
	    vector<string> vec = {"hello", "word"};
	    map<string, int> m = {{"you", 10}, {"I", 20}};
	
	    // c++11以后，以下stl中定义的函数均支持传initializer_list<T>作为参数
	    vector<int> v1 = {100, 200, 300};
	    vector<int> v2 {400, 500, 600};
	    vector<int> v3 ({700, 800, 900});
	    v3.insert(v3.end(), {1000, 1100});
	    cout << max({string("aa"), string("cc"), string("bb")}) << endl;
	
	    int i{};  // 初始化为0
	    int *p{}; // 初始化为空指针
	
	    // 自定义参数列表
	    print({11,22,33,44,55,66});
	
	    system("pause");
	    return 0;
	}


<br />
# 标准库部分
<br/>
## c++11新增容器

>* **array**
1. 为什么要引入 std::array 而不是直接使用 std::vector？
std::vecotr 太强大了，以至于我们没有必要为了去敲碎一个鸡蛋而用一个钉锤。
使用 std::array 保存在栈内存中，相比堆内存中的 std::vector，我们就能够灵活的访问这里面的元素，从而获得更高的性能；
2. 已经有了传统数组，为什么要用 std::array?
(1)代码更现代化，操作更方便 fill size at(i) ...
(2)越界检查（安全）
(3)和内置数组占用相同的内存，但是写入效率较低（低效换来了安全和便利）
(4)更方便的使用标准库的容器算法，如std::sort
<br/>
* **forward_list**
std::list是双向循环链表
std::forward_list是单向链表，插入操作o(1),没有size()方法，比list空间利用率更高，操作方法和list类似。
<br/>
* **unordered_set/unordered_map**
std::set/std::map内部实现是红黑树，插入和搜索时间复杂度是o(logN),输出元素有序。
unordered_set/unordered_map内部通过哈希表实现，插入和搜索时间复杂度o(1),无序，性能有提升。用法与set/map类似。
<br/>
* **tuple**
用于存放不同类型的数据。
<br/>
* **全局begin/end**

	#include <iostream>
	#include <cstdlib>
	#include <vector>
	#include <array>
	#include <forward_list>
	#include <unordered_set>
	#include <unordered_map>
	#include <tuple>
	#include <algorithm>
	using namespace std;

	int main(){
	    // array
	    array<string,6> strArr;
	    strArr.fill("test");
	    for (string s : strArr) {
	        cout << s << " ";
	    }
	    cout << strArr.size() << endl;
	
	    array<int,6> arr {12,45,23,1};
	    std::sort(arr.begin(), arr.end());
	    for(auto it = arr.begin(); it !=arr.end(); it += 2){
	        cout << *it << endl;
	    }
	
	    // forward_list
	    forward_list<int> fl;
	    fl.push_front(10);
	    fl.push_front(20);
	    fl.push_front(30);
	    fl.pop_front();
	    cout << fl.front() << endl;
	
	    // unordered_set/unordered_map
	    unordered_map<int, string> mymap = {{1, "aaa"}, {2, "bbb"}, {3, "ccc"}};
	    for(const auto& m : mymap){
	        cout << m.first << ", "  << m.second << endl;
	    } 
	    unordered_set<string> myset;
	    cout << myset.bucket_size(myset.size()-1) << endl;  // 返回下标为 n 的桶中的元素数
	    myset.insert("hello");
	    myset.insert({"world", "aaa", "ccc"});
	    for(const auto & s : myset) {
	        cout << s.data() << endl;
	    }
	
	    //tuple
	    tuple<string, int, char> student = make_tuple("zhangsan", 18, 'A');
	    cout << get<0>(student) << ","
	         << get<1>(student) << ","
	         << get<2>(student) << endl;
	    // 元组拆包
	    string name("");
	    int age = 0;
	    char level = 0;
	    tie(name, age, level) = student;
	    cout << "name=" << name << " age=" << age << " level=" << level << endl;
	
	    // begin/end
	    vector<int> v {1,2,3,4,5};
	    auto b = begin(v);
	    auto e = end(v); e--;     // 左开右闭的特性
	    cout << "begin=" << *b << " end=" << *e;
	    
	    system("pause");
	    return 0;
	}

<br/>
## 右值引用
>* c++11右值引用：
解决不必要的深拷贝，提升容器效率。
等号的右边（来源端）是一个右值，等号的左边的对象可以偷来源端的而不是重新分配空间和拷贝。
<br/>
* 左值和右值：
左值:可以出现在等号的左边。
右值：只能出现在等号的右边。
int a=10;
int b=a;
a = a + b;
变量a、b是左值，表达式a+b是右值。
临时对象是右值。
<br/>
* 左值引用和右值引用：
左值引用：常规引用。
右值引用：必须绑定到右值的引用，通过&&获取，只能绑定到一个将要被销毁的对象上，因此可以自由的移动（偷盗）其资源。
 * 举例1：
容器中，insert()、push_back()等函数都有两个版本：
insert(..., & x)     // 左值引用版本
insert(..., && x)    // 右值引用版本
编译器遇到临时对象，一定把它当做右值，然后调用右值参数的版本，
因此不真正发生指针深拷贝，而是偷临时对象的东西（把指针指向临时变量的位置就好了，即指针浅拷贝），
指针浅拷贝可能有风险，被move之后，原临时对象就不能再用了，原临时对象的指针要设置为NULL(保证临时对象消失调用析构函数的时候不会释放对应的内存空间)。
 * 举例2：
传入参数是左值，调用左值版本
传入参数是右值，调用右值版本
std::move(a) -> a被强转成右值，调用右值版本
-- 完美转交：在函数层级调用中，始终保持实参的左值、右值特性。通过std::forword函数实现。
-- 不完美转交：
临时对象是右值，因为他没有名字。但是右值在多层传递中，在实参中有了命名，变成了一个左值，接下来会调用左值版本，造成深拷贝浪费。c++11通过forward函数实现完美转交，做原来是右值，则经过forward转换一直是右值。
<br/>
* std::forward和std::move的联系和区别
（1）std::move是无条件转换，不管它的参数是左值还是右值，都会被强制转换成右值。就其本身而言，它没有move任何东西。
（2）std::forward是有条件转换。只有在它的参数绑定到一个右值时，它才转换它的参数到一个右值。当参数绑定到左值时，转换后仍为左值。
（3）std::move和std::forward在运行期都没有做任何事情。
<br/>

	#include <iostream>
	#include <cstdlib>
	using namespace std;
	
	// 左值引用版本(传入左值会调用左值引用版本)
	void process(int& i) {
	    cout << "process(int&) " << i << endl;
	}
	// 右值引用版本(重载版本，传入右值调用右值引用版本)
	void process(int&& i) {
	    cout << "process(int&&) " << i << endl;
	}
	
	// 不完美转交
	void myprocess(int&& i) {
	    cout << "myprocess(int&&) " << i << endl;
	    process(i);
	}
	
	// 完美转交
	void myprocess2(int&& i) {
	    cout << "myprocess2(int&&) " << i << endl;
	    process(std::forward<int>(i));
	}
	
	int main(){
	
	    int a = 0;
	    process(a);   // a是左值，调用左值版本
	
	    process(1);   // 常量表达式1是右值，调用右值版本
	
	    process(std::move(a));  // move函数将a强转为右值，调用右值版本
	
	    myprocess(2);   // 不完美转交：常量2是右值，经由myprocess传给另一个函数变成了左值（原因是传输过程中它变成了一个named object，不是临时对象了）
	
	    myprocess(move(a)); // 不完美转交：a经由myprocess传给另一个函数变成了左值
	
	    myprocess2(2); // 完美转交
	
	    // myprocess(a);   // 无左值版本，调用失败
	
	    const int& b = 1;
	    // process(b);  // 左值引用 无const版本 process(const int&)
	    // process(move(b));  // 无参数匹配的版本
	
	    system("pause");
	    return 0;
	}

<br/>
## 实现mystring类
>1. c++11右值引用：
c++11以后的容器，拷贝构造/拷贝赋值/insert/push_back等函数都增加了右值引用版本，
右值引用的本质是浅拷贝，相比深拷贝（左值引用版本）有更大的性能优势。
浅拷贝不需要重新分配空间和赋值操作，只是拷贝指针指向，也就是偷盗源端（左值）的东西。
浅拷贝后，右值(一般是临时对象）一般不能再用了，否则会出问题，
所以临时对象的指针会赋值为NULL,保证临时对象消失调用析构函数的时候不会释放对应的内存空间,
配合析构函数中类似 if (ptr != NULL) { // 执行内存释放...} 的写法。
<br/>
2. 举例1：
容器中，insert()、push_back()等函数都有两个版本：
insert(..., & x)     // 左值引用版本
insert(..., && x)    // 右值引用版本
编译器遇到临时对象，一定把它当做右值，然后调用右值参数的版本，
因此不真正发生指针深拷贝，而是偷临时对象的东西（把指针指向临时变量的位置就好了，即指针浅拷贝），
指针浅拷贝可能有风险，被move之后，原临时对象就不能再用了，原临时对象的指针要设置为NULL。
<br/>
3. 深拷贝和浅拷贝：
浅拷贝只是对指针的拷贝，拷贝后两个指针指向同一个内存空间；
深拷贝不但对指针进行拷贝，而且对指针指向的内容进行拷贝，经深拷贝后的指针是指向两个不同地址的指针。
浅拷贝可能导致一块内存空间被释放两次，导致内存泄露，程序崩溃。可使用智能指针解决类似的问题。
<br/>
4. 案例：自己实现myString，完成big five 特殊函数。
构造函数的特点：名称和类名相同，没有返回类型。
 * 拷贝构造(深拷贝)
 * 拷贝赋值(深拷贝)
 * 右值拷贝构造(浅拷贝)
 * 右值拷贝赋值(浅拷贝)
说明：拷贝赋值比拷贝构造多一步校验：自己是否有值？(有值先清空)；是否是自己赋值给自己？(如果赋值给自己则直接返回))；

	#include <iostream>
	#include <cstdlib>
	#include <cstring>
	
	using namespace std;
	
	class MyString{
	private:
	    char* _data;
	    size_t _len;
	
	public:
	    // 默认构造函数
	    MyString():_data(NULL), _len(0) {}
	    
	    MyString(char* data) {
	        cout << "MyString(char* data)" << endl;
	        _len = strlen(data);
	        _data = new char[_len+1];
	        memcpy(_data, data, _len);
	        _data[_len] = '\0';
	    }
	
	    // 拷贝构造函数(深拷贝)
	    MyString(const MyString& str) {
	        cout << "MyString(const MyString& str)" << endl;
	        _len = str._len;
	        _data = new char[_len+1];
	        memcpy(_data, str._data, _len);
	        _data[_len] = '\0';
	    }
	
	    // 拷贝赋值函数(深拷贝)
	    MyString& operator=(const MyString& str) {
	        cout << "MyString& operator=(const MyString& str)" << endl;
	        // 自己赋值给自己不需任何操作，别人赋值给自己，需要先清空自己
	        if (this != &str) {
	            if (_data) { delete _data;}
	            _len = str._len;
	            _data = new char[_len+1];
	            memcpy(_data, str._data, _len);
	            _data[_len] = '\0';
	        }
	        return *this;
	    }
	
	    // move版本的拷贝构造函数（浅拷贝）
	    MyString(MyString&& str) noexcept {
	        cout << "MyString(MyString&& str) noexcept" << endl;
	        _len = str._len;
	        _data = str._data;  // 浅拷贝 move操作
	        str._len = 0;
	        str._data = NULL;  // 重要，和析构函数配合，防止内存释放两边导致内存泄露
	    }
	
	    // move版本的拷贝赋值构造函数（浅拷贝）
	    MyString& operator= (MyString&& str) {
	        cout << "MyString& operator= (MyString&& str)" << endl;
	        if(this != &str) {
	            if(_data) { delete _data;}
	            _data = str._data;
	            _len = str._len;    // 浅拷贝 move操作
	            str._len = 0;
	            str._data = NULL;   // 重要，防止内存泄露
	        }
	    }
	
	    virtual ~MyString(){
	        cout << "virtual ~MyString()" << endl;
	        if (_data != NULL) {
	            delete _data;
	        }
	    }
	
	    void show(){
	        if (_len > 0) {
	            cout << "data=" << _data << endl;
	        }
	    }
	
	};
	
	int main(){
	    MyString ms1;
	    char str[] = "hello";
	    cout << "sizeof=" << sizeof(str) << endl;   // 输出6. 字符串一共占多少字节，包括'\0'
	    cout << "strlen=" << strlen(str) << endl;   // 输出5. 以 '\0' 为结束符号
	    MyString ms2(str);
	    ms1 = ms2;
	    ms1.show();
	
	    // 调用右值构造函数
	    MyString ms3(std::move(ms2));
	    ms3.show();
	    system("pause");
	    return 0;
	}

<br/>
## 智能指针
>1. 智能指针的作用：
（1）处理内存泄露的问题（申请了内存，没有释放）
（2）处理空悬指针（野指针）的问题，野指针不是nullptr，它会指向垃圾内存，给程序造成隐患。
（3）处理比较隐晦的由异常造成的资源泄露的问题（如异常导致程序退出，但是申请的内存没有释放）
<br/>
2. c++11的智能指针模板
* shared_ptr（共享式）: 
多个智能指针可以指向相同对象，
该对象和其相关资源会在“最后一个引用（reference）被销毁”时候释放。
* unique_ptr（独占式）:
同一时间内只有一个智能指针可以指向该对象。
它对于避免资源泄露（resourece leak）——例如“以new创建对象后因为发生异常而忘记调用delete”——特别有用。

	#include <iostream>
	#include <cstdio>
	#include <string>
	#include <vector>
	#include <memory>
	#include <cassert>
	using namespace std;
	
	shared_ptr<int> fun(shared_ptr<string> str) {
	    cout << *str << endl;
	    return shared_ptr<int>(new int(1));
	}
	
	class mydata {
	private:
	    int m_data;
	public:
	    mydata(int data):m_data(data) {};
	    ~mydata() {};
	    void show() {
	        cout << "data=" << m_data << endl;
	    }
	};
	
	
	int main() {
	    // shared_ptr
	    shared_ptr<string> pstr1(new string("hello"));
	    shared_ptr<int> pint(new int(100));
	
	    vector<shared_ptr<string>> vec;
	    vec.push_back(pstr1);
	
	    for(auto p : vec) {
	        cout << *p << endl;
	    }
	
	    cout << *fun(pstr1) << endl;
	
	    // 调用智能指针本身的类成员函数用'.',调用智能指针指向对象的方法用'->'
	    shared_ptr<mydata> pdata = make_shared<mydata>(100);
	    pdata.reset(new mydata(200));   // 指针重置，指向新的mydata实例
	    pdata->show(); 
	    shared_ptr<mydata> pdata2(new mydata(300));
	    pdata.swap(pdata2);   // 修改指向
	    pdata->show(); 
	    cout << pdata.use_count() << endl;  // pdata所指对象的引用计数
	
	
	    // unique_ptr
	    unique_ptr<mydata> up(new mydata(101));
	    mydata *pda = up.release();  // 返回一个指向被管理对象的指针，并释放所有权
	    pda->show();
	    assert (up.get() == nullptr);
	    // reset swap和上边类似
	
	    unique_ptr<int> pi = make_unique<int>(5);
	    cout << *pi << endl;
	
	    if (pi) {
	        cout << "before reset pi=" << *pi << endl;
	    } 
	    pi.reset();
	    if (pi) {  // false
	        cout << "after reset pi=" << *pi << endl;
	    } 
	
	    system("pause");
	    return 0;
	}