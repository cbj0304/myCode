// 解决的问题：如果一种特定类型的问题发生的频率足够高，就可将该问题的各个实例表述为一个简单语言中的句子，
//             如果可将该语言中的句子表示为一个抽象语法树时，则可使用解释器模式。
//             构建一个解释器，该解释器通过解释这些句子来解决该问题。
// 不足：解释器模式为文法中的每一条规则至少定义了一个类，因此包含许多规则的文法可能难以管理和维护。
//       建议当文法非常复杂时，使用其他的技术如语法分析程序或编译器生成器来处理。


#include <iostream>
#include <map>
#include <stack>

using namespace std;

// 表达式抽象基类
class Expression {
public:
    virtual int interpreter(map<char, int> var)=0;
    virtual ~Expression(){}

};

//变量表达式
class VarExpression: public Expression {
    
    char key;
    
public:
    VarExpression(const char& key) {
        this->key = key;
    }
    
    int interpreter(map<char, int> var) {
        return var[key];
    }

};

//符号表达式
class SymbolExpression : public Expression {
    
    // 运算符左右两个参数
protected:
    Expression* left;
    Expression* right;
    
public:
    SymbolExpression( Expression* left,  Expression* right):
        left(left),right(right){
        
    }
};

//加法运算
class AddExpression : public SymbolExpression {
    
public:
    AddExpression(Expression* left, Expression* right):
        SymbolExpression(left,right){
        
    }
    int interpreter(map<char, int> var) {
        return left->interpreter(var) + right->interpreter(var);
    }
};

//减法运算
class SubExpression : public SymbolExpression {
    
public:
    SubExpression(Expression* left, Expression* right):
        SymbolExpression(left,right){
        
    }
    int interpreter(map<char, int> var) {
        return left->interpreter(var) - right->interpreter(var);
    }
    
};


// 语法分析
Expression*  analyse(string expStr) {
    
    stack<Expression*> expStack;
    Expression* left = NULL;
    Expression* right = NULL;
    for(int i=0; i<expStr.size(); i++)
    {
        switch(expStr[i])
        {
            case '+':
                // 加法运算
                left = expStack.top();
                right = new VarExpression(expStr[++i]);
                expStack.push(new AddExpression(left, right));
                cout << "add=" << expStr[i] << endl; 
                break;
            case '-':
                // 减法运算
                left = expStack.top();
                right = new VarExpression(expStr[++i]);
                expStack.push(new SubExpression(left, right));
                cout << "sub=" << expStr[i] << endl; 
                break;
            default:
                // 变量表达式
                cout << "var=" << expStr[i] << endl; 
                expStack.push(new VarExpression(expStr[i]));
        }
    }
   
    Expression* expression = expStack.top();

    return expression;
}

void release(Expression* expression){
    
    //释放表达式树的节点内存...
}

int main(int argc, const char * argv[]) {
    
    
    string expStr = "a+b-c+d-e";
    map<char, int> var;
    var.insert(make_pair('a',5));
    var.insert(make_pair('b',2));
    var.insert(make_pair('c',1));
    var.insert(make_pair('d',6));
    var.insert(make_pair('e',10));

    
    Expression* expression= analyse(expStr);
    
    int result=expression->interpreter(var);
    
    cout<<result<<endl;
    
    release(expression);
    
    return 0;
}

// 面向对象的方式解决简单的文法表示：
// 例如：
//     string s1="肆仟叁佰伍拾陆" 转换为数字
