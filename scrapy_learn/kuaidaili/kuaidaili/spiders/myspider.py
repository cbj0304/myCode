# -*- coding: utf-8 -*-
import scrapy
from kuaidaili.items import KuaidailiItem


class MyspiderSpider(scrapy.Spider):
    name = 'myspider'
    allowed_domains = ['kuaidaili.com']
    # start_urls = ['http://kuaidaili.com/']

    # 拼接url
    # 抓取快代理的免费代理ip，通过start_urls获取带抓取的第一个url
    base_url = "https://www.kuaidaili.com/free/inha/"
    offset = 1
    start_urls = [base_url + str(offset)]

    # 可重写该父类该方法，返回一个可迭代的初始抓取列表
    # 默认是通过start_urls生成一个可迭代的待抓取Request对象列表
    # 这些Request对象默认使用get方法抓取，回调函数是parse（抓取请求发出去后，返回结果用parse函数处理）
    # def start_request(self):

    def parse(self, response):
        item = KuaidailiItem()

        node_list = response.xpath("//div[@id='list']/table/tbody/tr")

        for node in node_list:
            item['ip'] = node.xpath("./td[@data-title='IP']/text()").extract()[0]
            item['port'] = node.xpath("./td[@data-title='PORT']/text()").extract()[0]
            item['position'] = node.xpath("./td[@data-title='位置']/text()").extract()[0]
        
            # yield 的重要性：
            # 1. 再次调用时还能回到上次返回的位置继续执行代码, 如果用return，函数就直接退出了再次调用会从头开始执行。
            # 2.对于大批量的数据，yield比一次性返回items更节省内存

            # spider产生item，经由引擎递交给pipeline处理
            yield item

        # spider产生下一个Request抓取请求，经由引擎递交给scheduler处理
        # 注意：这里可以通过拼接url找到下一页链接，也可以通过提取xpath找到下一页的链接
        self.offset += 1
        if self.offset < 30:
            yield scrapy.Request(self.base_url + str(self.offset), callback=self.parse)
