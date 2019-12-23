# -*- coding: utf-8 -*-
import os
import sys
import io
import chardet
import mmap
import pickle
from tempfile import TemporaryFile, TemporaryDirectory, NamedTemporaryFile

'''
文件与IO

(1) 文本文件和二进制文件的区别：
文本文件和二进制文件物理上都是二进制存储，只有逻辑上的区别：
    文本文件是基于字符编码的文件，常采用ASCII、UTF-8、UTF-16、GBK等字符编码方式，文本编辑器可以识别出这些编码格式，并将编码值转换成字符展示出来。
    二进制文件（如视频、图片、音频等），是自定义编码的文件，文本编辑器无法识别这些文件的编码格式, 我们会看到一堆乱码。
open()的文本格式和二进制格式：
    唯一的区别是Windows系统中换行符的处理。在Windows系统中，以文本格式读取文件时，会将 "\r\n" 转换成 "\n"；反之，以文本格式将数据写入文件时，会将 "\n" 转换成 "\r\n"。
    在 Unix/Linux 系统中，默认的文件换行符就是 \n，因此在 Unix/Linux 系统中文本格式和二进制格式并无本质的区别。
    为了保险起见，对于 Windows平台最好用 b 打开二进制文件；对于 Unix/Linux 平台，打开二进制文件，可以用 b，也可以不用。

(2) python3字符串（参考d_str2.py）
    str - 普通字符串(字符序列), 写入文本方式打开的文件
    bytes - 二进制数据流(字节序列)， 写入二进制方式打开的文件

(3) 查看文件编码方式：
    pip install chardet

(4) 文件打开模式
    r - 只读
    w - 只写
    a - 追加
    x - 文件不存在时才能写入
    r+/w+/a+ - 读写
    t - 文本文件
    b - 二进制文件
    说明：默认是二进制b方式， 'r+t' 可以表示以文本可读可写方式打开
'''


# 测试文本文件
def txtReadWrite():
    # 文本文件写入
    with open('data/data.txt', 'wt', encoding='utf-8') as f3:
        f3.write('你好 hello\n')           # write传入字符串参数
        f3.writelines(['aaa\n', 'bbb\n', 'ccc\n'])
        print("python 学习", file=f3)

    # 文本文件读取
    with open('data/data.txt', 'rt', encoding='utf-8') as f:   # with控制块结束时文件会自动关闭
        data = f.read()                  # 一次性读出
        print('f.read() ->', data)
        # 游标指向起点，重新读取
        f.seek(0)
        for line in f:                   # 逐行读取
            print('f -> ', line)
        # 游标指向起点，重新读取
        f.seek(0)
        for l in f.readlines():
            print('f.readlines() ->', l)  # readlines() 读取整个文件得到一个迭代器以供遍历
        # 游标指向起点，重新读取
        f.seek(0)
        print('f.readline() ->', f.readline())             # readline()读取一行


def binReadWrite():
    # 二进制方式读写
    with open('data/data.bin', 'w+b') as f:       # 以读写的方式打开二进制文件
        f.write(b'hello \xe4\xb8\xad\xe5\x9b\xbd')

        data = f.read()
        # byte转str
        print(data.decode('utf-8'))

    # 二进制文件支持数组和c结构体类型直接写入
    import array
    nums = array.array('i', [1, 2, 5, 6])
    with open('data/data.bin', 'wb') as f2:
        f2.write(nums)

    a = array.array('i', [0, 0, 0, 0])        # i代表int类型
    with open('data/data.bin', 'rb') as f3:
        f3.readinto(a)
    print(a)


def strIOTest():
    # 使用类似文件对象的方式，操作普通字符串(str)和二进制字符串(bytes)
    s = io.StringIO()
    s.write("StringIO 111\n")
    print("StringIO 222", file=s)
    data = s.getvalue()             # 读取
    print('s.getvalue() -> ', data, type(data))
    s.seek(0)
    print('s.read() -> ', s.read())                # 读取

    s = io.BytesIO()
    s.write(b'BytesIO \xe4\xb8\xad\xe5\x9b\xbd')
    data = s.getvalue()
    print(data.decode('utf-8'))

    s.seek(0)
    print('s.read()->', s.read().decode('utf-8'))


