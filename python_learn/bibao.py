# encoding: utf-8

def decfun(func):
    def dec_mysum(x, y):     # 装饰器内部函数直接私有化被修饰的函数的参数
        x = x * 10
        y = y * 10
        return func(x, y)
    return dec_mysum

@decfun
def mysum(a, b):
    print(a+b)

mysum(2, 3)