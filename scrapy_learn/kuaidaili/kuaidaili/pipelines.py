# -*- coding: utf-8 -*-
import json

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


class KuaidailiPipeline(object):
    # 创建管道时，只执行一次（可选实现，用于参数初始化）
    def __init__(self):
        pass

    # 开启爬虫时，只执行一次，可以替代__init__进行参数初始化（可选实现）
    def open_spider(self, spider):
        self.__file = open('data.json', 'w')

    # spider抛出item时，scrapy引擎都会通知pipiline调用此函数处理（必须返回item对象，否则item被丢弃）
    # spider是爬虫对象，如获取爬虫名：spider.name
    # ensure_ascii=False，禁用ascii，支持中文
    # dict() 将item类强转成python的字典
    def process_item(self, item, spider):
        self.__file.write(json.dumps(dict(item), ensure_ascii=False) + ',\n')
        return item

    # 爬虫关闭时，只执行一次（可选实现）
    def close_spider(self, spider):
        self.__file.close()
