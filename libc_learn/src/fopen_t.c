#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>

/*
主题：标准IO库文件操作。

头文件：
#include <stdio.h>
FILE *fopen(const char *path, const char *mode);

mode介绍：
"r"： 只读模式打开
"r+"： 读写模式打开
"w"： 只写模式打开，如果不存在会新建，如果有会内容清零
"w+"：读写模式打开，如果不存在会新建，如果有会内容清零
"a"： 追加模式只写
"a+"： 追加模式读写
"b"： 二进制文件打开，在Linux加不加此模式无区别

什么时候用fflush？
fflush即清空缓存，
如果给定的文件流是一个输出流（内存->磁盘文件），fflush把输出到缓冲区的内容写入文件；
如果给定的文件流是一个输入流（文件->内存），fflush会清空输入缓冲区。
几处应用：
(1) flush(stdin) 刷新标准输入缓冲区，把输入缓冲区里的东西丢弃。
    int main() {
        printf("input a char\n");
        char a = getchar();
        fflush(stdin);  // getchar之后，输入n，按下回车就会被getchar接收到并保存到a中
        char b = getchar(); // 但是回车键'\n'在缓冲区中会被b接收，fflush可以清空缓冲区中的'\n'
        fflush(stdin);
        printf("you have put a=%c, b=%c\n", a, b);
        system("pause");
    }
(2) fflush(stdout) 刷新标准输出缓冲区，把输出缓冲区里的东西打印到标准输出设备上。
    如程序在输出到屏幕前发生了错误，调用此函数可以保证任意时间把调试输出打印到屏幕。
(3) 一般fflush不应该在读取文件的时候用，而应该在写入文件时用。
    另外，fclose关闭文件时会清空缓冲区；
    exit、return退出程序时，所有打开文件都会自动关闭，文件关闭时会清空缓冲区。

流的分类：
全缓冲：在填满标准IO缓冲区后才进行实际的IO操作。
行缓冲：在输入输出中遇到换行符时，标准IO库执行IO操作。（说明：缓冲区满即使没有遇到换行符，也进行IO）
不带缓冲：直接系统调用，立即执行IO。
默认值：标准出错流默认是不带缓冲的；涉及终端设备的流默认是行缓冲的；否则是全缓冲的。
可以调用setbuf函数更改缓冲类型和缓冲区大小。
任何时候我们都可以调用fflush冲洗一个流，是未写数据都传送至内核。

多线程通过fwrite写一个文件可能会存在线程不安全的问题，解决办法：
1、 在打开文件时，加锁，fwrite之后fclose,并释放锁。
2、 修改文件打开的权限为fopen(fileName, "a+"),并在fwrite后使用fflush(fp)刷出流。

*/

int main() {
    const char *filename = "data\\fopen.txt";

    FILE *pFile;
    pFile = fopen(filename, "w+");   // 以读写方式打开，文件不存在则创建

    if (pFile == NULL) {
        printf("open failed, filename=%s\n", filename);
        exit(0);           // 打开文件错误退出程序
    }

    // ********************每次一个字符的I/O
    // fputc 成功返回写入的字符，失败返回-1(EOF)
    char ch = 'y';
    char rch1 = fputc(ch, pFile);
    if (rch1 == EOF) {
        printf("fputc failed\n");
        exit(0);
    }
    assert(rch1 == ch);

    // fgetc 成功返回读取的字符，失败返回-1(EOF)
    fseek(pFile, 0, SEEK_SET);
    char rch2 = fgetc(pFile);
    if (rch2 == EOF) {
        printf("fgetc failed\n");
        exit(0);
    }
    assert(rch2 == 'y');

    // ******************** 每次一行的I/O
    rewind(pFile);      // 功能等同于 fseek(pFile, 0, SEEK_SET);
    // fputs 一次写入一个字符串，遇到null就停止
    // 成功返回非负值，失败返回-1(EOF)
    char *buf = "I love China";
    if(fputs(buf, pFile) == EOF) {
        printf("fputs failed\n");
        exit(0);
    }

    rewind(pFile);
    // fgets 成功返回buf，失败或到达文件尾返回NULL
    char r_buf[100];
    char *r_buf2 = fgets(r_buf, 100, pFile);
    if (r_buf2 == NULL) {
        printf("fgets failed\n");
        exit(0);
    }
    assert(strcmp(r_buf2, r_buf) == 0);

    // ******************** 直接I/O（二进制IO）
    rewind(pFile);
    // fwrite/fread 返回度或者写的对象数量
    // 读写一个二进制数组
    float data[10] = {1.2, 3.4, 5.6, 6.6, 7.7, 8.8};
    size_t fw_cnt = fwrite(&data[2], sizeof(float), 3, pFile);     // 5.6, 6.6, 7.7
    assert(fw_cnt == 3);

    rewind(pFile);
    float rdata[10];
    size_t fr_cnt = fread(rdata, sizeof(float), 2, pFile);     // 读出来 5.6 6.6
    assert(fr_cnt == 2);
    assert(fabs(rdata[0] - 5.6) < 1e-6);         // 1e-6表示10的负6次幂，表示一个很小的数
    assert(fabs(rdata[1] - 6.6) < 1e-6);

    // 读写一个结构体
    rewind(pFile);
    struct Item
    {
        char name[20];
        short age;
    };
    struct Item item = {"Lily", 18};
    size_t n = fwrite(&item, sizeof(item), 1, pFile);
    assert(n == 1);      // 写入对象个数

    rewind(pFile);
    struct Item ritem;
    if (1 != fread(&ritem, sizeof(ritem), 1, pFile)) {
        printf("fread failed\n");
        // fread 读取的对象数量少于预期，如何判断是读到了文件尾部，还是出错了？
        // feof判断文件结束是通过读取函数fread/fscanf等返回错误来识别的，故而判断文件是否结束应该是在读取函数之后进行判断。
        if(feof(pFile)) {                          // 到了文件尾部
            printf("has reached end of file");
        } else if (ferror(pFile)) {                // 其他错误
            printf("fail to read file");           
        }
        exit(0);
    }
    printf("name=%s, age=%d\n", ritem.name, ritem.age);

    // 二进制IO存在的不兼容、不可跨平台的问题：
    // 对于同一个结构体，不同编译器和系统可能有不同的对齐规则
    // 对于多字节整数、浮点数，不同机器体系结构间也占不同字节数

    // 获取文件相关信息
    long fsize = ftell(pFile);
    if( -1 == fsize) {
        printf("ftell failed\n");
        exit(0);
    }
    assert(fsize == 22);                               // 22字节

    // fstat 获取文件指针的详情
    // 从文件指针FILE*中获取文件的描述符(句柄)，以文件句柄为参数进行系统调用
    int fd = fileno(pFile);
    struct stat file_stat;
    fstat(fd, &file_stat);
    unsigned short st_mode = file_stat.st_mode;// 文件的类型和存取的权限，按位解析
    long st_size = file_stat.st_size;          // 文件大小
    time_t st_atime = file_stat.st_atime;      // 访问时间
    time_t st_ctime = file_stat.st_ctime;      // 创建时间
    time_t st_mtime = file_stat.st_mtime;      // 修改时间
    printf("stat=> st_mode=%d, \nst_size=%ld, \nst_atime=%ld, \nst_ctime=%ld, \nst_mtime=%ld",
                st_mode, st_size, st_atime, st_ctime, st_mtime);

    fclose(pFile);

    system("pause");
    return 0;
}