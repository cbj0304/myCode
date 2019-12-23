#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 将函数封装为对象，就能够以参数的形式将其传递给其他函数或者对象，告诉它们在旅行请求的过程中执行特定的操作。
// 可以用c++函数对象（重载()运算符）替代

class Command
{
public:
    virtual void execute() = 0;
};

class ConcreteCommand1 : public Command
{
    string arg;
public:
    ConcreteCommand1(const string & a) : arg(a) {}
    void execute()
    {
        cout<< "#1 process..."<<arg<<endl;
    }
};

class ConcreteCommand2 : public Command
{
    string arg;
public:
    ConcreteCommand2(const string & a) : arg(a) {}
    void execute()
    {
        cout<< "#2 process..."<<arg<<endl;
    }
};
      
class MacroCommand : public Command
{
    vector<Command*> commands;
public:
    void addCommand(Command *c) { commands.push_back(c); }
    void execute()
    {
        vector<Command*>::iterator it = commands.begin();
        for (;it != commands.end(); it++)
        {
            (*it)->execute();
        }
    }
};
       
int main()
{

    ConcreteCommand1 command1("Arg ###");
    ConcreteCommand2 command2("Arg $$$");
    
    MacroCommand macro;
    macro.addCommand(&command1);
    macro.addCommand(&command2);
    
    macro.execute();

    return 0;
}
