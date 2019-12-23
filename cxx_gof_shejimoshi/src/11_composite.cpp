#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class Component
{
public:
    virtual void process() = 0;
    virtual ~Component(){}
};

// 树节点
// 继承 + 组合
// 继承 -- 是为了实现父类定义的接口规范，不继承生死（构造函数和析构函数）
// 组合 -- 是同时包含并处理多个Component 类型
class Composite : public Component{
    
    string name;
    list<Component*> elements;
public:
    Composite(const string & s) : name(s) {}
    
    void add(Component* element) {
        elements.push_back(element);
    }
    void remove(Component* element){
        list<Component*>::iterator it = find(elements.begin(), elements.end(), element);
        if (it != elements.end()) {
            elements.erase(it);
        }
    }
    
    void process(){
        
        //1. process current node
        
        //2. process leaf nodes
        cout << "composite process... name=>" << name << endl;  
        list<Component*>::iterator it = elements.begin();
        for (;it != elements.end();it++) {
            (*it)->process(); //多态调用
        } 
    }
};

//叶子节点
class Leaf : public Component{
    string name;
public:
    Leaf(string s) : name(s) {}
            
    void process(){
        //process current node
        cout << "leaf process name=>" << name << endl;
    }
};


void Invoke(Component & c){
    //...
    c.process();
    //...
};


int main()
{

    Composite root("root");
    Composite treeNode1("treeNode1");
    Composite treeNode2("treeNode2");
    Composite treeNode3("treeNode3");
    Composite treeNode4("treeNode4");
    Leaf leaf1("left1");
    Leaf leaf2("left2");
    Leaf leaf3("left3");
    
    root.add(&treeNode1);
    treeNode1.add(&treeNode2);
    treeNode2.add(&leaf1);
    
    root.add(&treeNode3);
    treeNode3.add(&treeNode4);
    treeNode4.add(&leaf2);
    treeNode4.add(&leaf3);

    // root -----treeNode1---treeNode2---leaf1
    //      |
    //      | ---treeNode3---treeNode4---leaf2
    //                             |
    //                             |-----leaf3
    Invoke(root);
    Invoke(leaf2);
    Invoke(treeNode3);

    return 0;
  
}
