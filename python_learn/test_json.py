# -*- coding:utf-8 -*-
import json

'''
json是字符串，长得像字典，需要转换为字典才可以通过key、value来取值。

四个函数（技巧：带s的都是和字符串相关的，不带s的都是和文件对象相关的）
    loads -> json串转字典
    dumps -> 字典转字符串

    load -> 将.json文件转字典
    dump -> 字典转.json文件
    (后边两个可以等价于字典和字符串互转后，字符串写入或者读取文件)

'''

if __name__ == "__main__":
    s = """
    {
        "code": 101,
        "stu": [
            {"name": "张三", "age": 18},
            {"name": "李四", "age": 20}
            ]
    }
    """
    # loads
    d = json.loads(s)
    print('loads => d={}\n keys={}\n type={}'.format(d, d.keys(), type(d)))

    # load
    with open('.vscode/settings.json', encoding='utf-8') as f:
        d1 = json.load(f)
        print('load => d1={}\n keys={}\n type={}'.format(d1, d1.keys(), type(d1)))

    # dumps
    dct = {
        "code": 101,
        "stu": [
            {"name": "张三", "age": 18},
            {"name": "李四", "age": 20}
            ]
    }
    s1 = json.dumps(dct, ensure_ascii=False)
    print('dumps => s1={} \n type={}'.format(s1, type(s1)))

    # dump
    # json.dumps 序列化时对中文默认使用的ascii编码.想输出真正的中文需要指定ensure_ascii=False
    # indent 表示字符串换行+缩进
    with open('test.json', 'w', encoding='utf-8') as f:
        json.dump(dct, f, indent=4, ensure_ascii=False)
