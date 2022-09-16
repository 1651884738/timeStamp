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

    if((standardTime.Year < specialTime.Year) || (standardTime.Year > 2099))//不允许 specialTime.Year 之前的时间传进来
    {
        printf("This year %d is not supported\r\n",standardTime.Year);
        return -1;
    }

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
