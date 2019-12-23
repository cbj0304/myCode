# -*- coding: utf-8 -*-
import re
from fnmatch import fnmatch, fnmatchcase
import unicodedata
from test_class import Student
import textwrap

'''
字符串处理函数汇总：
    切割：
    re.split()
    str[m:n]

    查找与匹配：
    str.startswith()
    str.endswith()
    re.findall()
    re.match()
    str.find()
    fnmatch()
    fnmatchcase()

    替换：
    str.replace()
    re.sub()

    格式化：
    unicodedata.normalize()
    str.lstrip()
    str.rstrip()
    str.strip()

    转换：
    str.upper()
    str.lower()
    str.translate()

    格式化：
    文本标准化：unicodedata.normalize()
    清空左右指定字符：str.lstrip()/str.rstrip()/str.strip()
    替换：str.translate()/str.replace()
    对齐：str.ljust()/str.rjust()/str.center()/format
    拼接：join/+/print(..., sep=':')
    字符串中插入变量: format()/format_map()+vars()
    指定列宽格式化字符串: testwrap.fill()

    其他：
    s.isdigit()
'''


if __name__ == '__main__':

    # -------------------切割---------------------------
    str = 'hello my; name, is cbj'
    lst = re.split(r'[,;\s]\s*', str)
    print('split -> type={}, ret={}'.format(type(lst), lst))

    # ()在正则中用于捕获和分组
    lst2 = re.split(r'(,|;|\s)\s*', str)
    print('split re-has-() -> type={} ret={}'.format(type(lst2), lst2))

    # (?:...) 分组，不捕获
    lst3 = re.split(r'(?:,|;|\s)\s*', str)
    print('split re-has-() -> type={} ret={}'.format(type(lst3), lst3))

    # seq[start:end:step]
    lst4 = [1, 2, 3, 4, 5]
    assert(lst4[::2] == [1, 3, 5])

    # -------------------查找与匹配---------------------------
    # 检查字符串的开头结尾
    url = 'http://www.python.org'
    assert(url.startswith('http') is True)
    assert(url.endswith('https') is False)
    tu = ('org', 'python')
    assert(url.endswith(tu) is True)

    assert(url[-3:] == 'org')      # 切片的方式检查收尾

    ret = re.match(r'http', url)     # 正则的方式检查收尾
    print(ret.group() if ret else None)

    files = ['a.py', 'b.cpp', 'c.java']
    print(any(f for f in files if f.endswith('py')))
    print([f.endswith('py') for f in files])

    # 使用通配符匹配字符串（fnmatch模块）
    assert(fnmatch('test02.TXT', '*.txt') is True)
    assert(fnmatch('test02.py', '?est0?.py') is True)
    assert(fnmatch('test02.py', 'test[0-9]*.py') is True)
    assert(fnmatchcase('test.TXT', '*.txt') is False)    # 大小写敏感

    # 查找 （str.find 或者 re.match re.findall）
    assert(url.find('python') == 11)

    # -------------------替换---------------------------
    # 替换 （str.replace 或者 re.sub）
    str = 'my name is A, your name is B'
    strnew = str.replace('name', 'fullname')
    assert(str == 'my name is A, your name is B')  # 未被修改
    assert(strnew == 'my fullname is A, your fullname is B')

    # -------------------格式化---------------------------
    # 将文本标准化
    s1 = 'Spicy Jalape\u00f1o'
    s2 = 'Spicy Jalapen\u0303o'
    assert((s1 == s2) is False)

    t1 = unicodedata.normalize('NFC', s1)
    t2 = unicodedata.normalize('NFC', s2)
    assert((t1 == t2) is True)

    # 内置函数：大小写转换，判断是不是数字字符等等
    s = "hello world 2018"
    assert(s.isdigit() is False)
    assert(re.findall(r'\d+', s)[0].isdigit() is True)
    assert(s.upper() == 'HELLO WORLD 2018')
    assert(s.upper().lower() == 'hello world 2018')

    # strip
    s = '---*** hello  '
    assert(s.lstrip('-*') == ' hello  ')    # 去掉左侧的-或者*
    assert(s.rstrip() == '---*** hello')    # 去掉右侧空格

    # translate
    replace_map = {
        ord('\t'): ' ',
        ord('\f'): ' ',
        ord('\r'): None,   # 表示删除
    }
    s = 'my \fname\r is\tcb\rj\n'
    print(s.translate(replace_map))
    # 创建替换词典的技巧
    print(dict.fromkeys([1, 2, 3]))
    print(dict.fromkeys([1, 2, 3], "test"))
    # 也可以用replace
    s = 'my \fname\r is\tcb\rj\n'
    s = s.replace('\t', ' ')
    s = s.replace('\f', ' ')
    s = s.replace('\r', '')
    print(s)

    # 字符串对齐 ljust/rjust/center/format
    text = 'Hello World'
    f1 = text.ljust(20, '*')
    f2 = text.rjust(20)
    f3 = text.center(20, '-')
    g1 = format(text, '*<20')
    g2 = format(text, '>20')
    g3 = format(text, '-^20')
    print('f1={}\nf2={}\nf3={}'.format(f1, f2, f3))
    print('g1={}\ng2={}\ng3={}'.format(g1, g2, g3))

    data = 10.3247
    s1 = '{:-^20}'.format(text)
    s2 = '{:>10.2f}'.format(data)
    print('s1={}\ns2={}'.format(s1, s2))

    # 字符串拼接 join/+/print(..., sep=':')
    lst = ['hello', 'my', 'name', 'is', 'John']
    res1 = ' '.join(lst)             # 此方法效率更优
    res2 = lst[0] + ' ' + lst[4]     # 会引起内存赋值和垃圾回收
    res3 = 'hello' 'world'
    print('join -> res1={}\nres2={}\nres3={}'.format(res1, res2, res3))

    print('hello', 'my', 'world', sep=' ')

    # 使用生成器函数，复用代码
    def sample():
        yield 'hello1'
        yield 'my1'
        yield 'world1'

    print(' '.join(sample()))
    for part in sample():
        print(part)

    # 字符串中插入变量 format()/format_map()+vars()
    s = '{name} has {n} apples'
    r1 = s.format(name='cbj', n=10)
    name = 'bj'
    n = 100
    r2 = s.format_map(vars())    # vars从变量域中自行查找
    st = Student('zzs', 100)       # vars()提取对象实例中的成员变量
    r3 = '{name} has {score}'.format_map(vars(st))
    print('format -> r1={}\nr2={}\nr3={}\n'.format(r1, r2, r3))

    # 指定列宽格式化字符串testwrap.fill()
    text = """
Look into my eyes, look into my eyes, the eyes, the eyes, \
the eyes, not around the eyes, don't look around the eyes, \
look into my eyes, you're under"""
    print(textwrap.fill(text, 20))
    print(textwrap.fill(text, 30, initial_indent='    '))  # 首行缩进，其他格式见函数声明
