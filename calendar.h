#include <stdio.h>
#ifndef CALENDAR_H
#define CALENDAR_H
int input_day (int* ptr_year, char*month, int*ptr_day);
int input_month (int* ptr_year, char*month);
void input_year(int * ptr_year);
int month_size(const int year, const int month);
void print_calendar_on(FILE* output_stream, const int year);
void print_month_calendar_on(FILE* output_stream, const int year, const int month);
int valid_date(const int year, const int month, const int day);
int valid_month(char*month_name);
int week_day_for(const int year, const int month, const int day);
int week_days_before(const int year);
int week_days_before_month(const int year, int month);
#endif
