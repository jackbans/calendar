#include <threads.h>
#include <stdio.h>
#include <stdlib.h>

#include "calendar.h"

extern const char*week_days[];
typedef struct
{
    int years_number;
    int step;
} Test_arg;
mtx_t output_mtx;
int is_the_next_day(const int day, const int next_day)
{
    if(day <= 6 && next_day >= 0)
        if(next_day - day == 1 || next_day - day == -6)
            return 1;
    return 0;
}
int test_year(int year, const int step)
{
    if((step != 1 && step != -1) || !step) return 1;
    int month, next_month = ((step < 0) ? 12 : 1), i = step * 12;
    int month_day,week_day,next_week_day;
    while(i)
    {
	month = (step < 0) ? 13 + i : i;
	month_day = month_size(year,month);
	if(step < 0)
	{
	    //swap
	    month ^= next_month;
	    next_month ^= month;
	    month ^= next_month;
	    month_day = month_size(year,month);
	    if(i == -12) year--;
	    else if (i == -11) year++;
	}
        week_day = week_day_for(year, month, month_day);
        next_week_day = week_day_for(abs(i) == 12 ? (year + 1) : year, next_month, 1);
        if(!is_the_next_day(week_day, next_week_day))
            goto error_exit;
        if(step == 1) next_month = month;
        i -= step;
    }
    if(step == 1) year--;
    i = 12;
    month = 12; next_month = 1; month_day = 31;
    week_day = week_day_for(year, 12, 31);
    next_week_day = week_day_for(year + 1, 1, 1);
    if(!is_the_next_day(week_day, next_week_day))
        goto error_exit;
    return 0;
    error_exit:
    mtx_lock(&output_mtx);
    fprintf(stderr,"Error : %s %02d/%02d/%d et %s %02d/%02d/%d ne se suivent pas !\n",
        week_days[week_day], month_day, month, year, week_days[next_week_day],
        1, next_month, abs(i) == 12 ? year + 1 : year);
    mtx_unlock(&output_mtx);
    return 1;
}
int test(int years_number, const int step)
{
    int rtn_value = 0, tmp = 0;
    if(years_number < 0) years_number = -years_number;
    if (!step) return 1;
    while(years_number)
    {
        tmp = test_year(1900 + years_number * step, (step < 0 ? -1 : 1));
        if(tmp) rtn_value = tmp;
        years_number--;
    }
    if(step > 0) tmp = test_year(1900, 1);
    if(tmp) rtn_value = tmp;
    return rtn_value;
}
int thread_test(void*args)
{
    Test_arg* arg = (Test_arg*) args;
    return test(arg->years_number, arg->step);
}
int main(int argc, char*argv[])
{
    Test_arg arg = {0,1};
    if(argc > 1)
    {
        if(sscanf(argv[1],"%d",&arg.years_number) != 1) return 1;
        if(argc > 2 && (sscanf(argv[2],"%d",&arg.step) != 1)) return 1;
    }
    else return 1;
    thrd_t th;
    int res = 0;
    int success = 0;
    if(!(success = (thrd_create(&th,thread_test,&arg) == thrd_success)))
        test(arg.years_number, arg.step);
    test(arg.years_number, -arg.step);
    if(success) thrd_join(th, &res);
    if(res) return res;
    return 0;
}
