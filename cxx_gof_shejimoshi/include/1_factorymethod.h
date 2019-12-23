#include <iostream>
#include <cstdlib>

using namespace std;

//=============================抽象基类
class ISplitter{
public:
    virtual void split()=0;
    // 抽象基类必须自定义抽象的析构函数
    virtual ~ISplitter(){}
};

//=============================抽象工厂基类
class SplitterFactory{
public:
    virtual ISplitter* CreateSplitter()=0;
    virtual ~SplitterFactory(){}
};

//=============================具体类
// 二进制文件分割器
class BinarySplitter : public ISplitter{
   void split() { cout << "BinarySplitter..." << endl; } 
};

// 文本文件分割器
class TxtSplitter: public ISplitter{
   void split() { cout << "TxtSplitter..." << endl; } 
};

// 图片分割器
class PictureSplitter: public ISplitter{
   void split() { cout << "PictureSplitter..." << endl; } 
};

class VideoSplitter: public ISplitter{
   void split() { cout << "VideoSplitter..." << endl; } 
};

//=============================具体工厂方法
class BinarySplitterFactory: public SplitterFactory{
public:
    virtual ISplitter* CreateSplitter(){
        return new BinarySplitter();
    }
};

class TxtSplitterFactory: public SplitterFactory{
public:
    virtual ISplitter* CreateSplitter(){
        return new TxtSplitter();
    }
};

class PictureSplitterFactory: public SplitterFactory{
public:
    virtual ISplitter* CreateSplitter(){
        return new PictureSplitter();
    }
};

class VideoSplitterFactory: public SplitterFactory{
public:
    virtual ISplitter* CreateSplitter(){
        return new VideoSplitter();
    }
};

