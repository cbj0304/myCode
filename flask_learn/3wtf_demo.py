# -*- coding: utf-8 -*-
from flask import Flask, render_template, request, flash
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import DataRequired, EqualTo

'''
第三部分：
    案例：使用Flask-WTF实现表单

flask-WTF:
    flask_wtf是对wtforms组件的封装，是flask框架的表单验证模块，可以很方便生成表单，
    也可以当做json数据交互的验证工具，支持热插拔。

安装：
    pip install Flask-WTF

常用字段说明：
    BooleanField：布尔类型，如False,True
    StringField：字符串类型
    DecimalField：小数点文本字段，如：‘1.23’
    DateField：日期字段，格式：'%Y-%m-%d'
    DateTimeField:日期字段，格式：'%Y-%m-%d %H:%M:%S'
    FieldList:统一字段类型组成列表，如：FieldList(StringField('Name', [validators.required()]))
    FloatField:浮点数类型
    IntegerField：整形
    SelectMultipleField：多选框
    RadioField：单选框
    TextAreaField:文本域，可接受多行输入
    PasswordField：密码字段，输入的不会直接在浏览器明文显示
    FileField：上传文件，但不会处理验证文件，需要手动处理
    HiddenField：隐藏字段
    SubmitField：按钮

表单字段参数：
    label:字段的名字
    default：默认值
    validators：字段的验证序列 [DataRequired(), Length(4,20)]->必填字段，长度在4-20， 见下边
    description：字段的描述
    choices：SelectField和他的子类有的字段，选择框，多选一

字段验证序列：
    Required/required/DataRequired/data_required: 不能为空
    InputRequired/input_required：和DataRequired的区别在于可以是空白字符串；
    Email/email：验证符合邮件的格式，只有最基本的验证；
    EqualTo/equal_to:比较两个字段的值，比如密码和确认密码，如果不相等就触发错误，equal_to(field,message),需要输入另一个字段的名字。
    IPAddress/ip_address:验证是否是ip地址，默认验证IPV4地址。
    MacAddress/mac_address:验证是否符合mac格式；
    UUID：是否是uuid格式；
    URL/url:验证是否符合url格式；
    Regexp/regexp:用提供的正则表达式验证字段；Regexp(r"")
    Length/length:设置字段值的长度，Length(min,max);
    NumberRange/number_range:设置一个数字字段的取值范围，可以针对浮点数和小数；NumberRange(min,max)
    Optional/optional:允许字段为空并停止验证；
    NoneOf/none_of:将传入的数据和无效的比较，是抛出异常；Noneof(values).
    Anyof/any_of:将传入的数据和预设的数据比较，不是异常。Anyof(values).

使用WTF实现一个表单：
    自定义表单类，使用现成的控件和验证方式
在模板的表单标签下添加csrf token： {{ form.csrf_token }}
    CSRF（Cross Site Request Forgery, 跨站域请求伪造）是一种网络的攻击方式
'''

# 创建flask应用程序实例
# 需要传入__name__,作用是为了确定资源所在的路径
app = Flask(__name__)
app.secret_key = "cbjtestform"


# 自定义表单类
class LoginForm(FlaskForm):
    username = StringField(label='用户名', validators=[DataRequired()])     # '用户名' 是label, validators验证函数列表
    password = PasswordField('密码', validators=[DataRequired()])
    password2 = PasswordField('确认密码', validators=[DataRequired(), EqualTo('password', '密码输入不一致')])
    submit = SubmitField('提交')


@app.route('/', methods=['GET', 'POST'])
def login():
    login_form = LoginForm()

    # 1.判断请求方式
    if request.method == 'POST':
        # 2.参数获取
        username = request.form.get('username')
        password = request.form.get('password')
        password2 = request.form.get('password2')
        # 或者直接从表单对象取数据
        password_2 = login_form.password2.data

        # 3.参数验证
        # 我们没有 CSRF token
        if login_form.validate_on_submit():  # 提交时进行参数校验
            print('name={} pswd={} pawd2={} pswd2={}'.format(
                username, password, password2, password_2))
            return "success"
        else:
            flash('参数有误')

    return render_template('wtf_tp.html', form=login_form)


# 定义路由与视图函数
# Flask定义路由是通过装饰器实现的
@app.route('/helloworld')
def hello_world():
    return 'hello world!'


# 启动程序
if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=False)
