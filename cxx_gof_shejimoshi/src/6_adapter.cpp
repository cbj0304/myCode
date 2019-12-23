#include <iostream>
using namespace std;

//目标接口（新接口）
class ITarget{
public:
    virtual void process()=0;
};

//遗留接口（老接口）
class IAdaptee{
public:
    virtual void foo(int data)=0;
    virtual int bar()=0;
};

//遗留类型
class OldClass: public IAdaptee{
    virtual void foo(int data) { 
        cout << "old foo.. data="  << data << endl;
    }

    virtual int bar() {
        cout << "old bar..." << endl;
        return 10;
    }
};

//对象适配器(继承自ITarget，就要实现ITarget的接口规范)
class Adapter: public ITarget{ //继承
protected:
    IAdaptee* pAdaptee;//组合
    
public:
    
    Adapter(IAdaptee* pAdaptee){
        this->pAdaptee=pAdaptee;
    }
    
    virtual void process(){
        int data=pAdaptee->bar();
        pAdaptee->foo(data);
        
    }
};


int main(){
    IAdaptee* pAdaptee=new OldClass();
    
    ITarget* pTarget=new Adapter(pAdaptee);
    pTarget->process();
}
