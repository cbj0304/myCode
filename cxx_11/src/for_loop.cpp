#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

void show(string& s) {cout << s << endl;}

int main(){
    vector<string> v {"hello", "you", "and", "me"};
    // 值拷贝（副本）
    for(string elem : v){
        cout << elem << " ";
    }

    // 引用（可以修改原值）
    for(string& elem1 : v){
        elem1 += "haha";
    }

    for(const string& elem2 : v){
        cout << elem2 << " ";
    }

    for_each(v.begin(), v.end(), show);
    
    system("pause");
    return 0;
}