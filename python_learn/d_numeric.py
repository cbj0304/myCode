# -*- coding: utf-8 -*-
from fractions import Fraction
from decimal import Decimal
from decimal import localcontext
import cmath
import numpy as np
import random


'''
python3内置数值类型(Numeric)：
    整数（int）：python3中的整型只有一种 long 类型
    浮点数（float）：
    定点数（decimal.Decimal）：固定的小数点位置，固定位数的整数部分和小数部分，更精确。
    复数（complex）：用指数达到了浮动小数点的效果，更灵活。
    分数（fractions.Fraction）：有理数。
    布尔类型（bool）： True/False本质上是1/0。

python中的数学模块math/cmath：
    math模块：提供对实数的计算支持
    cmath模块：供对于复数运算的支持(a=3+4j)
    具体函数查看： dir(math)  dir(cmath)

无穷大于非数字：
    正无穷：float('inf')
    负无穷：float('-inf')
    非数字：float('nan')
    得到inf时就查看是否有溢出或者除以0，得到nan时就查看是否有非法操作（如对负数开平方）。

numPy模块
    第三方库安装 pip install numpy
    向量和矩阵的线性代数运算

random模块
    随机数生成模块
'''


def IntegerTest():
    print('整型测试...')
    data = 120
    print('data={}, type={}'.format(data, type(data)))    # <class 'int'>

    exit(0)


def FloatTest():
    print('浮点数测试...')
    # 生成浮点数
    data1 = 12.34
    # float() 将整数和字符串转换成浮点数
    data2 = float('12.35')
    print('data={}, type={}'.format(data1, type(data1)))   # <class 'float'>
    print('data={}, type={}'.format(data2, type(data2)))   # <class 'float'>

    exit(0)


def DecimalTest():
    print('定点数测试...')
    # 生成定点数
    data = Decimal('120.3')
    print('data={}, type={}'.format(data, type(data)))    # <class 'decimal.Decimal'>

    exit(0)


def ComplexTest():
    print('复数测试...')
    # 生成复数
    data1 = 2 + 3j
    data2 = complex(3, 4)
    print('data={}, type={}'.format(data1, type(data1)))    # <class 'complex'>
    print('data={}, type={}'.format(data2, type(data2)))    # <class 'complex'>

    # 取出实部和虚部
    assert(data1.real == 2)
    assert(data1.imag == 3)

    # 复数运算
    print(data1 * data2)
    print(data1 / data2)
    print(abs(data1))
    print(cmath.sin(data1))
    print(cmath.exp(data1))

    # 对复数数组执行操作
    arr = np.array([2+3j, 4+5j, 7-8j])
    print(arr + 2)
    print(np.sin(arr))

    print(cmath.sqrt(-1))

    exit(0)


def BooleanTest():
    print('布尔类型测试...')
    # 生成布尔类型
    data1 = False
    data2 = bool(100)
    print('data={}, type={}'.format(data1, type(data1)))     # <class 'bool'>
    print('data={}, type={}'.format(data2, type(data2)))     # <class 'bool'>  True

    exit(0)


def FractionTest():
    print('有理数测试...')
    # 生成有理数
    data = Fraction(2, 8)
    print('data={}, type={}'.format(data, type(data)))     # 1/4 <class 'fractions.Fraction'>

    # 取出分子和分母
    assert(data.numerator == 1)      # 分子
    assert(data.denominator == 4)    # 分母

    # 分数运算
    a = Fraction(3, 4)
    b = Fraction(7, 16)
    print(a + b)
    print(a * b)
    print(float(a))
    pi = Fraction('3.141592654')
    print(pi.limit_denominator(8))    # 设置分母的最大值，返回最接近的有理数 22/7

    # float转分数（有理数）
    x = 3.75
    tu = x.as_integer_ratio()   # (15, 4) <class 'tuple'>
    print(Fraction(*tu))

    exit(0)


