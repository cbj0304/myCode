# 数据结构和算法

## vscode快捷键
代码整体右移： 选中 + tab
代码整体左移： 选中 + shift + tab


## 自定义flake8语法检验时每行最大字符限制
命令行输入 flake8 --help
查看flake8的参数设置，其中有一项是--max-line-length=n 每行最大字符数，
修改vscode的配置 setting.json，增加：
"python.linting.flake8Args": ["--max-line-length=248"]

## python中的{} [] ()
[] 是单个字符匹配，字符集/排除字符集。特殊字符写在 [] 会被当成普通字符来匹配。
    [0-3]：表示找到这一个位置上的字符只能是 0 到 3 这四个数字。
    [^0-3]：表示找到这一个位置上的字符只能是除了 0 到 3 之外的所有字符。
    [(a)]: 表示匹配(、a、)中的一种。
() 是分组匹配。
    (abc)?，表示这一组要么一起出现，要么不出现。
    (?:abc) 表示找到这样abc这样一组，但是不记录。
    a(?=bbb) 表示a后边必须紧跟三个b。
    (?<=bbb)a 表示a前边必须有三个b。
{}一般用来表示匹配的长度。
    比如 \s{3} 表示匹配三个空格。
    [0-9]{0,9} 表示长度为0到9的数字字符串。

## 字符编码
ascII/unicode/utf-8 http://www.ruanyifeng.com/blog/2007/10/ascii_unicode_and_utf-8.html
(1) ascii码：规定了128个字符的编码（内存中用一个byte的后边7bit表示），表示英文够用，中文不够用。
(2) unicode：是一个符号集，规定了符号的二进制码(世界统一),但是没有规定二进制码该如何存储。
(3) utf8是互联网上使用广泛的一种unicode实现方式。它是一种变长编码，可以用1-4个字节表示一个符号，比如英文字母用1个字节表示，utf8和ascii码是相同的；比如汉字就需要用3个字节表示。

## python3数据类型：
(1) 数值类型（参考 test_numeric.py）
    整数（Integer）：python3中的整型只有一种 long 类型
    浮点数（Float）：
    复数（Complex）：
    分数（Fraction）：有理数。
    布尔类型（Boolean）： True/False本质上是1/0。

(2) 字符串（参考 test_str1.py/test_str2.py/test_str3.py）
    str
    bytes

(3) 容器类型（参考 test_container.py）
    列表（list）：
    元组（tuple）：
    集合（set）：
    词典（dict）：
    说明：字符串也可以看作是字符的集合。

类和对象，继续。。。 page 237
