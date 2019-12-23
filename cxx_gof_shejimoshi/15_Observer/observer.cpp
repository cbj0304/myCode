// 观察者模式：观察者模式定义了一种一队多的依赖关系，让多个观察者对象同时监听某一个主题对象。这个主题对象在状态上发生 变化时，会通知所有观察者对象，使他们能够自动更新自己。

#include <iostream>
#include <list>

using namespace std;

// 抽象接口（进度条）
class IProgress {
public:
    virtual void DoProgress(float value)=0;
    virtual ~IProgress(){}
};

// 文件分割器，文件分隔完毕后通知所有进度条更新其状态
class FileSplitter
{
    string m_filePath;
    int m_fileNumber;

    list<IProgress*>  m_iprogressList; // 抽象通知机制，支持多个观察者
    
public:
    FileSplitter(const string& filePath, int fileNumber) :
        m_filePath(filePath), 
        m_fileNumber(fileNumber){

    }

    void split(){

        //1.读取大文件

        //2.分批次向小文件中写入
        for (int i = 0; i < m_fileNumber; i++){
            //...

            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;
            onProgress(progressValue);//发送通知
        }

    }


    void addIProgress(IProgress* iprogress){
        m_iprogressList.push_back(iprogress);
    }

    void removeIProgress(IProgress* iprogress){
        m_iprogressList.remove(iprogress);
    }


protected:
    virtual void onProgress(float value){
        
        list<IProgress*>::iterator itor=m_iprogressList.begin();

        while (itor != m_iprogressList.end() ) {
            (*itor)->DoProgress(value); //更新进度条
            itor++;
        }
    }
};
