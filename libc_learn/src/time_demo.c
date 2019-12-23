#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
whatis time
man 2 time
(1) time：返回1970-1-1, 00:00:00以来经过的秒数（时间戳）。
#include <time.h>
time_t time(time_t *t);      // 成功返回秒数，失败返回-1
举例：结果可以通过参数或者返回值得到
time_t now;
time(&now);// 等同于now = time(NULL)
(2) localtime：将时间数值变换成本地时间，考虑到本地时区和夏令时标志;
#include <time.h>
struct tm *localtime(const time_t * calptr);
struct tm {
        int tm_sec;       // 秒 – 取值区间为[0,59]
        int tm_min;       // 分 - 取值区间为[0,59]
        int tm_hour;      // 时 - 取值区间为[0,23]
        int tm_mday;      // 一个月中的日期 - 取值区间为[1,31]
        int tm_mon;       // 月份（从一月开始，0代表一月） - 取值区间为[0,11]
        int tm_year;      // 年份，其值等于实际年份减去1900
        int tm_wday;      // 星期 – 取值区间为[0,6]，其中0代表星期天，1代表星期一
        int tm_yday;      // 从每年1月1日开始的天数– 取值区间[0,365]，其中0代表1月1日
        int tm_isdst;     // 夏令时标识符，夏令时tm_isdst为正；不实行夏令时tm_isdst为0
};
(3) 时间戳转格林威治标准时间，即未经时区转换的UTC时间。
struct tm *gmtime(long *clock);

(4) 结构体时间转时间戳
time_t mktime(strcut tm * timeptr);

(5) 将tm结构类型时间日期转换为ASCII码。
char *asctime(const struct tm *tblock);

(6) times: 获取进程及其子进程的时钟时间、用户cpu时间、系统cpu时间
#include <sys/times.h>
clock_t times(struct tms *buf);
struct tms {
    clock_t tms_utime;      // user time
    clock_t tms_stime;      // system time
    clock_t tms_cutime;     // user time of children
    clock_t tms_cstime;     // system time of children
};
int sc_clk_tck = sysconf(_SC_CLK_TCK); // 每秒时钟滴答数
返回的clock_t除以时钟滴答数，得到秒数。
*/

int main() {

    time_t t;
    struct tm *gmt, *area;
    t = time(NULL);              // 时间戳
    area = localtime(&t);        // 本地时间
    printf("Local time is: %s", asctime(area));         // Mon Nov 18 18:00:39 2019
    gmt = gmtime(&t);            // 格林威治时间（UTC时间）
    printf("GMT is: %s", asctime(gmt));                 // Mon Nov 18 10:00:39 2019

    // 转时间戳
    // 从公元1970年1月1日0时0分0 秒算起至今的UTC时间所经过的秒数。
    time_t t1 = mktime(area);
    time_t t2 = mktime(gmt);
    printf("t1=%ld t2=%ld", t1, t2);

    system("pause");
    return 0;
}