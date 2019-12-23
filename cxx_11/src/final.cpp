#include <iostream>
#include <cstdlib>

using namespace std;

/*
c++11 final 关键字：禁止继承和重写。
*/

// 例1：基类禁止被继承
// Error: a 'final' class type cannot be used as a base class
class Shape final {
    // ...
};

class Rectangle : public Shape {      // 异常（不能将final类类型作为基类）
    // ...
};

// 例2：虚函数禁止被重写(覆盖)
// Error： cannot override 'final' function "Shape1::Draw" (declared at line 23)
class Shape1 {
public:
    virtual void Draw() final {
        cout << "Shap1 Draw..." << endl;
    }
};

class Rectangle1 : public Shape1 {
public:
    void Draw() override {        // 异常（不能重写final类型的函数）
        cout << "Rectangle1 Draw..." << endl;
    }
};

int main(){
    system("pause");
    return 0;
}