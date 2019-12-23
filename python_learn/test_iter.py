# -*- coding: utf-8 -*-
from itertools import zip_longest
from itertools import chain
from itertools import permutations
from itertools import combinations
from collections import Iterable
'''
---------------------------- 迭代器 -------------------------------
可迭代对象：
    内部实现了__iter__方法，如str/list/tuple/set/dict
    可迭代对象的优势：
        1. 可以用for循环遍历
        2. 可用一些现成的算法，如sum、list等
    如何产生可迭代对象：
        1. 内建可迭代对象（list、set、tuple、dict、str）
        2. 自定义可迭代对象 (参考 intRange)
        3. 代理可迭代对象（参考 iterProxyText）
        4. 利用生成器(包含yield关键字)创建可迭代对象（参考 yeildText， 生成器机制和协程：test_coroutine.py）
迭代器对象：
    内部实现了__next__方法，此方法不依赖索引取值。
    内部实现了__iter__方法，执行迭代器的__iter__方法得到的依然是迭代器本身
作用过程(参考 iterTest)：
    执行可迭代对象下的__iter__方法,返回一个迭代器对象,
    在通过迭代器对象的__next__方法取值,如果取值次数超过源值的数量就会报错
迭代器的优点：
    1.提供了一种不依赖索引的取值方式
    2.同一时刻在内存中只存在一个值,更节省内存

（1）正向迭代

（2）反向迭代
    列表的reverse()方法
    切片操作
    实现反向迭代协议的__reversesd__方法，它返回一个反向迭代器
'''


def iterTest():
    a = [1, 2]
    it = a.__iter__()
    print(it.__next__())
    print(it.__next__())
    # print(it.__next__())    # 越界报错

    # next方法操作迭代器对象
    a1 = [3, 4, 5]
    it1 = iter(a1)          # <class 'list_iterator'>
    try:
        while True:
            print(next(it1))
    except StopIteration:
        pass

    # 文件是迭代器对象
    with open('test_re.py', encoding='utf-8') as f:
        while True:
            line = next(f, None)
            if line is None:
                break
            print(line, end='#')


# 自定义迭代对象
class intRange(object):
    def __init__(self, start, end, step):
        self.start = start
        self.end = end
        self.step = step

    # 实现正向迭代方法
    def __iter__(self):
        n = self.start
        while n <= self.end:
            yield n
            n += self.step

    # 定义反向迭代方法
    def __reversed__(self):
        n = self.end
        while n >= self.start:
            yield n
            n -= self.step


# 定义代理可迭代对象
class iterProxyText(object):
    def __init__(self, topic):
        self._topic = topic
        self._values = []

    def add_value(self, val):
        self._values.append(val)

    def __iter__(self):
        return iter(self._values)


# 利用生成器创建可迭代对象和方法
def yeildText():
    # 类
    class iterYeild(object):
        def __init__(self):
            self.values = [100, 200, 300]

        def __iter__(self):
            for i in self.values:
                yield i

    # 测试（类）
    y = iterYeild()
    for i in y:
        print(i)
    print(list(y))

    # 函数
    def frange(start, stop, step):
        x = start
        while x < stop:
            yield x
            x += step

    # 测试（函数）
    for i in frange(10, 15, 2):
        print(i)
    print(sum(frange(10, 15, 2)))

    L = [x * x for x in range(1, 11) if x % 2 == 0]   # 这是一个列表（可迭代对象）
    # 把[] 换成 () 就创建了一个生成器
    G = (x * x for x in range(1, 11) if x % 2 == 0)
    print('type(L)={}, type(G)={}'.format(type(L), type(G)))


if __name__ == '__main__':
    # iterTest()
    yeildText()
    exit(0)

    # 自定义可迭代对象 实现__iter__/__reverse__方法
    n1 = intRange(1, 5, 1)
    for n in n1:
        print(n)               # 正向
    for n in reversed(n1):
        print(n)               # 反向

    # 其他反向迭代方法，先逆序，在遍历
    d1 = [1, 3, 5, 7, 9]
    d1.reverse()                      # 逆序
    print('list.reverse()=', d1)

    d2 = [1, 3, 5, 7, 9]
    d3 = d2[::-1]                    # 逆序 [start: stop:step]
    print('[::-1]=', d3)

    # 测试代理可迭代对象
    t = iterProxyText('test')
    t.add_value('a')
    t.add_value('b')
    t.add_value('c')
    for i in t:
        print(i)

    # 可迭代对象的enumerate方法
    s = ['a1', 'b1', 'c1']
    for i in enumerate(s):
        print(i)                   # 返回数据及其下标的tuple列表 (0, 'a1') (1, 'b1') ...
    for j in enumerate(s, 10):     # 从10开始
        print(j)

    # 同时迭代多个可迭代对象
    a = ('aaa', 'bbb', 'ccc')
    b = [100, 200, 300, 400]
    for k, v in zip(a, b):
        print('k={}, v={}'.format(k, v))         # 返回3项
    for k1, v1 in zip_longest(a, b):
        print('k1={}, v1={}'.format(k1, v1))     # 返回4项

    # 多个集合合并迭代
    for k3 in chain(a, b):
        print('k3=', k3)

    # 展开一个多层嵌套的序列
    def flatten(items, ignore_types=(str, bytes)):
        for x in items:
            if isinstance(x, Iterable) and not isinstance(x, ignore_types):
                yield from flatten(x)    # 词句可以改为 for i in flatten(x): yeild i
            else:
                yield x

    items = ['a1', ['c1', 'b1', ['f1', 'o1']], 'b3']
    for i in flatten(items):
        print(i)

    # 排列组合
    items = [1, 2, 3]
    print('排列...')
    print('permutations...')
    for p in permutations(items):
        print(p)
    print('permutations 2...')
    for p in permutations(items, 2):
        print(p)

    print('组合...')
    print('combinations 3...')
    for p in combinations(items, 3):
        print(p)
    print('combinations 2...')
    for p in combinations(items, 2):
        print(p)
