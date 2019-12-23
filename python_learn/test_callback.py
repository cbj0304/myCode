# -*- coding: utf-8 -*-

'''
回调函数：
    回调函数就是一个通过函数指针调用的函数。
    把函数指针（地址）作为参数传递给另一个函数，当这个指针被用来调用其所指向的函数时，我们就说这是回调函数。
    回调函数不是由该函数的实现方直接调用，而是在特定的事件或条件发生时由另外的一方调用的。

'''


def add(a, b):
    return a + b


def max(a, b):
    return a if a > b else b


def min(a, b):
    return a if a < b else b


def compute(a, b, func):
    return func(a, b)


def simpleCallback():
    print('回调函数的定义...')
    a = input('a=')
    b = input('b=')
    print('a+b=', compute(int(a), int(b), add))
    print('max=', compute(int(a), int(b), max))
    print('min=', compute(int(a), int(b), min))


def apply_async(func, args, *, callback):
    result = func(*args)
    callback(result)      # 回调函数处理result


def print_reslut(result):
    print('get->', result)


class ResultHandler(object):
    def __init__(self, seq):
        self.seq = seq

    def handler(self, result):
        self.seq += 1
        print('result={}, handler={}'.format(result, self.seq))


def ResultHandlerFunc():
    seq = 200
    def handlerFunc(result):
        nonlocal seq         # nonlocal关键字说明，此变量不仅在inner函数里边有效，在整个大函数都有效
        seq += 10
        print('result={}, handler={}'.format(result, seq))
    return handlerFunc


def make_handler():
    seq = 300
    while True:
        result = yield
        seq += 1
        print('result={}, seq={}'.format(result, seq))


def callbackWithState():
    print('带额外状态信息的回调函数三种实现...')

    # 回调函数的应用
    apply_async(add, ("hello ", "world"), callback=print_reslut)

    # 带状态的回调函数（类成员函数）
    h = ResultHandler(100)
    apply_async(add, ("hello ", "world"), callback=h.handler)

    # 带状态的回调函数（闭包函数）
    f = ResultHandlerFunc()
    apply_async(add, ("hello ", "world"), callback=f)

    # 带状态的回调函数（协程）
    g = make_handler()     # 创建一个生成器，可迭代对象
    next(g)                # 首次调用，启动生成器, 遇到yield中断
    apply_async(add, ("hello ", "world"), callback=g.send)   # send的参数被yield接收返回


def inlineCallback():
    print('内联回调函数...')


if __name__ == '__main__':
    # simpleCallback()
    callbackWithState()
    exit(0)
