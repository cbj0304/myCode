# -*- coding: utf-8 -*-

'''
locals() 和 globals() 是python 的内建函数，他们提供了字典形式访问局部变量和全局变量的方式。
locals() 返回当前局部变量的深拷贝，修改locals() 中变量值对原变量本身没有影响。
globals() 返回全局变量的字典，修改其中的内容，值会真正的发生改变。
'''

ga = "hello world"


def test(**args):
    a = "local hello world"
    print('locals()={}'.format(locals()))
    print('globals()={}'.format(globals()))

    # 通过词典访问并修改局部变量，不生效
    locals()['a'] = "change local hello world"
    print('after change locals()={}'.format(locals()))


if __name__ == "__main__":
    # d是globals， 参数args是locals
    d = {"name": "cbj", "age": 20}
    test(**d)

    # 通过词典访问并修改全局变量，生效
    globals()['ga'] = "change hello world"
    print('after globals()={}'.format(globals()))
