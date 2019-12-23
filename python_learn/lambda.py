# -*- coding=utf-8 -*-

from functools import reduce

'''
(1) lambda表达式(匿名函数)
     格式： 参数:表达式
    （说明：冒号前边是参数，参数可以是0个或多个，多个时用逗号隔开，冒号后边是返回值，返回一个函数对象）

    函数：
    def add(x, y):
        return x + y

    转为lambda表达式：
    add = lambda x,y : x + y

    调用 print(add(3, 4))
(2) for...in...if...表达式
(3) 三元运算符（处理简单的if...else...）
'''


if __name__ == '__main__':
    # sort/map/filter/reduce(累计)，这些内置函数，都可以传一个lambda表达式作为函数对象
    # lambda表达式的参数x是可迭代的一个元素
    # 排序：
    a = [(1, 2), (4, -1), (9, 10), (13, -3)]
    a.sort(key=lambda x: x[1])
    print('sort -> type={}, ret={}'.format(type(a), a))

    # 元素映射：map返回的是迭代器(不要和dict混淆)，需要转list再打印
    b = map(lambda x: (x[0]+x[1]), a)
    print('map -> type={}, list(ret)={}'.format(type(b), list(b)))

    # 过滤：
    c = filter(lambda x: x[1] > 0, a)
    print('filter -> type={}, list(ret)={}'.format(type(c), list(c)))

    d = reduce(lambda x, y: x + y, [1, 2, 3, 4, 5])
    print('reduce -> type={} ret={}'.format(type(d), d))

    # for...in...if...表达式
    print([x[0]+x[1] for x in a])      # -> map
    print([x for x in a if x[1] > 0])  # -> filter

    # 三元运算符（处理简单的if...else...）
    if 1 == 1:
        print('yes')
    else:
        print('no')

    data = 'yes' if 1 == 1 else 'no'
    print('data={}'.format(data))
