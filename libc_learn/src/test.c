#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    printf("input a char\n");
    char a = getchar();
    fflush(stdin);  // getchar之后，输入n，按下回车就会被getchar接收到并保存到a中
    char b = getchar(); // 但是回车键'\n'在缓冲区中会被b接收，fflush可以清空缓冲区中的'\n'
    fflush(stdin);
    printf("you have put a=%c, b=%c\n", a, b);

    // DIR* opendir (const char*);
    DIR * dir = opendir(".");
    // struct dirent* readdir (DIR*);
    struct dirent* ptr;
    while ((ptr = readdir(dir)) != NULL) {
        printf("dirname: %s\n", ptr->d_name);
    }
    closedir(dir);
    
    system("pause");
}