def numPyTest():
    print('test numPy')

    # 一维数组，作用到所有元素上
    ax = np.array([1, 4, 5, 2])
    ay = np.array([2, 3, 1, 5])

    print(ax, type(ax))        # <class 'numpy.ndarray'>
    print(ax * 2)
    print(ax + 10)
    print(ax + ay)
    print(ax * ay)

    myfun = lambda x: 3*x**2 - 2*x + 7
    print(myfun(ax))

    print(np.sqrt(ax))
    print(np.cos(ax))

    # 多维数组，作用到所有元素上
    grid = np.zeros(shape=(3, 4), dtype=float)
    print(grid + 10)
    print(grid, type(grid))      # <class 'numpy.ndarray'>

    grid2 = np.array([[1, 2, 3], [4, 5, 6]])   # 2行3列
    print(np.sin(grid2))
    print(grid2[0])              # 第1行
    print(grid2[:, 0])           # 第1列
    print(grid2[0, 0:2])       # 1-2行，1-3列   (下标从0开始，:两侧左开右闭)

    # 矩阵操作
    m = np.matrix([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    print(m, type(m))
    print(m.T)        # 转置
    v = np.matrix([[1], [2], [3]])
    print(m * v)

    exit(0)


def RandomTest():
    print('test Random...')
    values = [10, 2, 3, 4, 5, 6]
    a1 = random.choice(values)      # 随机选取一个元素
    a2 = random.sample(values, 3)   # 随机选取n个元素
    random.shuffle(values)          # 乱序输出
    print('choice={}\nsample={}\nshuffle={}'.format(a1, a2, values))

    b1 = random.randint(0, 100)       # 产生随机整数
    b2 = random.random()              # 产生0-1的随机浮点数
    b3 = random.getrandbits(100)      # 产生占据100个二进制bit位的大整数（python支持大整数运算，位数不受限制）
    print('randint={}\nrandom={}\ngetrandbits={}'.format(b1, b2, b3))

    # python随机数生成算法是确定可复现的，可以修改初始化种子(可以用int或者bytes字符串)
    random.seed(1234)
    print(random.randint(0, 10))
    random.seed(b'test')
    print(random.randint(0, 10))

    print(random.uniform(1.0, 10.0))     # 获取均匀分布的随机数
    print(random.gauss(10.0, 2.0))    # 产生高斯分布的随机数（均值10.0， 标准差2.0）
 
    exit(0)


if __name__ == '__main__':
    # IntegerTest()
    # FloatTest()
    # DecimalTest()
    # ComplexTest()
    # BooleanTest()
    # FractionTest()
    # numPyTest()
    RandomTest()

    # 四舍五入
    assert(round(2.4573, 2) == 2.46)
    assert(round(2.76) == 3)
    assert(round(273513, -3) == 274000)

    # 浮点数不能特别精确的表示十进制数，如果要求不能有任何误差就用定点数，但是会有一些性能损耗
    # 一般情况下浮点数足以
    a = Decimal('4.2')
    b = Decimal('2.15')
    assert(a + b == Decimal('6.35'))    # 试试换成float怎么样？...
    # 创建本地上下文控制定点数参数，如有效数字
    with localcontext() as ctx:
        ctx.prec = 3
        print(a/b)

    # 格式化  '[<>^]?width[,]?(.digits)?'
    x = 12345.678
    print(format(x, '>10.2f'))
    print(format(x, '^10.2E'))
    print(format(x, ','))      # 千分位分隔符

    # 二、八、十、十六进制
    y = 1234
    s1 = bin(y)       # <class 'str'>
    s2 = oct(y)
    s3 = hex(y)
    len = y.bit_length()   # 转换为二进制占多少bit位
    print('bin(y)={}\noct(y)={}\nhex(y)={}\nbit_length()={}'.format(s1, s2, s3, len))
    # 另一种方法
    print(format(y, 'b'))
    print(format(y, 'o'))
    print(format(y, 'x'))
    # 转十进制
    assert(int('4d2', 16) == 1234)
    assert(int('10011010010', 2) == 1234)

    # 整数转字节码
    d = 20747284487117727783387188
    nbyte, rem = divmod(d.bit_length(), 8)    # 计算整数占多少字节
    if rem:
        nbyte += 1
    print(d.to_bytes(nbyte, 'little'))
    assert(d.to_bytes(nbyte, 'big') == b'\x11)h\x8b\xb3Y<\xfc#\x004')
    assert(d.from_bytes(b'\x11)h\x8b\xb3Y<\xfc#\x004', 'big') == 20747284487117727783387188)
