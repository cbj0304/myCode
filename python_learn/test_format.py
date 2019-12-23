# -*- coding=utf-8 -*-

a = 100
b = 88.0932
c = ["hello", "words"]
d = {"name": "zz", "age": 18}
e = 'hello world'

# 通过位置格式化
print('score1={}, score2={}'.format(a, b))
print('{0}, age={1}, default={1}'.format(d['name'], d['age']))

# 通过关键字映射
print('n={name}, s={score}'.format(name=d['name'], score=b))


# 通过对象属性
class Person(object):
    def __init__(self, Name, Age):
        self.name = Name
        self.age = Age

    def __str__(self):
        # return('name={}, age={}'.format(self.name, self.age))  # 这样也可以
        return('name={self.name}, age={self.age}'.format(self=self))


p = Person("cbj", "20")
print(str(p))

# 填充与对齐
'''
填充常跟对齐一起使用
^、<、>分别是居中、左对齐、右对齐，后面带宽度
:号后面带填充的字符，只能是一个字符，不指定的话默认是用空格填充
'''
print('{:*>10}'.format(b))


# 精度和类型f
print('{:.2f}'.format(b))

# 进制格式转换
'''
b 二进制
d 十进制
o 八进制
x 十六进制
'''
print('{:b}'.format(a))
print('{:d}'.format(a))
print('{:o}'.format(a))
print('{:x}'.format(a))
