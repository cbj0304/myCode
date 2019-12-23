#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/*
1. 创建并启动一个线程：
    int pthread_create(pthread_t *th, const pthread_attr_t *attr, 
                       void *(* func)(void *), void *arg);
    参数说明：
    线程id；
    线程属性指针，缺省为NULL;
    线程函数；
    线程函数的参数；

2. 结束线程
    void  pthread_exit(void *res);   // res存放线程结束时的退出状态

3. 等待指定线程结束
    说明：假设 A 线程调用 pthread_join 试图去操作B线程，
    该函数将A线程阻塞，直到B线程退出，当B线程退出以后，A线程会收集B线程的返回码。
    int pthread_join(pthread_t t, void **res);
    参数说明：
    t 要等待结束的线程id。
    res指向的位置存放的是终止线程的返回状态，缺省为NULL。

*/

int *threadFun(void* args) {
    int *index = (int *)args;
    for (int i = 0; i < 5; i++) {
        printf("tread=%d, put=%d\n", *index, i);
    }
    return NULL;
}

int main() {
    pthread_t pid1, pid2;
    printf("mian thread id = %d\n", pthread_self());

    int thread_1 = 100;
    int ret1 = pthread_create(&pid1, NULL, (void *)threadFun, (void *)&thread_1);
    int thread_2 = 200;
    int ret2 = pthread_create(&pid2, NULL, (void *)threadFun, (void *)&thread_2);

    if (ret1 != 0 || ret2 != 0) {
        printf("thread create failed\n");
        exit(0);
    }

    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);

    system("pause");
    return 0;
}