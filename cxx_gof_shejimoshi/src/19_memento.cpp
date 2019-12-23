// 备忘录模式：备忘录对象是一个用来存储另外一个对象内部状态的快照的对象。
// 备忘录模式的用意是在不破坏封装的条件下，将一个对象的状态捉住，并外部化，存储起来，
// 从而可以在将来合适的时候把这个对象还原到存储起来的状态。
#include <iostream>
#include <string>
using namespace std;

class Memento
{
    string state;
    //..
public:
    Memento(const string & s) : state(s) {}
    string getState() const { return state; }
    void setState(const string & s) { state = s; }
};

class Originator
{
    string state;
    //....
public:
    Originator() {}

    
    Memento createMomento() {
        Memento m(state);
        return m;
    }

    void setMomento(const Memento & m) {
        state = m.getState();
    }
};



int main()
{
    Originator orginator;
    
    //捕获对象状态，存储到备忘录
    Memento mem = orginator.createMomento();
    
    //... 改变orginator状态
    //从备忘录中恢复
    orginator.setMomento(mem);
}
