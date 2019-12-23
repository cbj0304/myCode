# -*- coding: utf-8 -*-

'''
（1）字符编码：
    (1) ascii码：规定了128个字符的编码（内存中用一个byte的后边7bit表示），表示英文够用，中文不够用。
    (2) unicode：是字符集，规定了符号的二进制码(万国码),但是没有规定二进制码该如何存储。
    (3) utf8：是编码规则，是互联网上使用广泛的一种unicode实现方式。它是一种变长编码，可以用1-4个字节表示一个符号，
    比如英文字母用1个字节表示，utf8和ascii码是相同的；比如汉字就需要用3个字节表示。

（2）python字符串类型：
    参考：python中的str和bytes类型 https://www.cnblogs.com/chownjy/p/6625299.html
    a. python3字符串的两种类型：
    -- str(unicode)  -> <class 'str'>          # 普通字符串
    -- byte码        -> <class 'bytes'>        # 二进制数据流
    [可以简单理解为: python2 中的<class 'unicode'> 变成了 python3 的<class 'str'>
                    python2 中的<class 'str'> 变成了 python3 的<class 'bytes'> ]
    b. str(unicode)对象和bytes对象转换：
        bstr = str.encode('utf-8')
        str = bstr.decode('utf-8')
'''


if __name__ == '__main__':
    # python3 中 unicode和基础str是等价的，类型都是 <class 'str'>
    ustr = u'字符串'
    str = '字符串'
    print('ustr={}, type={}'.format(ustr, type(ustr)))        # <class 'str'>
    print('str={}, type={}'.format(str, type(str)))           # <class 'str'>

    # 字符串转字节码
    bstr = ustr.encode('utf-8')
    print('bstr={}, type={}'.format(bstr, type(bstr)))        # <class 'bytes'>

    # 字节码转字符串
    str_new = bstr.decode('utf-8')
    print('str_new={}, type={}'.format(str_new, type(str_new)))  # <class 'str'>

    # 整型转ascii字符chr(i)  i取值在0-255
    print(chr(97))   # str 'a'

    # ascii字符转整型ord('a')
    print(ord('a'))  # int 97
