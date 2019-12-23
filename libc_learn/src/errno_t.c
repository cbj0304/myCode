#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <error.h>
#include <string.h>

/*
errno: 保留最后一次调用c方法的错误代码。

#include <stdio.h>
void perror(const char *s);
参数s是用户提供的字符串，输出这个字符串，后面跟着一个冒号和空格，然后是基于当前errno的值进行的错误类型描述。

#include <string.h>
char * strerror(int errnum);
这个函数将errno的值作为参数，并返回一个描述错误的字符串

*/

int main() {

    errno = 0;       // 任何一个函数都不会将error置为0
    int s = sqrt(-1);
    if(errno) {
        printf("error num=%d\n", errno);                // error num=33
        perror("sqrt failed");                          // sqrt failed: Domain error
        printf("stderr(errno)=%s\n", strerror(errno));  // stderr(errno)=Domain error
    }

    system("pause");
    return 0;
}