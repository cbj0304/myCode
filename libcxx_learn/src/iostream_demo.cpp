#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <bitset>
#include <fstream>
#include <string>

using namespace std;

/*
主题：c++ IO
c++的IO是围绕流对象进行的
头文件
#include <ostream>
#include <istream>
#include <iostream>
#inlcude <ifstream>
#include <ofstream>
#include <fstream>

标准输入输出流对象：
cin
cout
cerr

创建文件流对象：
fstream f("a.txt", ios::in | ios::out);
或者
ofstream fout;
fout.open("a.txt", ios::out);

定义文件流对象时，打开方式如下：
ios::in      : 以输入方式打开文件流
ios::out     ：输出
ios::app     ： 追加
ios::binary  ： 二进制

文件流对象输入输出方式：
1. 通过流插入和提取运算符： <<  >>
2. 通过成员函数： put/get/getline等
*/

class Student
{
private:
    string _name;
    int _age;
public:
    Student(string name="", int age=-1):_name(name), _age(age) {}
    void show() {
        cout << "<name=" << this->_name << ", age=" << this->_age << ">" << endl;  
    }
};

int main()
{
    // ****************cin 标准输入流对象，和终端关联
    char ch1 = cin.get();
    cout << "get a char from stdin stream: " << ch1 << endl;
    cin.putback(ch1);            // 把ch1放回到输入流
    if (cin.peek() == ch1) {     // 查看下一个输入流中的字符，不移除流
        cout << "char in stdin stream = ch1" << endl;
    }
    cin.ignore(5);               // 忽略掉5个字符
    char str[11];
    cin.getline(str, 11);       // 读取剩余的字符
    cout << "str left is: "<< str << endl;

    // ********************cout 标准输出流对象，和终端关联
    char ss[10] = "12345";
    cout.put('a');                  // 向标准输出打印一个字符
    cout.write(ss, strlen(ss));     // 向标准输出打印一个字符串
    cout.flush();                   // 清空缓冲
    
    // 宽度是10，左对齐，x补齐
    cout << setw(10) << setfill('x') << setiosflags(ios::left) << "abcd" << endl;

    // 宽度是10，定点方式表示实数，保留3位小数
    cout << setw(10) << setiosflags(ios::fixed) << setprecision(3) << setfill(' ') << "12.345215" << endl; 

    int data = 15;
    cout << hex << data << endl;                   // 十六进制大写
    cout << oct << data << endl;                   // 八进制
    cout << bitset<sizeof(int)*8>(data)  << endl;  // 二进制

    // *******************fstream
    fstream f1("src\\file1.txt", ios::in | ios::out);    // 以可读可写的方式打开文件流f1
    if (!f1) {
        perror("open f1 failed");
        system("pause");
        return -1;
    }
    if (f1) {
        f1.put('a');
        f1.put('\n');              // 写入一个字符

        f1.flush();                // 冲洗输入流

        f1 << "hello world" << endl;  // 写入字符串

        f1.close();
    }

    ifstream fin;
    fin.open("src\\filein.txt", ios::in);   // 以读的方式打开输入流
    if (fin) {
        char ch = fin.get();                // 读一个字符
        cout << "get=" << ch << endl;

        char str[100];
        fin.getline(str, sizeof(str));      // 读一行字符串
        cout << "getline" << str << endl;

        while(!fin.eof()) {                 // 环循读取各行，直到结尾
            memset(str, 0, sizeof(str));
            fin >> str;
            cout << "str=" << str << endl;    
        }
        fin.close(); 
    }

    // **********************二进制文件读写
    Student s1("zhangsan", 18);
    Student s2("lisi", 20);

    fstream fbi("src\\fbi.txt", ios::in | ios::out | ios::binary);
    if (!fbi) {
        perror("open fbi failed:");
        system("pause");
        return -1;
    }
    fbi.seekp(ios::beg);      // 设置输出文件流的指针
    fbi.write((char *)&s1, sizeof(Student));
    fbi.write((char *)&s2, sizeof(Student));
    fbi.flush();

    fbi.seekg(0, ios::beg);     // 设置输入文件流的指针
    Student *stmp = new Student();
    while (!fbi.eof()) {   
        fbi.read((char *)stmp, sizeof(Student));
        fbi.flush();
        stmp->show();
    }
    fbi.close();

    system("pause");
    return 0;
}