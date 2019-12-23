# -*- coding: utf-8 -*-
from flask import Flask, render_template, request, flash

'''
第二部分：原生态form表单操作：
    (1) 表单
        表单是html页面中负责数据采集的部件，通过表单把用户输入的数据提交给服务器。
        包括三部分：标签、域、按钮，举例：
        <form method="post">
            <label>用户名：</label><input type="text" name="username" /><br />
            <label>密码：</label><input type="text" name="password" /><br />
            <label>确认密码：</label><input type="text" name="password2" /><br />
            <input type="submit" value="提交" /><br />
        </form>
    (2) vscode生成html模板文件：
        文件->新建文件->右下角点击'纯文本',选择文件类型为html->命令提示框输入英文的i，会自动补全一个html模板页面。
    (3) flash - 给模板传递消息
        需要对消息内容进行加密，设置secret_key，做消息加密混淆
        在模板里遍历获取闪现消息

    (4)案例：
        实现一个基础的表单（参考：form_demo.py）
        使用Flask-WTF实现表单（参考：wtf_demo.py）
'''

# 创建flask应用程序实例
# 需要传入__name__,作用是为了确定资源所在的路径
app = Flask(__name__)
app.secret_key = "cbjtestform"

# 定义路由与视图函数
# Flask定义路由是通过装饰器实现的
# 实现简单的登录处理
@app.route('/', methods=['POST', 'GET'])
def hello_world():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        password2 = request.form.get('password2')
        if not all([username, password, password2]):
            # print("参数不完整")
            flash("参数不完整")
        elif password != password2:
            # print("密码输入有误")
            flash("密码输入有误")
        else:
            return "success"
    return render_template('form_tp.html')


# 启动程序
if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=False)
