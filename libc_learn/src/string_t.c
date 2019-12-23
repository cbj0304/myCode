#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
strcpy_s是strcpy的安全版本：
举例说明：
char buf[2];
strcpy(buf, "1234567"):
以buf为起点的*(buf+3)也就是buf[3]被写入值, 
但是, 此时也许这个buf+3这个位置被其它的程序或变量使用时, 则会改变其它变量的值。

strcpy_s(buf,2,"1234567")：
告诉程序它只有两个字节, 此时, 程序不会将数据写入到 buf+3的地址中, 所以它更安全。

字符串基本操作：
拷贝
strcpy_s
strncpy
strncpy_s
memcpy
memmove

拼接
strcat

比较
strcmp(memcmp)
stricmp
strncmp

查找
strchr(memchr)
strrchr
strstr

赋值(初始化)
memset

计算长度
strlen(不包括\0在内)

类型转换
atoi
atof
atol
*/

int main() {

    {
        char str1[] = "123456789";
        char str2[] = "hello";
        // 字符串拷贝，先清空 str1，再拷贝
        // 注意：strlen(s)计算的长度不包括\0， 这里需要+1
        strcpy_s(str1, strlen(str2)+1, str2);       // assert(strcmp(str1, "hello") == 0);
        
    }
    {
        char str1[] = "123456789";
        char str2[] = "hello";
        // 拷贝前n个
        strncpy(str1, str2, 2);   // assert(strcmp(str1, "he3456789") == 0);
        memcpy(str1, str2, 4);    // *** mem版本  assert(strcmp(str1, "hell56789") == 0);
        // 目标区域和源区域有重叠的话memmove比以上版本更安全，
        // 它能够保证源串在被覆盖之前将重叠区域的字节拷贝到目标区域中。
        memmove(str1, str2, 5);   // *** mem版本  assert(strcmp(str1, "hello6789") == 0);
        
    }   
    {
        char str1[] = "123456789";
        char str2[] = "hello";
        // 先清空再拷贝
        // 第二个参数是目标缓冲区的大小，防止dest中空间不够
        strncpy_s(str1, strlen(str1)+1, str2, 4);       // assert(strcmp(str1, "hell") == 0);    
    } 
    {
        char str1[20] = "123456789";
        char str2[] = "hello";
        // 字符串拼接 
        // 拼接后的长度不大于str1的长度
        strcat(str1, str2);    //  assert(strcmp(str1, "123456789hello") == 0);
    }
    {
        char str1[20] = "123456789";
        char str2[] = "hello";
        // 字符串拼接，拼接前n个
        strncat(str1, str2, 2);     // assert(strcmp(str1, "123456789he") == 0);   
    }
    {
        char str1[] = "heLLO";
        char str2[] = "hello";
        // 字符串比较
        int ret = strcmp(str1, str2);
        if (ret == 0) {
            printf("str1=str2");
        } else if (ret > 0) {
            printf("str1 > str2");
        } else {
            printf("str1 < str2");
        }

        // 比较前n个
        assert(strncmp(str1, str2, 2) == 0);
        assert(memcmp(str1, str2, 2) == 0);    //  *** mem版本

        // 忽略大小写
        assert(stricmp(str1, str2) == 0);
    }
    {
        char str[] = "Lucy like china";
        // 查找首次出现字符i的位置
        char *p = strchr(str, 'i');       // assert(strcmp(p, "ike china") == 0);
        //  *** mem版本 在前10个字符中找字符首次出现的位置
        char *mp = memchr(str, 'i', 10);   // assert(strcmp(mp, "ike china") == 0);
        
        // 反向查找
        char *rp = strrchr(str, 'i');      // assert(strcmp(rp, "ina") == 0);
        
        // 查找子串"chi"出现的位置
        char *ps = strstr(str, "chi");     // assert(strcmp(ps, "china") == 0);
    }
    {
        char str[10];
        // 赋值n个字符c到str指向的位置 mem版本不仅限于字符串处理
        // void *memset(void *str, int c, size_t n) 
        memset(str, 0, sizeof(str));  // 初始化
    }
    {
        // 类型转换
        char str[] = "12.34";
        int i = atoi(str);          // 12
        double d = atof(str);       // 12.340000
        long l = atol(str);         // 12
    }

    system("pause");
    return 0;
}