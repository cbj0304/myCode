#include <iostream>

using namespace std;

// 基类
class House {
    //....
};

// 基类builder
class HouseBuilder {
public:
    House* GetResult() {
        return pHouse;
    }
    virtual ~HouseBuilder(){}
    
    House* pHouse;
    virtual void BuildPart1()=0;
    virtual void BuildPart2()=0;
    virtual bool BuildPart3()=0;
    virtual void BuildPart4()=0;
    virtual void BuildPart5()=0;
    
};

// 具体类
class StoneHouse: public House{
    
};

// 具体类的builder
class StoneHouseBuilder: public HouseBuilder{
public:
    
    virtual void BuildPart1(){
        cout << "StoneHouseBuilder BuildPart1..." << endl;
    }
    virtual void BuildPart2(){
        cout << "StoneHouseBuilder BuildPart2..." << endl;
    }
    virtual bool BuildPart3(){
        cout << "StoneHouseBuilder BuildPart3..." << endl;
        return true;
    }
    virtual void BuildPart4(){
        cout << "StoneHouseBuilder BuildPart4..." << endl;
    }
    virtual void BuildPart5(){
        cout << "StoneHouseBuilder BuildPart5..." << endl;
    }
    
};


class HouseDirector{
    
public:
    HouseBuilder* pHouseBuilder;
    
    HouseDirector(HouseBuilder* pHouseBuilder){
        this->pHouseBuilder=pHouseBuilder;
    }
    
    House* Construct(){
        
        pHouseBuilder->BuildPart1();
        
        for (int i = 0; i < 4; i++){
            pHouseBuilder->BuildPart2();
        }
        
        bool flag=pHouseBuilder->BuildPart3();
        
        if(flag){
            pHouseBuilder->BuildPart4();
        }
        
        pHouseBuilder->BuildPart5();
        
        return pHouseBuilder->GetResult();
    }
};


int main() 
{
    HouseBuilder* pHB = new StoneHouseBuilder();
    HouseDirector hd(pHB);
    hd.Construct();

    // 释放堆内存
    if (pHB) {
        delete pHB;
    }
    return true;
}
