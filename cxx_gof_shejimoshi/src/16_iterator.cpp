// 迭代器模式：提供一种方法顺序访问一个聚合对象中各个元素，而又不需要暴露该对象的内部表示。

// 设计模式中的迭代器模式有点过时了，可以被stl中的迭代器取代
// stl中泛型编程（模板类 编译时绑定的方案）效率更高

#include <iostream>

using namespace std;

template<typename T>
class Iterator
{
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual T& current() = 0;
};



template<typename T>
class MyCollection{
    
public:
    
    Iterator<T> *GetIterator(){
        //...
    }
    
};

template<typename T>
class CollectionIterator : public Iterator<T>{
    MyCollection<T> mc;
public:
    
    CollectionIterator(const MyCollection<T> & c): mc(c){ }
    
    void first()  {
        
    }
    void next()  {
        
    }
    bool isDone() const {
        
    }
    T& current() {
        
    }
};

void MyAlgorithm()
{
    MyCollection<int> mc;
    
    Iterator<int> *iter = mc.GetIterator();
    
    for (iter->first(); !iter->isDone(); iter->next()){
        cout << iter->current() << endl;
    }
    
}

int main() {
    MyAlgorithm();
    return 0;
}
