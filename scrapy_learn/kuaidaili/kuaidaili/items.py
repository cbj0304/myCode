# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class KuaidailiItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    # pass
    # 定义要提取的结构化数据, 此类可以通过dict()强转成python词典
    # 提取快代理网站的匿名代理信息：ip，port，位置
    ip = scrapy.Field()
    port = scrapy.Field()
    position = scrapy.Field()
