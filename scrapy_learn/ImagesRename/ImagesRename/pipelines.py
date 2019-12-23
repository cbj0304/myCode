# -*- coding: utf-8 -*-
import re
from scrapy.pipelines.images import ImagesPipeline
from scrapy import Request

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# 继承自图片管道类ImagesPipeline，图片会自动保存到配置文件设置的路径IMAGES_STORE中
class ImagesrenamePipeline(ImagesPipeline):

    def get_media_requests(self, item, info):
        # 循环每一张图片地址下载，若传过来的不是集合则无需循环直接yield
        for image_url in item['imgurl']:
            # item里面的数据是从spider获取，然后通过item传递给下面方法：file_path
            yield Request(image_url, meta={'name': item['imgname']})

    # 重命名，若不重写这函数，图片名为哈希(md5)
    def file_path(self, request, response=None, info=None):

        # 提取url前面名称作为图片名。
        image_guid = request.url.split('/')[-1]
        # 接收上面item传递过来的图片名称
        name = request.meta['name']
        # 过滤windows字符串，不经过这么一个步骤，你会发现有乱码或无法下载
        name = re.sub(r'[？\\*|“<>:/]', '', name)
        # 分文件夹存储的关键：{0}对应着name；{1}对应着image_guid
        filename = u'{0}/{1}'.format(name, image_guid)
        return filename
