# -*- coding: utf-8 -*-
from flask import Flask, render_template


# 创建flask应用程序实例
# 需要传入__name__,作用是为了确定资源所在的路径
app = Flask(__name__)

# 定义路由与视图函数
# Flask定义路由是通过装饰器实现的
@app.route('/helloworld')
def hello_world():
    return render_template('result.html', result='hello world')


# 启动程序
if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=False)
