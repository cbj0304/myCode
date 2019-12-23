# -*- coding: utf-8 -*-
from functools import partial
import math

'''
python中的闭包：
    在一个外函数中定义了一个内函数，内函数里运用外函数的临时变量，并且外函数的返回值是内函数的引用。
    “闭包”的本质就是函数的嵌套定义，即在函数内部再定义函数。
    “闭包”有两种不同的方式，第一种是在函数内部就“直接调用了”；第二种是“返回一个函数名称”。
闭包中引用的自由变量有如下性质：
    1. 闭包的每个实例引用的自由变量互不干扰；
    2. 一个闭包实例对其自由变量的修改会被传递到下一次该闭包实例的调用。
闭包的作用：
    一般函数，内部声明的局部变量、函数参数等在函数调用结束之后函数里面保存的信息就被销毁了。
    闭包的作用是保存函数的状态信息，使函数的局部变量信息依然可以保存下来。


'''


def outer_func():      # 定义闭包
    lst = []
    def inner_func(name):
        lst.append(len(lst) + 1)
        print(name, lst)
    return inner_func


if __name__ == '__main__':
    # *参数　**参数，参考test_param.py
    def avg(first, *rest):
        return (first + sum(rest)) / (1 + len(rest))

    print(avg(1, 2, 3, 4))

    # 函数返回多个值，实际上是先创建一个元组，然后返回的
    def test_ret_value():
        return 1, 2, "hello"

    ret1, ret2, ret3 = test_ret_value()      # 用多个变量接收返回值
    print('ret1={} type={}, re2={} type={}, ret3={} type={}'.format(
        ret1, type(ret1),
        ret2, type(ret2),
        ret3, type(ret3)
    ))
    ret = test_ret_value()                  # 用单个变量接收返回值 tuple
    print('ret={} type={}'.format(ret, type(ret)))

    # 以下两种赋值是等价的
    x = "hello", 1.2, 45
    y = ("hello", 1.2, 45)
    print('type(x)={} type(y)={}'.format(type(x), type(y)))

    # lambda中自由变量的值是运行时绑定，不是定义时绑定的
    x = 10
    a = lambda y: x + y         # 定义时
    x = 20
    b = lambda y: x + y         # 定义时
    assert(a(10) == 30)                # 执行时，输出30
    assert(b(10) == 30)                # 执行时，输出30

    # 使匿名函数在定义时就捕获到值 -- 将参数定义成默认参数
    x = 10
    a = lambda y, x=x: x + y
    x = 20
    b = lambda y, x=x: x + y
    assert(a(10) == 20)              # 输出 20
    assert(b(10) == 30)

    # 匿名函数列表
    func = [lambda x, n=n: x+n for n in range(5)]
    for i in func:
        print(i(0))

    # partial固定某些参数的值
    def test_partial(a, b, c, d):
        print(a, b, c, d)

    s1 = partial(test_partial, 1, d=42)  # 设置了默认参数值 a=1, d=42,只需要在给b、c赋值即可
    s1('bb', 'cc')

    # list的排序方法可以接受一个key关键字参数作为排序规则
    # 以下按照距离点(4, 3)的远近排序
    # partial用于微调其他库函数所使用的回调函数的参数
    points = [(1, 2), (3, 4), (5, 6), (7, 8)]

    def distance(p1, p2):
        x1, y1 = p1
        x2, y2 = p2
        return math.hypot(x2-x1, y2-y1)

    points.sort(key=partial(distance, (4, 3)))
    print('points sort ->', points)

    # 测试闭包
    f1 = outer_func()
    f1("bb1")
    f1("bb1")
    f2 = outer_func()
    f2("bb2")
    f1("bb1")
    f2("bb2")

