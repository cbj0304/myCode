# -*- coding: utf-8 -*-
from datetime import datetime
from datetime import timedelta
from datetime import date
from dateutil.relativedelta import relativedelta
import calendar
import pytz
from pytz import timezone
import time

'''
datetime库
    timedelta: 时间差对象
    datetime: 时间对象

dateutil库
    第三方库安装 pip install python-dateutil
    处理较复杂的时间日期操作（时区， 模糊时间范围， 节假日等）

calendar库
    处理日历操作

pytz库
    第三方库安装 pip install pytz
    处理时区操作
    整个地球被划分为二十四时区，每个时区都有自己的本地时间。
    为统一而普遍使用一个标准时间，称为通用协调时UTC。
    北京时区是东八区，领先UTC 8个小时,标记为 Date: Sun, 13 June 2010 09:45:28 +0800。
    uct时间转北京时间： uct + 时区差 = 本地时间。

time模块
时间戳 timestamp
时间元组 struct_time
格式化时间 format_time

'''

if __name__ == '__main__':
    # datetime库
    a1 = timedelta(days=2, hours=6)
    a2 = timedelta(hours=4)
    a3 = a1 + a2
    print('type(a)={}\na.seconds()={}\na.days()={}\na.total_seconds()={}\n'.format(
        type(a3),
        a3.seconds,
        a3.days,
        a3.total_seconds()
    ))

    b1 = datetime(2019, 10, 13, 10, 16)
    print(b1 + timedelta(days=2, minutes=30))
    b2 = datetime(2019, 12, 12)
    b3 = b2 - b1
    print(b3.days)

    today = datetime.today()
    now = datetime.now()
    print('today={}, type={}\n now={}, type={}'.format(
        today,
        type(today),
        now,
        type(now)
    ))
    print('weekday=', b1.weekday())   # 星期几 取值是[0, 6]

    # 统计本月有多少天
    d = date.today().replace(day=1)  # 回归本月第一天
    print('first date of month={}, type={}'.format(d, type(d)))
    _, days_in_month = calendar.monthrange(d.year, d.month)
    # 打印日历
    print(calendar.prcal(2019))

    # dateutil库
    c1 = datetime(2019, 10, 18)
    print(c1 + relativedelta(months=+4))
    print(c1 + relativedelta(months=-2))

    print('next Tuesday=', c1 + relativedelta(weekday=1))   # 下一个星期二

    # 字符串转日期
    text = '2019-09-20'
    d1 = datetime.strptime(text, '%Y-%m-%d')
    print('d1={}, type={}'.format(d1, type(d1)))
    # 方法2
    year_, month_, day_ = text.split('-')
    d2 = datetime(int(year_), int(month_), int(day_))

    # 日期转字符串
    t = datetime.strftime(d1, '%Y %m %d %H:%M:%S')
    print('t={} type={}'.format(t, type(t)))

    # pytz (时区 timezone)
    e = datetime(2012, 12, 21, 9, 30, 0)
    # 时间本地化为芝加哥时间
    loc_d = timezone('US/Central').localize(e)
    # 本地化后的时间转换为其他时区的时间
    h_d = loc_d.astimezone(timezone('Asia/Hong_Kong'))
    print('l_d={}\nhd={}'.format(loc_d, h_d))  # hd=2012-12-21 23:30:00 +08:00   +08:00代表东八区

    # 为了避免不必要的错误，一般的做法是先将日期转为utc时间(0时区的标准时间)，
    # 所有时间操作完毕后再转为本地时间
    utc_d = loc_d.astimezone(pytz.utc)
    print('utcd=', utc_d)

    # 打印pytz库中的时区代码
    print(pytz.all_timezones)

    # time模块
    print(dir(time))
    t1 = time.time()  # 时间戳
    t2 = time.localtime()   # struct_time
    print('y={} m={} d={} h={} M={} S={} weekday={} nth_day_of_year={} 是否夏令时={}'.format(
        t2.tm_year, t2.tm_mon, t2.tm_mday,
        t2.tm_hour, t2.tm_min, t2.tm_sec,
        t2.tm_wday, t2.tm_yday, t2.tm_isdst
    ))

    t3 = time.mktime(t2)  # struct_time转时间戳

    t4 = time.strftime("%Y-%m-%d %X", t2)  # struct_time 转 字符串时间

    t5 = time.strptime('2011-05-05 16:37:06', '%Y-%m-%d %X')  # 字符串时间转struct_time

    t6 = time.ctime(time.time())  # 时间戳转可读字符串时间，如 Tue Feb 17 10:00:18 2013

    print('t1={}\nt2={}\nt3={}\nt4={}\nt5={}\nt6={}'.format(
        t1, t2, t3, t4, t5, t6
    ))
