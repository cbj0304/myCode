# -*- coding: utf-8 -*-

'''
协程的概念：
定义：
    协程，又称微线程， 纤程。
    线程是系统级别的，它们是由操作系统调度；协程是程序级别的，由程序员根据需要自己调度。
    我们把一个线程（coroutineTest）中的一个个函数（A和B）叫做子程序，
    那么子程序（A）在执行过程中可以中断去执行别的子程序（B）；
    别的子程序（B）也可以中断回来继续执行之前的子程序（A），这就是协程。

python使用生成器yield中断机制实现协程：
    生成器、yield关键字、next()、send()函数
    next()、send()函数作用类似，区别是send()可以传参数，c.next()和c.send(None)作用一样。

'''


# 理解 生成器、yield关键字、next()、send()函数 运行
def func():
    while True:
        a = yield 10
        print(a)


def generatorTest():
    c = func()                # 生成可迭代对象
    m = next(c)               # 首次调用，启动生成器，进入while第1次循环，遇到yield中断
    n1 = c.send('hello')      # 从中断处开始执行，yield收到参数'hello'，并把hello赋值给a，打印a, 第二次while循环，遇到yield中断
    n2 = c.send('world')      # 同上
    print('m={} n1={} n2={}'.format(m, n1, n2))


# 协程操作
def A():
    yield
    print('1')
    yield
    print('2')
    yield
    print('3')
    yield
    print('4')


def B():
    yield
    print('a')
    yield
    print('b')
    yield
    print('c')
    yield
    print('d')


def coroutineTest():
    a = A()
    next(a)
    b = B()
    next(b)

    next(a)
    next(a)

    next(b)
    next(b)

    next(a)


if __name__ == '__main__':
    # 生成器机制
    generatorTest()
    # 协程
    coroutineTest()
