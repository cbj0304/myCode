# encoding: utf-8

import os
from collections import Iterable
from collections import defaultdict
from collections import OrderedDict
from operator import itemgetter
from collections import Counter
from collections import namedtuple
from collections import ChainMap
import json

'''
python内置容器
列表（list）
举例：[1，2，3]， 有序集合，元素可重复，元素类型可以不同。
方法：append/insert/extend/pop/clear/copy/index/remove/reverse/sort

元组（tuple）
举例：('abc', 3, 3.21)
和list类似，但是元素一旦初始化不能修改，没有append/insert修改元素的这类方法。

集合（set）
举例：{1, 4, 7}
无序集合，元素没有重复。
方法：add/clear/copy/discard/pop/remove/difference/intersection/symmetric_difference/union/issubset/issuperset/isdisjoin

词典（dict）
举例：{'a':2,'b':18}
通过 key 来查找 value。key-value序对是没有顺序的，key不能重复。
方法：clear/copy/fromkeys/get/has_key/items/keys/setdefault/update/values/pop/popitem

字符串（string）
举例：'abc'
字符的有序集合
方法：

以上都是可迭代对象（Iterable），内部实现了__iter__方法，可以通过for...in...循环遍历/迭代。
通过isinstance()函数可以判断一个对象是否是 iterable 对象。
isinstance(a, Iterable) -> 如果a是可迭代类型，返回True

学习链接：
内置容器： https://blog.csdn.net/wu_tian_hao/article/details/81253902
可迭代对象： https://blog.csdn.net/huaxiawudi/article/details/81129144
集合操作：https://www.jianshu.com/p/245fe6597060

'''

if __name__ == '__main__':
    a = [1, 2, 23, -2, 4, 23]
    print(a)
    print(list(a))
    print(type(a))

    assert(a.index(23, 0, len(a)) == 2)
    assert(isinstance(a, Iterable) is True)

    a.reverse()
    print(a)
    print(a.count(23))

    tu = (1, 23, 'aaa')
    print(tu)

    # 可迭代对象之间可以相互转换
    listA = [3, 4, 2, 6, 4]
    tupleA = tuple(listA)
    setA = set(tupleA)
    print(tupleA)
    print(setA)

    # set
    s = set('acbds')
    print(s)  # {'c', 's', 'a', 'b', 'd'}

    # defaultdict会自动为将要访问的键创建映射实体，类似于普通dict的setdefault方法
    d = defaultdict(list)
    d['a'] = [1, 2, 3]
    d['b'] = [4, 5]
    d['a2'] = [11]
    print(json.dumps(d))

    dic = {}
    dic.setdefault('a2', []).append(2)
    dic.setdefault('b3', []).append(3)
    dic.setdefault('b1', []).append(11)
    print(json.dumps(dic))

    # 使词典有序
    d2 = OrderedDict()
    d2['a2'] = 200
    d2['a5'] = 500
    d2['a1'] = 100
    print(json.dumps(d2))

    # 字典计算
    prices = {
        'CC': 201,
        'BB': 403,
        'JJ': 100
    }
    # zip：接受两个可迭代对象，将两个对象中对应元素'压缩'成一个个的tuple，
    # 返回由这些tuple组成的list
    # 若两个可迭代对象不等长，以短者为基准截断
    lst = list(zip(prices.values(), prices.keys()))
    assert(max(lst) == (403, 'BB'))
    lst.sort()
    print(lst)    # [(100, 'JJ'), (201, 'CC'), (403, 'BB')]

    la = [3, 5, 2, 10]
    ta = ('g', 'f', 'c')
    za = zip(ta, la)
    print(list(za))

    # 可迭代对象的集合操作
    print(prices.keys())
    another = {'CC', 'DD'}
    another2 = ['CC', 'DD']
    print(prices.keys() & another)
    print(prices.keys() & another2)

    # 词频统计
    words = ["hello", "you", "you", "and", "hello", "hello"]
    words_count = Counter(words)
    print(words_count, type(words_count))
    print(words_count.most_common(2))

    # 根据某一键值排序
    lines = [
        {'name': 'aaa', 'age': 17, 'score': 98.2},
        {'name': 'bbb', 'age': 16, 'score': 89.2},
        {'name': 'ccc', 'age': 21, 'score': 10.2},
        {'name': 'ddd', 'age': 16, 'score': 10.2}
    ]
    by_age = sorted(lines, key=itemgetter('age'))
    print(by_age)
    by_age_score = sorted(lines, key=itemgetter('age', 'score'))
    print(by_age_score)

    mylist = [3, 5, -1, 9, -5, 7]
    out = [n if n > 0 else 0 for n in mylist]
    print(out)

    mydict = {
        "beijing": 100,
        "shanghai": 300,
        "tianjin": 90,
        "suzhou": 160,
        "nanjing": 88
    }
    skey = ["beijing", "suzhou"]
    # 字典推导
    p1 = [(key, val) for key, val in mydict.items() if val > 100]
    p2 = {key: mydict[key] for key in mydict.keys() if key in skey}
    p3 = dict((key, val) for key, val in mydict.items() if val > 100)
    print(p1)

    # 命名元组(代码从下标操作解脱出来)
    student = namedtuple('student', ['name', 'age', 'score'])  # 返回一种类型student
    st = student("cbj", 18, 100)
    print(st)
    print("new name=%s, age=%d" % (st.name, st.age))
    print("old name=%s, age=%d" % (st[0], st[1]))

    # 生成器表达式
    nums = [2, 3, 4]
    s1 = sum(x*x for x in nums)     # 使用生成器表达式（更优雅和省内存）
    s2 = sum(x*x for x in nums)     # 创建一个临时列表

    files = os.listdir('D:/gcctool/0_mytestdata')
    print([file for file in files])

    if any([file.endswith('.py') for file in files]):
        print('there be python.')

    datas = ['my ', 'age ', 18]
    print(','.join([str(x) for x in datas]))

    lang = [
        {'name': 'c++', 'score': 100},
        {'name': 'python', 'score': 95},
        {'name': 'shell', 'score': 90}
    ]
    m1 = min([x['score'] for x in lang])
    # 另一种迭代器版本
    # 处理列表页每一行是，对于每个可迭代的元素，使用lambda函数
    m2 = min(lang, key=lambda x: x['score'])
    print("m1=%d, m2=%s" % (m1, m2))

    # 多字典合并
    a = {'x': 1, 'y': 2}
    b = {'z': 4, 'x': 3}
    c = ChainMap(a, b)
    print("x=%d, y=%d, z=%d" % (c['x'], c['y'], c['z']))
    del c['y']
    print(c.keys(), c.values(), c.items())
