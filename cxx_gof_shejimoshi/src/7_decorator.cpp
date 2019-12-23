#include <iostream>

using namespace std;

// 文件流、网络流、内存流 都继承自流基类  <- 抽象
// 加密、缓存 都是对流的修饰              <- 装饰
// 装饰模式以对客户端透明的方式扩展对象的功能，是继承关系的一个替代方案，比继承更灵活。动态给一个对象增加（撤销）功能。
// 实现：继承(is a) + 组合(has a)


//业务操作
class Stream{

public:
    virtual char Read(int number)=0;
    virtual void Seek(int position)=0;
    virtual void Write(char data)=0;
    
    virtual ~Stream(){}
};

//主体类
class FileStream: public Stream{
public:
    virtual char Read(int number){
        //读文件流
        cout << "File Read..." << endl;
    }
    virtual void Seek(int position){
        //定位文件流
        cout << "File Seek..." << endl;
    }
    virtual void Write(char data){
        //写文件流
        cout << "File Write..." << endl;
    }

};

class NetworkStream :public Stream{
public:
    virtual char Read(int number){
        //读网络流
    }
    virtual void Seek(int position){
        //定位网络流
    }
    virtual void Write(char data){
        //写网络流
    }
    
};

class MemoryStream :public Stream{
public:
    virtual char Read(int number){
        //读内存流
    }
    virtual void Seek(int position){
        //定位内存流
    }
    virtual void Write(char data){
        //写内存流
    }
    
};

//扩展操作

class DecoratorStream: public Stream{
protected:
    Stream* stream;//...
    
    DecoratorStream(Stream * stm):stream(stm){
    
    }
    
};

class CryptoStream: public DecoratorStream {
 
public:
    CryptoStream(Stream* stm):DecoratorStream(stm){
    
    }
    
    
    virtual char Read(int number){
       
        //额外的加密操作...
        cout << "Crypto Read..." << endl;
        stream->Read(number);//读文件流
    }
    virtual void Seek(int position){
        //额外的加密操作...
        cout << "Crypto Seek..." << endl;
        stream->Seek(position);//定位文件流
        //额外的加密操作...
    }
    virtual void Write(char data){
        //额外的加密操作...
        cout << "Crypto Write..." << endl;
        stream->Write(data);//写文件流
        //额外的加密操作...
    }
};



class BufferedStream : public DecoratorStream{
    
public:
    // 调用父类的构造函数
    BufferedStream(Stream* stm):DecoratorStream(stm){
        
    }
    virtual char Read(int number){
       
        //额外的加密操作...
        cout << "Buffered Read..." << endl;
        stream->Read(number);//读文件流
    }
    virtual void Seek(int position){
        //额外的加密操作...
        cout << "Buffered Seek..." << endl;
        stream->Seek(position);//定位文件流
        //额外的加密操作...
    }
    virtual void Write(char data){
        //额外的加密操作...
        cout << "Buffered Write..." << endl;
        stream->Write(data);//写文件流
        //额外的加密操作...
    }

};




int main(int argc, char* argv[]){
    // 运行时装配
    int num = 100;
    FileStream* s1=new FileStream();
    s1->Read(num);

    CryptoStream* s2=new CryptoStream(s1);
    s2->Read(num);

    BufferedStream* s3=new BufferedStream(s1);
    s3->Read(num);

    return 0;
}
