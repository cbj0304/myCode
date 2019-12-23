#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
预备知识：
c/c++程序的内存分配：
    栈区： 由编译器自动分配释放，存放函数的参数值，局部变量的值等。
    堆区： 由程序员分配释放。malloc/free、new/delete
    静态存储区（全局区）：初始化全局变量和静态变量。
    初始化的全局变量和静态变量在一块区域，未初始化的全局变量和未初始化的静态变量在相邻的另一块区域。
    程序结束后由系统释放。
    文字常量区：如常量字符串就是放在这里的，程序结束后由系统释放。
    程序代码区

char*和char[]的区别:
    char *a1="hello world";
    char a2[]="123456789";

    a1是字符指针，指向的字符串存放在文字常量区，无法修改；赋值在编译时就确定了（常量区）。
    a2是字符数组，数组存放在栈中，可以被修改；赋值是在运行时确定的（栈区）。

*/

void test_memory() {
    int b;            // 栈
    char s[]="abc";   // 栈
    char *p2;         // 栈
    char *p3="123456";   // 123456\0在常量区，p3在栈上。
    static int c = 0;    // 全局（静态）初始化区
    p2 = (char*)malloc(20);   //分配得来得20字节的区域就在堆区。
    strcpy(p2,"123456");   //123456\0放在常量区，编译器可能会将它与p3所向"123456"优化成一个地方。
}

int main() {

    char *a1="000456789";
    char a2[20]="111456789";
    printf("a1=%s \na2=%s \n", a1, a2);
    printf("sizeof(a1)=%d  sizeof(a2)=%d \n", sizeof(a1), sizeof(a2));   // 8 20 这个类型需要开辟的空间
    printf("strlen(a1)=%d  strlen(a2)=%d \n", strlen(a1), strlen(a2));   // 9 9  字符串长度

    // a1[3] = 'm';        // Error 静态存储区(常量区) 不可更改
    a2[3] = 'm';
    printf("a1=%s \na2=%s \n", a1, a2);

    strcat(a2, a1);
    printf("a1=%s \na2=%s \n", a1, a2);       // a2 => 111m56789000456789

    // strcat(a1, a2);    // Error 静态存储区(常量区) 不可更改
    printf("a1=%s \na2=%s \n", a1, a2);      

    system("pause");
    return 0;
}