#include <stdio.h>
#include "time.h"
#include "string.h"
#include "stdlib.h"

typedef struct times
{
    int Year;
    int Mon;
    int Day;
    int Hour;
    int Min;
    int Second;
}Times;

int standard_to_stamp(char *str_time)
{
    struct tm stm;
    int iY,iM,iD,iH,iMin,iS;
    memset(&stm,0,sizeof(stm));
    iY = atoi(str_time);
    iM = atoi(str_time+5);     //和实际输入的格式 有关系
    iD = atoi(str_time+7);
    iH = atoi(str_time+10);
    iMin = atoi(str_time+13);
    iS = atoi(str_time+16);
    stm.tm_year=iY-1900;
    stm.tm_mon=iM-1;
    stm.tm_mday=iD;
    stm.tm_hour=iH;
    stm.tm_min=iMin;
    stm.tm_sec=iS;
    printf("\n", iY, iM, iD, iH, iMin, iS);

    return (int)mktime(&stm);

}

Times stamp_to_standard(int stampTime)
{
    time_t tick = (time_t)stampTime;
    struct tm tm;
    char s[100];
    Times standard;
    tm = *localtime(&tick);
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);
    printf("%d  %s\n", (int)tick, s);

    standard.Year = atoi(s);
    standard.Mon = atoi(s+5);
    standard.Day = atoi(s+8);
    standard.Hour = atoi(s+11);
    standard.Min = atoi(s+14);
    standard.Second = atoi(s+17);

    return standard;
}

enum TIME_DEF
{
    SEC = 1,
    MIN = SEC * 60,
    HOUR = MIN * 60,
    DAY = HOUR * 24,
    YEAR = DAY * 365,
};

time_t time_difference = 8 * HOUR;
static time_t mon_yday[2][12] =
        {
                {0,31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
                {0,31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335},
        };

int leap(int year) {
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
        return 1;
    }
    return 0;
}
long long get_day(int year) {
    year = year - 1;
    int leap_year_num = year / 4 - year / 100 + year / 400;
    long long tol_day = year * 365 + leap_year_num;
    return tol_day;
}
#if 1
time_t _mymktime(int year,int mon,int day,int hour,int min,int sec) {
    long long tol_day = 0;
    year += 1900;
    tol_day = get_day(year) - get_day(1970);
    tol_day += mon_yday[leap(year)][mon];
    tol_day += day - 1;

    long long ret = 0;
    ret += tol_day * DAY;
    ret += hour * HOUR;
    ret += min * MIN;
    ret += sec * SEC;

   return ret - time_difference;
   //return ret;
}
#endif

time_t mymktime(struct tm* mk) {
    if (!mk) {
        return -1;
    }
    if (!(mk->tm_sec>= 0 && mk->tm_sec <= 59)) {
        return -1;
    }
    if (!(mk->tm_min>= 0 && mk->tm_min <= 59)) {
        return -1;
    }
    if (!(mk->tm_hour>= 0 && mk->tm_hour <= 23)) {
        return -1;
    }
    if (!(mk->tm_mday>= 1 && mk->tm_hour <= 31)) {
        return -1;
    }
    if (!(mk->tm_mon>= 0 && mk->tm_mon <= 11)) {
        return -1;
    }
    if (!(mk->tm_year>= 70)) {
        return -1;
    }

    return _mymktime(mk->tm_year,mk->tm_mon,mk->tm_mday,mk->tm_hour,mk->tm_min,mk->tm_sec);
}


/**
 *
 *
 * */

typedef struct
{
    int 	year;
    int 	month;
    int 	day;
    int 	hour;
    int 	min;
    int 	sec;
    int 	ms;
}_clock;



void timToStamp(long long int *pStamp, _clock clock)
{
    static  int MON1[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	//平年
    static  int MON2[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	//闰年
    int *month = NULL;
    int leapYearCnt = 0;
    long long int days = 0;
    //获得1970年到当前年的前一年共有多少闰天
    for(int i = 1970; i < clock.year; i++)
    {
        if((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        {
            leapYearCnt++;
        }
    }
    days = leapYearCnt * 366 + (clock.year - 1970 -leapYearCnt) * 365;
    /*判断当前年是不是闰年*/
    if((clock.year % 4 == 0 && clock.year % 100 != 0) || (clock.year % 400 == 0))
    {
        month = MON2;
    }
    else
    {
        month = MON1;
    }

    for(int i = 0; i < clock.month - 1; i++)
    {
        days += month[i];
    }

    *pStamp = (days + clock.day-1) * 24 * 3600 * 1000 + clock.hour * 3600 * 1000 + clock.min * 60 * 1000 + clock.sec * 1000 + clock.ms - 8 * 3600 * 1000;
}

int main() {
    struct tm stamp;
    standard_to_stamp("2022-09-16 14:45:33");
    stamp_to_standard(1663310733);

    stamp.tm_year = 2022;
    stamp.tm_mon = 9;
    stamp.tm_mday = 16;
    stamp.tm_hour = 14;
    stamp.tm_min = 45;
    stamp.tm_sec = 33;
    int timeStamp  = (int)mymktime(&stamp);
    printf("%d\r\n",timeStamp);

    _clock clock;
    clock.year = 2022;
    clock.month = 9;
    clock.day = 16;
    clock.hour = 14;
    clock.min = 45;
    clock.sec = 33;
    clock.ms = 000;

    static long long int stampx = 0;
    timToStamp(&stampx, clock);
    printf("%ld\r\n", stampx);

    return 0;
}

/*******************************************************/

#define  SECONDS_IN_A_MINUTE   60
#define  SECONDS_IN_AN_HOUR    60 * SECONDS_IN_A_MINUTE
#define  SECONDS_IN_A_DAY      24 * SECONDS_IN_AN_HOUR

#define  SECONDS_IN_A_COMMON_YEAR   365 * SECONDS_IN_A_DAY
#define  SECONDS_IN_A_LEAP_YEAR     366 * SECONDS_IN_A_DAY

//从1970-01-01 08：00：00 起开始数秒
//定义一个起始时间戳 2022-01-01 00:00:00
#define  SPECIALTIMESTAMP       1640966400
typedef struct
{
    int Year;
    int Mon;
    int Day;
    int Hour;
    int Min;
    int Second;
}Date;

Date specialTime = {
        2022,
        01,
        01,
        00,
        00,
        00
};

//日期转时间戳
size_t Date2timeStamp(Date standardTime){
    //需要计算 传进来的 standardTime 比 specialTime 大多少秒
    size_t differenceValue = 0;     //定义这个差值，单位为秒
    int leapYears = 0;

    if(standardTime.Year < specialTime.Year)    //不允许 specialTime.Year 之前的时间传进来
        return -1;

    //从 specialTime 开始，到 standardTime 的前一年之间有过少个闰年
    for(int i = specialTime.Year; i < standardTime.Year; i++)
    {
        if((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        {
            leapYears++;
        }
    }
    //判读今年是不是闰年
    if((standardTime.Year % 4 == 0 && standardTime.Year % 100 != 0) || (standardTime.Year % 400 == 0))  //判断是否闰年
    {
        if(standardTime.Mon >= 2)
        {
            if(standardTime.Mon = 2)
            {

            }
        }
    }

}
