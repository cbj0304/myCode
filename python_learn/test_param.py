# -*- coding: utf-8 -*-

'''
python中的*和**
（1）用在参数(实参、形参)前边：
     * 会把接收到的参数存入一个元组 （另一种描述：表示函数能接受任意数量的位置参数）
     ** 会把接收到的参数存入一个字典（另一种描述：表示函数能接受任意数量的关键字参数）
（2）用作运算符号
     * 乘法
     ** 平方
'''


def pringParam(x, *y, **z):
    print('x={}, type(x)={}'.format(x, type(x)))
    print('y={}, type(y)={}'.format(y, type(y)))
    print('z={}, type(z)={}'.format(z, type(z)))


if __name__ == "__main__":
    # 普通变量、列表、字典 同时传
    pringParam(3, 4, name='cbj', age=20)
    '''
    输出：
    x=3, type(x)=<class 'int'>
    y=(4,), type(y)=<class 'tuple'>
    z={'name': 'cbj', 'age': 20}, type(z)=<class 'dict'>
    '''

    pringParam(3, 1, 3, 4)
    '''
    输出：
    x=3, type(x)=<class 'int'>
    y=(1, 3, 4), type(y)=<class 'tuple'>
    z={}, type(z)=<class 'dict'>
    '''

    a1 = 123
    a2 = [1, 2, 3, 4, 5]
    a3 = {'name': 'alam', 'age': 12}
    pringParam(a1, a2, a3)
    '''
    输出：
    a1 a2 a3都被看作普通变量传入
    x=123, type(x)=<class 'int'>
    y=([1, 2, 3, 4, 5], {'name': 'alam', 'age': 12}), type(y)=<class 'tuple'>
    z={}, type(z)=<class 'dict'>
    '''

    # 这个才是符合预期的， 实参和形参都要加 * 和 **
    pringParam(a1, *a2, **a3)
    '''
    输出：
    x=123, type(x)=<class 'int'>
    y=(1, 2, 3, 4, 5), type(y)=<class 'tuple'>
    z={'name': 'alam', 'age': 12}, type(z)=<class 'dict'>
    '''
