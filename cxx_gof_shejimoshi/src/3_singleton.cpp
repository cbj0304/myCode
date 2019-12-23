#include "3_singleton.h"
#include <pthread.h>
#include <cstdlib>

// 懒汉初始化
Singleton_ *Singleton_::single_ = NULL;

// 饿汉初始化
Singleton *Singleton::single = new Singleton();

void *threadFunc(void * arg){
    int* pnum = (int *)arg;
    Singleton::GetInstance()->print(*pnum);
    return (void *)0;
}

int main(int argc, char* argv[]) 
{
    pthread_t tids[5];
    int thread_data[5]={111, 222, 333, 444, 555};
    for(int i = 0; i < 5; ++i) {
        int ret = pthread_create(&tids[i], NULL, threadFunc, (void *)(&thread_data[i]));
        if(ret) {
            cout << "pthread err:" << i << endl;
            return -1;
        }
    }

    for (int j = 0; j < 5; ++j) {
        pthread_join(tids[j], NULL);
    }

    system("pause");
    return 0;
}
