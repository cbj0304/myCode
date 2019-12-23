#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/stat.h>

/*
主题：系统调用文件操作。
头文件： <fcntl.h>

特殊文件描述符：
标准输入0 (POSIX符号常量- STDIN_FILENO) 
标准输出1 (STDOUT_FILENO)
标准错误输出2 (STDERR_FILENO)

系统调用文件操作：
int open(const char *pathname, int flags, mode_t mode)
openflags：
    O_RDONLY
    O_WRONLY
    O_RDWR
    O_APPEND
    O_CREAT
    O_TRUNC
int creat(const char *pathname, mode_t mode);  -- 只写方式创建并打开新文件
int close(int fd)  -- 进程终止时，内核会自动关闭所创建的文件
off_t lseek(int fd, off_t offset, int whence)  -- 为打开的文件设置偏移量（空洞文件不占存储区）
ssize_t read(int fd，void* buf, size_t count)
实际读取的数据量(ssize_t)可能小于期望读取的数据量(count),比如：
1. 普通文件督导期望字节数之前已经到了文件尾部；
2. 从网络读取时，网络的缓冲机构可能造成返回值小于所要求的字节数。
ssize_t write(int fd, const void *buf, size_t count)

原子操作：
1. 追加写文件：使用open函数的O_APPEND选项
2. pread/pwrite
#include <unistd.h>
ssize_t pread(int fd, void *buf, size_t count, off_t offset);    -- 在offset位置开始读取count字节
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);   -- 在offset位置开始写入count字节

fsync和fflush的区别：
1. 源：fflush是C函数库(libc.a)中提供的方法，fsync是系统提供的系统调用。
2. 函数原型：fflush参数是FILE*文件指针, fsync参数是文件int描述符。
    int fflush(FILE *_File)
    int fsync(int fd);
3. 功能：
    fflush:是把C库中的缓冲（用户缓冲）调用write函数写到磁盘[其实是写到内核的缓冲区]。
    fsync：是把内核缓冲刷到磁盘上。

文件持久化到磁盘的顺序：
C库缓冲 -- fflush -- 内核缓冲区 -- fsync -- 磁盘


获取文件相关的信息：
int fstat(int fd, struct stat *buf);
int stat(const char *path, struct stat *buf);
int lstat(const char *path, struct stat *buf);
可以获取的信息如：文件的用户id、组id、文件类型、访问权限、
最后一次访问时间、修改时间、对文件io较合适的长度、为文件分配的512字节块的数量。

*/

int main() {

    const char *filename = "D:\\gcctool\\code\\libc_learn\\data\\open.txt";
    int fd = open(filename, O_RDWR|O_APPEND);      // 以读写、追加的方式打开,返回当前最小未用的文件描述符。

    if (fd < 0) {
        perror("open failed");
        exit(1);
    }

    // lseek用于显示的设置偏移量，成功返回新的文件偏移量，错误返回-1
    // 打开一个文件，如果未设置O_APPEND选项时，文件偏移量会被设置为0
    // SEEK_CUR->距当前值加offset, offset可正可负。SEEK_END->距文件尾加offset, offset可正可负。
    off_t start = lseek(fd, 0, SEEK_SET);              // 0
    off_t cur = lseek(fd, 12, SEEK_CUR);               // 12
    if ((start == -1 || cur == -1) && errno) {
        perror("leek error");
        exit(1);
    }

    // ssize_t write(int fd, void *buf, size_t nbytes);
    // 返回值通常与nbyte相同，否则表示出错。
    char *wbuf = "I am learning linux c";
    ssize_t w_cnt = write(fd, (void *)wbuf, strlen(wbuf));  // strlen是字符串的真实长度，sizeof会计算出char*的长度8
    assert(w_cnt == strlen(wbuf));

    // ssize_t read (int fd, void *buf, size_t nbytes);
    // read成功返回读到的字节数，如已到文件结尾，则返回0。
    if (lseek(fd, 0, SEEK_SET) != -1) {
        char buf[100];
        ssize_t r_cnt = read(fd, (void *)buf, 100);
        printf("count=%d, buf=%s", r_cnt, buf);
    } 

    // fstat 获取文件指针的详情
    struct stat file_stat;
    // fstat(fd, &file_stat);
    stat(".\\src\\fopen_t.c", &file_stat);
    unsigned short st_mode = file_stat.st_mode;// 文件的类型和存取的权限，按位解析
    long st_size = file_stat.st_size;          // 文件大小
    time_t st_atime = file_stat.st_atime;      // 最近一次被访问的时间(access)
    time_t st_mtime = file_stat.st_mtime;      // 文件内容上一次被修改的时间(modify)
    time_t st_ctime = file_stat.st_ctime;      // 文件属性(i节点状态)或者内容上一次被修改的时间（change)
    printf("stat=> st_mode=%d, \nst_size=%ld, \nst_atime=%ld, \nst_ctime=%ld, \nst_mtime=%ld \n",
            st_mode, st_size, st_atime, st_ctime, st_mtime);
    // 判断文件类型
    if (S_ISDIR(file_stat.st_mode)) {
        printf("it is a directory.\n");
    } else if (S_ISREG(file_stat.st_mode)) {
        printf("it is a regular file\n");
    } else {
        unsigned short mode = file_stat.st_mode;
        char s[10];
        itoa(mode, s, 2);  // 转为字符串，进制基数为2
        printf("unknown %s \n",  s);
    }

    close(fd);

    // 三个特殊的文件流指针
    // 文件句柄参数换成STDIN_FILENO、STDOUT_FILENO、STDERR_FILENO，可以对标准输入输出操作。

    system("pause");
    return 0;
}