#include "prototype.h"

class MainForm
{
    ISplitter*  prototype;//原型对象

public:
    
    MainForm(ISplitter* prototype){
        this->prototype=prototype;
    }
    
    void ButtonClick(){

        ISplitter * splitter=
            prototype->clone(); //克隆原型
        
        splitter->split();
    }
};

int main()
{
    ISplitter *is = new PictureSplitter();
    MainForm mf(is);

    mf.ButtonClick();

    delete is;
    return 0;
}
