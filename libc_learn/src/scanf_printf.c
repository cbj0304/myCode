#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
格式化I/O
头文件：<stdio.h>

int scanf(const char *format, ...);      // 从标准输入接收的字符串，格式化到指定变量中
int printf (const char *format, ...);    // 格式化打印到标准输出


int fscanf(FILE *stream, const char *format, ...)    // 从文件中读取的字符串格式化到指定变量中
int fprintf (FILE *stream, const char *format, ...)  // 格式化打印到文件   

int sscanf(const char *source, const char *format, ...)           // 字符串格式化到指定变量中
int sprintf (char *stream, const char *format, ...)               // 格式化打印到字符串
int snprintf (char *stream, size_t n, const char *format, ...)    // 格式化打印到字符串，指定截断长度

int printf(const char * format，...);                            // 格式化到标准输出
int sprintf(char *str, const char *format，...); 
int snprintf(char *str, size_t size, const char *format, ...);   // 格式化到字符串
int fprintf(FILE *fptr, const char *format, ...);                // 格式化到文件

说明：
*printf版本：成功返回存入字符串的字符数，失败则返回负数。
*scanf版本：成功返回指定的输入项数，失败返回EOF

int i=43;    
printf("%d\n", printf("%d\n", printf("%d\n",i)));
        2\n            3\n    43\n -- 3个字符
输出：
43
3
2 

*/

void test_scanf_printf() {
    char name[10];
    char ch;
    int age;

    // scanf 通过标准输入(键盘)格式化到指定变量
    // 键盘输入> name=zs age=18 flag=y
    scanf("name=%s age=%d flag=%c", name, &age, &ch);
    //printf 格式化打印到标准输出(终端)
    printf("you have input=>name=%s, age=%d, flag=%c\n", name, age, ch);
}

void test_fscanf_fprintf() {

    FILE *fp;
    char* fileName="D:\\gcctool\\code\\libc_learn\\data\\scanf.txt"; 
    fp = fopen(fileName, "w+");
    if (fp == NULL) {
        perror("fopen failed");       // 打印errno报错详情
        exit(0);
    }

    // fprintf 格式化打印到文件中
    int size1 = fprintf(fp, "%s %d\n", "zs", 100);
    int size2 = fprintf(fp, "%s %d\n", "ls", 200);
    int size3 = fprintf(fp, "%s %d\n", "ww", 300);
    assert(size1 == 7 && size2 == 7 && size3 == 7);   // 返回写入的字节数

    // fscanf 从文件中读取的字符串格式化到n个变量
    fseek(fp, 0, SEEK_SET);
    char name[10];
    int age;
    while(!feof(fp)) {
        fscanf(fp, "%s %d", name, &age);   // 格式化到变量
        printf("<%s %d>\n", name, age);    // 输出到终端
    }

    fclose(fp);
}

void test_sscanf_sprintf() {
    char name1[20] = "Lily";
    char name2[20] = "Lucy";
    int  age = 18;

    // sprintf 格式化打印到字符串
    char res[100];
    int cnt1 = sprintf(res, "name=%s age=%d", name1, age);        // 应用1：格式化数据
    // name=Lily age=18
    assert(cnt1==16);
    assert(strcmp(res, "name=Lily age=18") == 0);

    int cnt2 = sprintf(res, "%s%s", name1, name2);                 // 应用2：字符串拼接
    // LilyLucy
    assert(cnt2 == 8);
    assert(strcmp(res, "LilyLucy") == 0);

    // snprintf 格式化打印到字符串，并指定截断长度
    char nres[100];
    int n1 = snprintf(nres, 5, "%s", "hello12345678");
    printf("cnt=%d res=%s\n", n1, nres);        // cnt=-1, hello
    int n2 = snprintf(nres, 50, "%s", "hello12345678");
    printf("cnt=%d res=%s\n", n2, nres);        // cnt=13, hello

    // sscanf 字符串格式化到n个变量
    int y, m, d, H, M;
    sscanf("2019-10-10 12:45", "%d-%d-%d %d:%d", &y, &m, &d, &H, &M);
    assert(y == 2019 && m == 10 && d == 10 && H == 12 && M == 45);
}


int main() {

    printf("************ test scanf/printf *************\n");
    test_scanf_printf();

    printf("************ test fscanf/fprintf *************\n");
    test_fscanf_fprintf();

    printf("************ test sscanf/snprintf/sprintf *************\n");
    test_sscanf_sprintf();

    system("pause");
    return 0;
}