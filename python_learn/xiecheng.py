# encoding: utf-8

import time

def task_1():
    while True:
        print("task 1 is runing...")
        time.sleep(0.1)
        yield

def task_2():
    while True:
        print("task 2 is runing...")
        time.sleep(0.1)
        yield

def main():
    t1 = task_1()     # 生成器（可迭代对象），调用next()时，遇到yeild返回
    t2 = task_2()

    # 先让t1执行一会儿，t1遇到yeild的时候，会返回位置T1，
    # 然后next(t2)会运行t2,t2遇到yeild时，会再次切换到t1中，
    # 这样 t1/t2/t1/t2...交替执行，最终实现了多任务...协程
    while True:
        next(t1)         # 位置T1
        next(t2)         # 位置T2