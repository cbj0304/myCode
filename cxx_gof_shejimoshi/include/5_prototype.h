#include <iostream>
using namespace std;

//抽象类
class ISplitter{
public:
    virtual void split()=0;
    virtual ISplitter* clone()=0; //通过克隆自己来创建对象
    
    virtual ~ISplitter(){}

};

//具体类
class BinarySplitter : public ISplitter{
public:
    virtual ISplitter* clone(){
        cout << "BinarySplitter clone..." << endl;
        return new BinarySplitter(*this);
    }

    virtual void split() {
        cout << "BinarySplitter split..." << endl;
    }
};

class TxtSplitter: public ISplitter{
public:
    virtual ISplitter* clone(){
        cout << "TxtSplitter clone..." << endl;
        return new TxtSplitter(*this);
    }

    virtual void split() {
        cout << "TxtSplitter split..." << endl;
    }
};

class PictureSplitter: public ISplitter{
public:
    virtual ISplitter* clone(){
        cout << "PictureSplitter clone..." << endl;
        return new PictureSplitter(*this);
    }

    virtual void split() {
        cout << "PictureSplitter split..." << endl;
    }
};