def gzip_bz2_test():
    # 读写压缩文件
    # gzip
    import gzip
    with gzip.open('data/data.gz', 'wt') as f:
        f.write('gzip 你好中国')
    with gzip.open('data/data.gz', 'rt') as f:
        print('gzip -> ', f.read())

    # bz2
    import bz2
    with bz2.open('data/data.bz2', mode='wt') as f1:
        f1.write('bz2 你好中国')
    with bz2.open('data/data.bz2', mode='rt') as f1:
        print('bz2 -> ', f1.read())


def mmapTest():
    size = os.path.getsize('data/data.bin')
    fd = os.open('data/data.bin', os.O_RDWR)
    m = mmap.mmap(fd, size, access=mmap.ACCESS_READ)
    print('mmap len=', len(m))
    print('slice m[0:10]=', m[0:10])
    m.close()


def openFdTest():
    # 前边的open方法都是打开指定文件名，
    # open还支持传入一个文件描述符(句柄)， 如文件句柄，socket句柄，标准输入句柄等
    bstdout = open(sys.stdout.fileno(), 'wb', closefd=False)  # 自行关闭
    bstdout.write(b'bstdout hello world \n')
    bstdout.flush()
    bstdout.close()

    fd = os.open('data/test.json', os.O_RDWR)
    f = open(fd, 'rt', encoding='utf-8')
    print(f.read())
    f.close()


def temporaryTest():
    with TemporaryFile('w+t') as f:   # 以读写的方式打开文本文件
        f.write('hello\n')
        f.write('TemporaryFile')
        f.seek(0)
        print(f.read())

    # delete=False 防止文件关闭时被自动删除
    with NamedTemporaryFile('w+t', encoding='utf-8', delete=False) as f:
        f.write('NamedTemporaryFile\n')
        f.seek(0)
        print(f.read(), f.name)

    with TemporaryDirectory() as dirname:
        print('dirname=', dirname)


def pickleTest():
    # pickle用于序列化python对象，是python特有的数据编码方式
    # 字典对象的序列化可以用json模块，见test_json.py
    # 大部分python数据类型和自定义类对象都可以通过pickle模块序列话
    from d_class import Student
    st_org = Student('zhangsan', 100)

    # 序列化到字符串
    s = pickle.dumps(st_org)
    st1 = pickle.loads(s)
    print('pickle.loads -> ', st1)

    # 序列话到文件
    with open('data/student.data', 'wb') as f:
        pickle.dump(st_org, f)
    with open('data/student.data', 'rb') as f:
        st2 = pickle.load(f)
        print('pickle.load -> ', st2)        # 打印时调用__str__方法

    s = pickle.dumps([1, 2, 3, 4])
    assert(pickle.loads(s) == [1, 2, 3, 4])


if __name__ == "__main__":
    # txtReadWrite()         # 文本文件读写
    # binReadWrite()         # 二进制文件读写
    # strIOTest()            # 字符串用类文件对象操作
    # gzip_bz2_test()        # 文件压缩读写
    # mmapTest()             # 内存映射
    # openFdTest()           # 扩展：open文件句柄（socket，标准输入输出流)
    # temporaryTest()        # 临时文件、目录
    # pickleTest()           # 对象序列化
    exit(0)

    # 检测文件的编码方式
    f = open('data/data.txt', 'rb')
    data = f.read()
    print('encoding -> ', chardet.detect(data))
    f.close()

    # 当前文件的编码
    print('fileencoding=', sys.getfilesystemencoding())

    # print输出数据，改变默认的分隔符，行尾符
    print('my', 'name', 'is', 'Alice', sep=', ', end='!!\n')

    # 测试文件、目录是否存在
    assert(os.path.exists('data/data.bin') is True)
    assert(os.path.isfile('data/test.json') is True)
    assert(os.path.isdir('data/'))
    print('size=', os.path.getsize('data/test.json'))
    print('mtime=', os.path.getctime('data/test.json'))
    print('ctime=', os.path.getctime('data/test.json'))
    print('listdir=', os.listdir('data/'))

    # 获取文件长度
    print('file size=', os.path.getsize('data/data.txt'))

    # 文件名与路径
    assert(os.path.basename('data/test.json') == 'test.json')
    assert(os.path.dirname('data/test.json') == 'data')
    assert(os.path.join('tmp', 'data', os.path.basename('data/test.json')) == r'tmp\data\test.json')
    print(os.path.splitext('data/test.json'))  # 分隔扩展名 ('data/test', '.json')
