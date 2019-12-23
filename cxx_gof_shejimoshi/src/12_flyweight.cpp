#include <iostream>
#include <map>

using namespace std;

// 享元模式（轻量模式，轻量级细粒度对象）减少创建对象的数量,以减少内存占用和提高性能。
// 一篇文档中如果所有汉字都对应一个字体对象，那么一篇文档所要容纳的对象将是非常庞大且耗费内存的，
// 实际组成文档的字体是有限的，文档是由这些字体的排列组合得到的，因此将有限的字体集共享。 

class Font {
private:

    //unique object key
    string key;
    
    //object state
    //....
    
public:
    Font(const string& key){
        //...
    }
};

class FontFactory{
private:
    map<string,Font* > fontPool;
    
public:
    Font* GetFont(const string& key){

        map<string,Font*>::iterator it = fontPool.find(key);
        
        if(it != fontPool.end()){
            return fontPool[key];
        }
        else{
            Font* font = new Font(key);
            fontPool[key]= font;
            return font;
        }

    }
    
    void clear(){
        //...
    }
};

int main(int argc, char* argv[])
{
    return 0;
}
