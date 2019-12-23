# -*- coding: utf-8 -*-
from flask import Flask, render_template, request, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy
from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField
from wtforms.validators import DataRequired


# 创建flask应用程序实例
# 需要传入__name__,作用是为了确定资源所在的路径
app = Flask(__name__)
app.secret_key = 'test'
# 配置数据库地址（mysql://user:passwd@ip:port/database）
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://spider:spider2013@10.160.81.11:3306/mytest'
# 跟踪数据库的修改，不建议开启，未来版本中会被移除
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
# 创建数据库对象实例
db = SQLAlchemy(app)

'''
图书管理系统案例：
    1.配置数据库
        a.导入SQLAlchemy扩展
        b.创建db对象
        c.在终端创建数据库(db对象只是增删表，以及增删改查操作,需先行创建database)
    2.添加书和作者模型
        作者模型：字段->id，name              一
        书籍模型：字段->id，name，author_id   多
        a.模型继承db.Model
        b.表名__tablename__
        c.字段名 db.Column
        d.添加关系引用：db.relationship
    3.添加数据
        main函数中初始化数据表中的数据
    4.使用模板显示数据库查询的数据
        a.查询所有作者的信息，传给模板
        b.模板中两重for循环，取出作者，作者的书籍(此处用的关系引用)
    5.使用wtf显示表单
        a.自定义表单类
        b.模板中显示
        c.secret_key / csrf_token 等问题
    6.实现相关的增删的逻辑
        验证逻辑：
        1.调用wtf的函数实现验证
        2.验证通过获取数据
        3.判断作者是否存在
        4.如果作者存在，判断书籍书否存在，没有重复书籍，则添加数据，如果重复，提示错误
        5.如果作者不存在，则添加作者和书籍
        6.验证不通过提示错误
'''


# 作者模型：字段->id，name              一
# 书籍模型：字段->id，name，author_id   多
class Author(db.Model):
    # 表名
    __tablename__ = 'authors'

    # 字段
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(48), unique=True)

    # 支持打印
    def __repr__(self):
        return '<Author> id={}, name={}'.format(self.id, self.name)

    # 一对多关系(books和author是自定义的名字，Book是另一个模型的类名)
    books = db.relationship('Book', backref='author')


class Book(db.Model):
    __tablename__ = 'books'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(48), unique=True)
    author_id = db.Column(db.Integer, db.ForeignKey('authors.id'))


class AddForm(FlaskForm):
    author_name = StringField(label='作者', validators=[DataRequired()])
    book_name = StringField(label='书籍', validators=[DataRequired()])
    submit = SubmitField('添加')


# 定义路由与视图函数
# Flask定义路由是通过装饰器实现的
@app.route('/', methods=['GET', 'POST'])
def show_page():

    add_form = AddForm()
    # 提交时进行表单参数验证   
    if not add_form.validate_on_submit():
        if request.method == 'POST':
            flash('参数不完整！')
    else:
        author_name = add_form.author_name.data
        book_name = add_form.book_name.data
        print('222', author_name, book_name)
        # 判断作者和书籍是否存在
        author = Author.query.filter_by(name='author_name').first()
        if author:
            # 作者存在，如果书籍存在提示已存在，如果书籍不存在，插入书籍
            book = Book.query.filter_by(name=book_name).first()
            if book:
                flash('书籍已存在！')
            else:
                new_book = Book(name=book_name, author_id=author.id)
                try:
                    db.session.add(new_book)
                    db.session.commit()
                except Exception as e:
                    flash('插入书籍失败')
                    db.session.rollback()
        else:
            # 作者不存在，如果书籍存在提示已存在，如果书籍不存在，插入作者和书籍
            book = Book.query.filter_by(name=book_name).first()
            if book:
                flash('书籍已存在！')
            else:
                try:
                    new_author = Author(name=author_name)
                    new_book = Book(name=book_name)
                    print("111", new_author, new_book)
                    new_author.books.append(new_book)
                    db.session.add_all([new_author, new_book])
                    db.session.commit()       # 添加作者和书籍
                except Exception as e:
                    flash('插入作者和书籍失败')
                    db.session.rollback()

    # 查询数据
    authors = Author.query.all()
    print(authors)

    # 渲染到页面
    return render_template('booklist.html', authors=authors, form=add_form)


# 删除书籍，删除完毕， 更新数据库后重定向到显示面展示
@app.route('/delete_book/<int:book_id>')
def delete_book(book_id):
    try:
        # 根据传过来的book_id 查询到book对象进行删除
        book = Book.query.get(book_id)
        # 删除数据
        db.session.delete(book)
        db.session.commit()
        flash('删除成功')
    except BaseException as e:
        print(e)
        flash('数据库操作失败')
        db.session.rollback()

    return redirect(url_for('show_page'))


# 删除作者，删除完毕更新数据库，并重定向到显示页面
@app.route('/delete_author/<int:author_id>')
def delete_author(author_id):
    try:
        # 根据传过来的author_id 查询到author对象
        author = Author.query.get(author_id)
        # 查询作者名下的书籍模型
        books = author.books
        # 遍历删除
        for book in books:
            db.session.delete(book)
        # 删除数据
        db.session.delete(author)
        db.session.commit()
        flash('删除成功')
    except BaseException as e:
        print(e)
        flash('数据库操作失败')
        db.session.rollback()

    return redirect(url_for('show_page'))


# 启动程序
if __name__ == '__main__':
    # 删除所有继承自db.Model的表
    db.drop_all()
    # 创建所有继承自db.Model的表
    db.create_all()

    # 生成作者数据
    au1 = Author(name='金庸')
    au2 = Author(name='古龙')
    au3 = Author(name='梁羽生')
    db.session.add_all([au1, au2, au3])  # 把数据提交给用户会话
    db.session.commit()                  # 提交会话

    # 生成书籍数据
    bk1 = Book(name='《神雕侠侣》', author_id=au1.id)
    bk2 = Book(name='《天龙八部》', author_id=au1.id)
    bk3 = Book(name='《鹿鼎记》', author_id=au1.id)
    bk4 = Book(name='《浣花洗剑录》', author_id=au2.id)
    bk5 = Book(name='《多情剑客无情剑》', author_id=au2.id)
    bk6 = Book(name='《七剑下天山》', author_id=au3.id)
    bk7 = Book(name='《白发魔女传》', author_id=au3.id)

    db.session.add_all([bk1, bk2, bk3, bk4, bk5, bk6, bk7])
    db.session.commit()

    app.run(host='127.0.0.1', port=8080, debug=False)
