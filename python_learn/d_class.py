# encoding: utf-8

'''
python
私有属性（静态属性、普通属性）、私有方法：
格式：在私有属性/方法名称前加双下划线。
权限：一般在当前类内部被调用，不能被外部对象或者继承类调用。

但是python的私有是伪私有，可以通过"对象._类名__属性名"被调用，但是绝对不允许，
原因是：类在创建时,如果遇到了私有成员(包括私有静态字段,私有普通字段,私有方法)它会将其保存在内存时自动在前面加上_类名

访问权限：
公有: 外部对象可以访问；类内部可以访问；派生类中可以访问
私有: 仅类内部可以访问

'''


class Person(object):
    def __init__(self, name):
        self.name = name


class Student(Person):

    topic1 = "公有静态字段"
    __topic2 = "私有静态字段"

    # 创建实例本身，属性绑定到self
    # 先调用父类的构造函数，再构造子类
    def __init__(self, name, score):
        Person.__init__(self, name)
        self.score = score
        self.topic3 = "公有普通字段"
        self.__topic3 = "私有普通字段"

    # 调用的时候，参数self代表类对象本身，不用传入
    # 公有方法
    def printScore(self):
        print("name=%s, score=%d" % (self.name, self.score))

    # 公有方法
    def getGrade(self):
        return self.__getAgrade()

    # 私有方法
    def __getAgrade(self):
        if self.score > 90:
            return 'A'
        else:
            return 'B'

    def __str__(self):
        str = 'name={}, ascore={}'.format(self.name, self.score)
        return str


if __name__ == "__main__":
    st = Student("bj", 95)
    print(st.getGrade())
    print(st)
