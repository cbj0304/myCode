#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#include<stdio.h>

标准输入输出流--字符、字符串操作
    int getc(FILE *stream);
    int getchar(void);                     // 等价于 getc(stdin)
    int ungetc(int c, FILE *stream);       // 将字符压回流中，成功返回c，失败返回EOF
    char* gets(char *buf);

    int putc(int c, FILE *stream);
    int putchar(int c);                   // 成功返回c，失败返回EOF
    int puts(const char *s);

文件--字符、字符串操作
    int fgetc(FILE *stream);
    char* fgets(char *buf, int size, FILE *stream);      // 成功返回buf，失败返回NULL

    int fputc(int c, FILE *stream);
    int fputs(const char *s, FILE *stream);         // 成功返回非负数，失败返回EOF
*/

int main() {

    // ************************* getchar/putchar 标准输入输出，字符IO
    printf("getchar/putchar: Enter 2 char\n");

    char c1 = getchar();
    fflush(stdin);         // 冲洗掉缓冲区中的换行符
    char c2 = getchar();
    fflush(stdin);         // 冲洗掉缓冲区中的换行符

    if (c1 != EOF) { putchar(c1);  putchar('\n'); }
    if (c2 != EOF) { putchar(c2);  putchar('\n'); }

    // ************************* fgetc/fputc 文件，字符IO
    printf("\n\n\nfgetc/fputc: \n");

    FILE *fp = fopen(".\\data\\stdio.txt", "w+");
    fseek(fp, 0, SEEK_SET);
    char charset[] = "testfgetcfputc";
    for (char *p = charset; *p != '\0'; p++) {
        fputc(*p, fp);
    }

    fseek(fp, 0, SEEK_SET);
    char c;
    while((c = fgetc(fp)) != EOF) {
        printf("%c ", c);
    }

    // ************************* gets/puts 标准输入输出，行IO
    printf("\n\n\ngets/puts: \n");

    char sbuf[100];
    gets(sbuf); 

    char sbuf2[200] = "testgetsputs";
    strcat(sbuf2, sbuf);
    // sprintf(sbuf2, "%s%s", sbuf2, sbuf);
    puts(sbuf2);

    // ************************* fgets/fputs 文件，行IO
    printf("\n\n\nfgets/fputs: \n");
    fseek(fp, 0, SEEK_SET);
    char buf[100] = "testfgetsfputs";       
    fputs(buf, fp);           // 遇到换行符、行缓冲区满、或者字符串结束标识'\0'，则写入结束

    fseek(fp, 0, SEEK_SET);
    char buf2[100];
    fgets(buf2, 100, fp);
    puts(buf2);             // 读取的数据不超过100， 遇到换行符号或者文件结束标识EOF(-1)，则读取结束。
    system("pause");    
    return 0;
}