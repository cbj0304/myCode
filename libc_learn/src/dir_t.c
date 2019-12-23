#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {

    // DIR* opendir (const char*);
    DIR * dir = opendir(".");         // 打开目录文件，成功返回指针，出错返回NULL
    // struct dirent* readdir (DIR*);   
    struct dirent* ptr;
    // 循环读取目录中所有子目录和文件，成功返回指针，到目录结尾或者出错返回NULL
    while ((ptr = readdir(dir)) != NULL) {
        printf("dirname: %s\n", ptr->d_name);  
    }
    closedir(dir);
    
    system("pause");
}