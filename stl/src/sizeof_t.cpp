#include <iostream>
#include <cstdlib>

using namespace std;

/*
1. sizeof和strlen的区别：
（1）sizeof是运算符，strlen是函数。 
（2）strlen只能用char*做参数，且必须是以'\0'结尾的。->计算字符串首地址到\0之前的字节数。
（3）sizeof的本质是得到某个类型的大小，也就是当创建这个类型的一个对象（或变量）的时候，需要为它分配的空间的大小。
    char str[20]="0123456789";
    int a=strlen(str);  // a=10;
    int b=sizeof(str);  // b=20;

    short f();  // sizeof(f()) == sizeof(short)

2. 结构体计算占用字节大小：
    原则：结构体变量中每个成员的偏移量必须是成员大小的整数倍。（首元素偏移量是0）
*/

struct A {
        char c;
        static int i;
};

struct B  
{  
    float f;    //  偏移量是0，占4 byte
    char p;     //  偏移量>=4,这里取离4最近的sizeof(char)=1的整数倍->4， 占1 byte
    int adf[3]; // 偏移量>=5,这里取离5最近的sizeof(int)=4的整数倍->8，占12字节
                // 统计结果，占20个字节
};   

int main() {
    // ******************** 关于sizeof ************************
    // 基础数据（64位系统的测试）
    cout << "char=" << sizeof(char) << endl;       // char=1
    cout << "short=" << sizeof(short) << endl;     // short=2
    cout << "int=" << sizeof(int) << endl;         // int=4
    cout << "long=" << sizeof(long) << endl;       // long=4
    cout << "float=" << sizeof(float) << endl;     // float=4
    cout << "double=" << sizeof(double) << endl;   // double=8
    cout << "pointer=" << sizeof(int*) << endl;    // pointer=8

    // 类/结构体中的静态变量、堆空间new的变量都不会被sizeof统计
    // 原因：sizeof的本质是得到某个类型的大小，
    // 确切的来说就是当创建这个类型的一个对象（或变量）的时候，需要为它分配的空间的大小。
    // 实际上，在类中，sizeof只计算类内部栈空间的大小，
    // static是被分配在静态区供各实例共享的，实例化类对象时不需要再对其分配空间。
    // 堆空间是各种实例创建后各自通过程序员动态开辟的，也不计算在内，如stl各种容器。
    cout << "sizeof(A)=" << sizeof(A) << endl;      // sizeof(A)=1

    // static不在类中的时候，为static类型（static int等等）定义一个变量的时候，是必须要分配空间的。
    static int a;
    cout << "static int=" << sizeof(a) << endl;     // static int=4

    // ******************** 关于关于结构体/类的对齐 ************************
    cout << "sizeof(B)=" << sizeof(B) << endl;      // sizeof(B)=20

    system("pause");
    return 0;
}

