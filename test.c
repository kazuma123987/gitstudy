#include <stdio.h>
#include <string.h>
struct date
{
    int day;
    int month;
    int year;
};
int is_leap_year(struct date d)
{
    int ret = 0;
    if ((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0)
        ret = 1;
    return ret;
}
int Month_days(struct date d)
{
    int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (is_leap_year(d))
        month_days[1] = 29;
    return month_days[d.month - 1];
}
void date_input(struct date *d)
{
    printf("请输入今天的日期（月/日/年）：\n");
    while (1)
    {
        scanf("%d%d%d", &d->month, &d->day, &d->year);
        if (d->day > Month_days(*d) || d->day <= 0)
        {
            printf("invalid day!\n");
            continue;
        }
        else if (d->month > 12 || d->month <= 0)
        {
            printf("invalid month!\n");
            continue;
        }
        else if (d->year < 0)
        {
            printf("invalid year!\n");
            continue;
        }
        break;
    }
}
int main()
{
    struct date today, tomorrow;
    date_input(&today);
    if (today.day < Month_days(today))
    {
        tomorrow.day = today.day + 1;
        tomorrow.month = today.month;
        tomorrow.year = today.year;
    }
    else if (today.month == 12)
    {
        tomorrow.day = 1;
        tomorrow.month = 1;
        tomorrow.year = today.year + 1;
    }
    else
    {
        tomorrow.day = 1;
        tomorrow.month = today.month + 1;
        tomorrow.year = today.year;
    }
    printf("明天的日期是:%d\\%d\\%d\n", tomorrow.month, tomorrow.day, tomorrow.year);
}