#include "1_factorymethod.h"

class MainForm
{
    SplitterFactory*  factory;//工厂

public:
    
    MainForm(SplitterFactory*  factory){
        this->factory=factory;
    }
    
    void ButtonClick(){
        
        ISplitter * splitter=
            factory->CreateSplitter(); //多态new
        
        splitter->split();

    }
};

int main()
{

    MainForm m1(new PictureSplitterFactory());
    m1.ButtonClick();

    MainForm m2(new TxtSplitterFactory());
    m2.ButtonClick();

    // TODO 考虑堆资源释放 delete
    system("pause");
    return 0;
}
