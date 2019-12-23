# -*- coding: utf-8 -*-
from flask import Flask
from flask import render_template
from flask import request

'''
第一部分：flask基础

(1) 为什么要用web框架？
    web框架提供 稳定性、安全性、高并发性的支持，
    避免重复造轮子, 专注于核心业务逻辑的处理, 提高工作效率。

(2) flask是一个轻量级的web开发框架。
    自带的核心功能：路由模块、模板引擎。
    其他功能如邮件扩展、用户认证、数据库操作等都需要第三方扩展来实现。
    flask中文文档：https://dormousehole.readthedocs.io/en/latest/

(3) 配置python+flask开发环境：
    （1）安装虚拟环境
        虚拟环境主要是为了避免包的混乱和版本的冲突， 它是Python解释器的一个私有的副本，在这个环境中你可以安装私有包（通过pip安装都会装到该python副本的lib>site-packages中，查看所有的依赖可以用pip freeze命令），而且不会影响系统中安装的全局或者其他的Python解释器。使用虚拟环境还有个好处是不需要管理员权限。
    （2）安装flask
        pip install flask (flask安装到虚拟环境文件夹中)

    在新环境中部署依赖：
        虚拟环境中依赖包及版本号生成至文件中：pip freeze > requirements.txt
        按照文件中的依赖包依次下载并安装：pip install -r requirements.txt

(4) 测试工具：
    安装软件postman，模拟收发http请求。

(5) jinja2模板引擎
    flask内置的模板语言，用于把一些变量数据动态传入网页模板中。
    (1) 注释
        {# 这是一行注释 #}
    (2) 变量代码块
        str {{ var }}
        list {{ my_list }}  {{ my_list.2 }}  {{ my_list[2] }}
        dict {{my_dict }} {{ my_dict['name'] }}  {{my_dict.name}}
    (3) 控制代码块
        {% if flag %} ... {% endif %}
        {% for v in varlist %} ... {% endfor %}
    (4) 内置过滤器（通过管道符后跟过滤器，可以链式操作）
        字符串操作
            禁止转义 {{ '<em>hello</em>' | safe }}
            首字母转大写 {{ 'hello' | capitalize }}
            转小写 {{ 'HELLO' | lower }}
            转大写 {{ 'hello' | upper }}
            每个单词的首字母转大写 {{ 'hello' | title }}
            字符串反转 {{ 'olleh' | reverse }}
            格式化输出 {{ '%s is %d' | format('name',17) }}
            去掉html标签  {{ '<em>hello</em>' | striptags }}
            字符串截断  {{ 'hello every one' | truncate(9)}}
        列表操作
            取第一个元素 {{ [1, 2, 3, 5] | first }}
            取最后一个元素 {{ [1, 2, 3, 4] | last }}
            获取列表长度 {{ [1, 2, 3, 4] | length }}
            列表求和 {{ [1, 2, 3, 4] | sum }}
            列表排序  {{ [3, 7, 2, 1] | sort }}
'''

# 创建flask应用程序实例
# 需要传入__name__,作用是为了确定资源所在的路径
app = Flask(__name__)

# 定义路由与视图函数
# Flask定义路由是通过装饰器实现的
@app.route('/helloworld')
def hello_world():
    return 'hello world!'


# 通过methods参数指明请求类型，默认是get请求
@app.route('/deal_request', methods=['GET', 'POST'])
def deal_request():
    if request.method == 'GET':
        # get通过request.args.get("param_name","")形式获取参数值
        get_q = request.args.get('q', '')
        return render_template('result.html', result=get_q)
    elif request.method == 'POST':
        # post通过request.form["param_name"]形式获取参数值
        post_q = request.form['q']
        return render_template('result.html', result=post_q)


# <>定义路由的参数, 并在视图函数括号内填入参数名
# 参数类型默认是str, 限定类型，如int: float:
@app.route('/orders/<int:order_id>')
def get_order_id(order_id):
    return 'order={}'.format(order_id)


@app.route('/')
def test_data():
    # 通过键值对的方式传入参数
    mystr = "https://www.python.org"
    mylist = [3, 7, 2, 1, 5]
    mydict = {"name": "cbj", "age": 18}
    return render_template('jinja2_tp.html', mystr=mystr, mylist=mylist, mydict=mydict)


# 启动程序
if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=False)
