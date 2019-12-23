
# 网络爬虫及分类

    爬虫是一个模拟人类请求网站信息并提取有价值数据的程序。
    分类：
    通用爬虫：爬取所有内容，如通用搜索引擎。
    聚焦爬虫：面向特定需求的爬虫，只提取对自己有价值的信息。

#　python写爬虫程序的优势

    代码简洁，开发效率高，支持的模块、框架多（http请求模块，xml/html解析模块、scrapy框架等等）。

# 环境

    python3 
    vscode 
    虚拟环境（virtualenv/virtualenvwrapper）
    自带库urllib 或者 第三方scrapy框架等

# 基本网络常识

    http协议：超文本传输协议， 80端口。
    https协议：http协议的加密版本，在http协议下加入了ssl层，443端口。

    url：统一资源定位符。
    格式：协议://用户名:密码@子域名.域名.顶级域名:端口号/目录/文件名.文件后缀?参数=值#标志

    http两种常用的请求方法（一共8种）：
        GET：只是从服务器下载数据，并不会对服务器产生影响，一般要用get请求。
        POST：向服务器发送数据（提交表单，上传文件等），可能会导致服务器上新资源建立或已有资源修改。
        其他：HEAD/PUT/DELETE/CONNECT/OPTIONS/TRACE/PATCH
    常用请求参数：
        User-Agent：浏览器名称，可伪造。
        Referer：表明当前请求是从哪个url过来的，也就是上一页的url。
        Cookie：http协议是无状态的，也就是同一个人发送两次请求，服务器是没有能力知道这两个请求是否来自同一个人，因此这时候就用cookie来标识。如用户自动登录。
    常见响应状态码：
        2xx -- 成功
            200：服务器正常返回数据。
        3xx -- 重定向
            301：永久重定向，如输入“www.jingdong.com”会重定向到“www.jd.com”。
            302：临时重定向，比如访问一个需要登录的页面的时候，而此时没有登录，那么就会重定向到登录页面。
        4xx -- 客户端错误，请求语法错误
            400：url错误，请求的url在服务器上找不到。
            403：服务器拒绝访问，权限不够。
            404: 服务器无法根据客户端的请求找到资源（网页）
        5xx -- 服务器错误
            500：服务器内部错误。（服务器的问题）

# urllib库

    python3自带的网络请求库。
    在python3中所有和网络请求相关的方法都被集到了urllib.request模块下边。
    from urllib import request
    resp = request.urlopen('https://www.baidu.com')
    print(type(resp))          # <class 'http.client.HTTPResponse'> 类文件句柄对象
    # print(resp.read(10))
    # print(resp.read())
    # print(resp.readline())
    print(resp.readlines())  # 返回多行存到list中

# scrapy

    安装： pip install scrapy
    终端输入scrapy查看是否安装成功

    scrapy组件及架构：https://www.jianshu.com/p/269eab38f03b
    1. spider（产出Request，处理Response）
    2. Pipeline：管道，爬虫产生的item数据，做过滤和持久化。
    3. Downloader：下载器，接收引擎传递过来的请求，下载，最终将响应结果交给spider爬虫文件。
    4. Scheduler：调度器，将Request存储在任务队列中，引擎会从任务队列中提取任务交给下载器。调度器中不存在任何request了，整个程序会停止。
    5. Scrapy Engine：scrapy引擎，负责信号和数据的传递，发号施令，起协调作用。
    6. Spider Middlewares（Spider中间件）：可以自定义request请求和过滤Response响应。
    7. Downloader Middlewares（下载中间件）：自定义下载组件（请求任务和响应结果都会经过下载中间件）代理中间件，cookies中间件，User-Agent中间件，selenium中间件。

    知识点：
    1. 熟悉scrapy的架构和运行流程。
    2. 熟悉scrapy shell和scrapy selectors的使用
    3. 使用scrapy进行网站爬取
        创建scrapy项目（scrapy startproject xxx）
        定义提取的结构化数据（Item类）
        编写爬取网站的spider并提取出结构化数据（xpath、正则等）

    中文学习网站：https://scrapy-chs.readthedocs.io/zh_CN/1.0/intro/overview.html

# 创建scrapy项目的步骤

    项目功能：抓取快代理网站前N页的代理ip信息。
    1. 创建scrapy工程
        >> scrapy startproject kuaidaili
    2. 写item.py文件，定义要提取的结构化数据
    3. 写爬虫文件：创建名称为kuaidaili的爬虫文件, 并限制在www.kuaidaili.com域下爬取
        >> cd kuaidaili/kuaidaili/spiders
        >> scrapy genspider myspider "kuaidaili.com"
            可能需要手动修改start_urls
            需要导入Item类
            查看网页源码，确定xpath（推荐安装Chrome的xpath helper）
            使用yield生成器，解析出item（递交给pipline处理）、产生后续的Request（递交给spider抓取）
    4. 写管道文件 pipeline.py
        所有item会共用一个管道，数据持久化和其他处理。
    5. 编写setting.py文件
        启动管道
        其他配置，如 爬虫协议、header、user-agent
        >> #不遵守爬虫协议
            ROBOTSTXT_OBEY = False
        >> #开启pipiline，进行结构化数据(Item类)的持久化
        >> #可以设置多个pipline依次处理，优先级0-1000，越小优先级越高，越优先处理。
            ITEM_PIPELINES = {
                'Teacher.pipelines.kuaidailiPipeline': 300,
            }
    6. 启动爬虫
        >> cd kuaidaili/kuaidaili/spiders
        >> scrapy crawl myspider(爬虫名称)

# robots协议

    也叫爬虫协议、机器人协议，通常写在服务器的robots.txt文件中，用来限定爬虫程序可以爬取的内容范围，告诉爬虫，本网站哪些目录下的网页不希望你进行爬取收录。在Scrapy启动后，会访问网站的robots.txt 文件，然后决定该网站的爬取范围。如果网站不希望我们爬取我们仍要访问，就将ROBOTSTXT_OBEY设置为False，不遵守爬虫协议。

# Item Pipeline

    当item在spider中被收集后，它将被传递到item pipeline，这些item pipeline组件按定义的顺序（优先级0-1000）处理item。基本应用有：
    验证item中某些字段；
    查重并丢弃（url请求去重在调度器里实现的，数据去重在管道实现）；
    爬取结果保存到文件或数据库等；

# xpath语法
    // TODO

# scrapy shell：模拟代码发送请求

    >> scrapy shell "https://www.baidu.com/"     # 启动scrapy shell
    >>> item_list = response.xpath("//a[@class='mnav']/text()").extract()
    >>> for i in item_list:
    >>>     print(i)
    >>> print(response.head)      # 响应头
    >>> print(response.body)      # 响应体

# selector响应器

    response.selector返回Selector对象然后调用以下函数，
    效果和response.xpath()这种快捷方式查询一样，基本方法有4个：
    xpath(): 传入xpath表达式，返回表达式对应的所有节点的selector list列表。
    css(): 传入css表达式，返回表达式对应的所有节点的selector list列表。
    extract(): 序列化该节点为unicode字符串的list。
    re(): 根据正则表达式提取，返回unicode字符串的list。

# spider

    spider类的功能：如何爬取数据（如是否跟进链接）、如何提取结构化的item。

# scrapy用于大批量的抓取静态页面,非常高效

问题：如何抓取动态页面？

# 图片抓取和分类

    参考： http://www.scrapyd.cn/example/175.html
    和"快代理项目"的区别：
    继承自ImagesPipeline管道，并重写父类的两个方法；
    在settings.py中设置图片的存取路径：IMAGES_STORE = "d:\imageData"
