# -*- coding: utf-8 -*-
from flask import Flask
from flask_sqlalchemy import SQLAlchemy


'''
第四部分：
    案例：flask数据库操作
    (1) Flask-SQLAlchmey
        Flask-SQLAlchmey是一个操作关系型数据库的flask扩展，
        让开发者不用直接和sql语句打交道，而是通过python对象来操作数据库。
        Flask-SQLAlchmey中，数据库使用url指定，而且程序使用的数据库必须保存到flask配置对象的FLASKALCHEMY_DATABASE_URI键中

        安装flask扩展：
        pip install flask-sqlalchemy
        如果连接的是mysql数据库，还需要安装mysqldb：
        pip install flask-mysqldb

    (2) 创建数据库模型
    sqlalchemy数据类型和python、mysql数据类型的对应关系：
        类型名 	            Python类型 	          数据库类型
        Integer 	        int 整数(4字节) 	  INT
        SmallInteger 	    int 整数(2字节) 	  SMALLINT
        BigInteger 	        int或long 	          BIGINT
        Float 	            float 	              FLOAT
        Numeric 	        decimal.Decimal 	  DECIMAL
        String 	            str 	              VARCHAR
        Text 	            str 	              TEXT
        Boolean 	        bool 	              BOOLEAN
        Date 	            datetime.date 	      DATE
        Time 	            datetime.time 	      TIME
        DateTime 	        datetime.datetime 	  DATETIME
        Enum 	            str 	              ENUM
        LargeBinary 	    str 	              VARBINARY

    (3) 查询操作
        常用查询过滤器（写条件的）
            filter()
            filter_by()
            limit
            offset()
            order_by()
            group_by()
        常用查询执行器（开始执行的）
            all()
            first()
            first_or_404() 返回查询的第一个结果，如未查到返回404
            get()
            get_or_404()  返回指定主键对应的行，如不存在返回404
            count()
            paginate() 返回一个paginate对象，它包含指定范围的结果
'''

# 创建flask应用程序实例
# 需要传入__name__,作用是为了确定资源所在的路径
app = Flask(__name__)
# 配置数据库地址
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://spider:spider2013@10.160.81.11:3306/mytest'
# 跟踪数据库的修改，不建议开启，未来版本中会被移除
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
# 创建数据库对象实例
db = SQLAlchemy(app)

'''
一对多关系的两张表：
    角色
        - 角色id
        - 角色名称（管理员、普通用户）
    用户
        - 用户id、用户名、邮箱、密码
        - 角色id（外键，关联角色表的角色id）
'''


# 数据库模型
class Role(db.Model):
    # 定义表名
    __tablename__ = 'roles'

    # 定义字段
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(16), unique=True)

    # 也可以在这里定义
    # myuser = db.relationship('User', backref='myroles')

    # 支持可读字符串打印
    def __repr__(self):
        return '<Role: {} {}>'.format(self.name, self.id)


class User(db.Model):
    __tablename__ = 'users'

    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(16), unique=True)
    email = db.Column(db.String(32), unique=True)
    password = db.Column(db.String(32))
    role_id = db.Column(db.Integer, db.ForeignKey('roles.id'))  # 关联外键（多对一）
    # User希望有一个role属性，但是这个属性的定义需要在另一个模型中定义，反向引用

    # 添加关系引用
    # db.relationship('Post'): 正向关联
    # backref='myuser': 反向引用
    # 技巧：在(多对一)多的一方定义外键，关系引用可以在任一方定义（一方即可）
    # users表中的记录通过myroles查找关联的roles表中的值
    # roles表中的记录通过myusers查询关联的user表中的值
    # myroles是给自己用的，myuser是给对方Role用的
    myroles = db.relationship('Role', backref='myuser')

    def __repr__(self):
        return '<User: name={} id={} email={} pswd={} rid={}>'.format(
            self.name, self.id, self.email, self.password, self.role_id)


# 定义路由与视图函数
# Flask定义路由是通过装饰器实现的
@app.route('/helloworld')
def hello_world():
    return 'hello world!'


# 启动程序
if __name__ == '__main__':
    # 删除所有继承自db.Model的表
    db.drop_all()
    # 创建所有继承自db.Model的表
    db.create_all()

    '''
    (1) 测试增删改查
        数据库的增删改，需要通过会话：
        db.session.add(role)
        db.session.add_all([user1, user2, ...])
        db.session.commit()
        db.session.rollback()
        db.session.delete(user)
    '''

    # 插入数据
    ro1 = Role(name='admin')
    db.session.add(ro1)
    db.session.commit()
    ro2 = Role(name='user')
    db.session.add(ro2)
    db.session.commit()

    us1 = User(name='jzs1', email='jzs1@163.com', password='ps3456', role_id=ro1.id)
    us2 = User(name='azs2', email='azs2@163.com', password='12as35', role_id=ro2.id)
    us3 = User(name='szs3', email='szs3@163.com', password='166556', role_id=ro2.id)
    us4 = User(name='dzs4', email='dzs4@163.com', password='154rg6', role_id=ro1.id)
    us5 = User(name='rzs5', email='rzs5@163.com', password='245886', role_id=ro1.id)
    us6 = User(name='tzs6', email='tzs6@163.com', password='123aa6', role_id=ro2.id)
    db.session.add_all([us1, us2, us3, us4, us5, us6])
    db.session.commit()

    # 修改数据
    us3.name = 'baijie'
    db.session.commit()        # 修改了某个字段，只需要commit即可，不需要再add了

    # 删除数据
    db.session.delete(us5)
    db.session.commit()

    # 显示数据库内容
    print("User---", User.query.all())

    # 查询操作
    # 1.查询所有用户
    User.query.all()
    # 2.查询有多少个用户
    User.query.count()
    # 3.查询第一个用户
    User.query.first()
    # 4.查询id为4的用户
    User.query.get(4)  # 主键为4
    User.query.filter_by(id=4).first()     # filter_by(属性=val)
    User.query.filter(User.id == 4).first()  # filter(对象.属性==val) 功能更强大，可以实现更多查询，如比较运算符

    '''
    (2) 测试关联关系
        User表和Role表是一对多的关系，User表通过外键role_id和Role表关联
        如果想通过User对象询用户的角色信息，或者通过Role对象查询角色对应的多个用户的信息，
        需要两表建立关联(user查role)和反向引用(role查user)：
        db.relationship('User', backref='role') -> User是另一侧对象实例(模型)，role为自定义的反向引用的别名
    '''
    # 删除表
    db.drop_all()
    # 创建表
    db.create_all()
    # 测试关联关系
    role = Role(name='admin')
    db.session.add(role)
    db.session.commit()
    user1 = User(name='sz', role_id=role.id)
    user2 = User(name='ls', role_id=role.id)
    db.session.add_all([user1, user2])
    db.session.commit()
    print("role.users--", role.myuser)   # 查询role这条记录对应的user表的信息
    print("user1.roles--", user1.myroles)  # 查询user1这一行对应的roles表的信息
    print("user1={}, user1.roles.name={}".format(user1, user1.myroles.name))

    app.run(host='127.0.0.1', port=8080, debug=False)
