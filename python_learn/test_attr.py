# -*- coding=utf-8 -*-
import re
import test_class

'''
python内置方法：
系统自动创建

__dict__: 以字典的形式显示实例自定义属性
__class__: 实例所在类
__init__ 和 __del__: 构造和析构
__new__: 在__init__之前调用, 用于生成实例对象， __init__主要是作初始化工作。
__doc__: 类文档
__str__:  实例字符串表示，可读性，调用print时触发
__gt__(self, other)：比较函数，self是否大于other对象，类似的还有ge/lt/le/eq
__getattribute__：属性访问拦截器，访问属性时被调用
__dir__：返回属性和方法列表，调用dir(Obj)是触发，常用于显示类的方法属性列表
'''


class Singleton(object):
    # __new__ 实现单例模式
    __instance = None

    def __init__(self):
        pass

    def __new__(cls, *args, **kwargs):
        if Singleton.__instance is None:
            Singleton.__instance = object.__new__(cls, *args, **kwargs)
        return Singleton.__instance


if __name__ == "__main__":

    # 查看模块所有属性
    print(test_class.__dict__)
    st = test_class.Student('cbj', 20)
    st.getGrade()

    # 正则提取所有的函数(正向肯定预查)
    reg = r"[a-z0-9]+(?=\': <function)"
    regObj = re.compile(reg)
    lst = regObj.findall(str(test_class.__dict__))
    print(lst)
