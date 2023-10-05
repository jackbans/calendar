#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "calendar.h"

const char * months[] = {"Janvier", "Fevrier", "Mars", "Avril", "Mai",
"Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};
const char *week_days[]={"Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi","Dimanche"};

///b////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                          ///
///   input_day function is for getting user data corresponding to a date securely.          ///
///   the function ensure that the input date is a valid one.                                ///
///                                                                                          ///
///m////////////////////////////////////////////////////////////////////////////////////////////
int input_day (int* ptr_year, char*month, int*ptr_day)
{
    // month parameter should have at least 15 characters
    int valid_input = 0,valid_mth = 0;
    do
    {
        valid_input = valid_mth = 0;
        printf("\n Date (ex. 7 Aout 2015) : ");
        if((valid_input = scanf("%d %14s %d",ptr_day,month,ptr_year)) < 0)
            exit( EXIT_FAILURE );
        if(!(valid_input == 3))
            printf(" Date invalide !\n"
            " Evitez les caracteres accentues comme dans '7 Aout 2015'\n");
        else
            valid_mth = valid_month(month);
        if(!valid_mth)
            printf(" '%s' n'est pas un mois valide !\n"
            " Evitez les caracteres accentues comme dans '7 Aout 2015'\n",month);
        else if(!valid_date(*ptr_year,valid_mth,*ptr_day))
        {
            printf(" Date invalide !\n"
            " %d n'est pas present dans %s %d\n", *ptr_day, month,*ptr_year);
            valid_mth = 0;
        }
        while(getchar() != '\n')
            ;
    }
    while(!valid_mth);
    return valid_mth;
}
////////////////////////////////////////// END OF FUNCTION /////////////////////////////////////////

///m////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                              ///
///   input_month gets datas from the keyboard, that correspond to a month and a year, in the    ///
///   format of 'Month Year'. Only the year is specified in numeric.                             ///
///                                                                                              ///
///b////////////////////////////////////////////////////////////////////////////////////////////////
int input_month (int* ptr_year, char*month)
{
    // month parameter should have at least 15 characters
    int valid_input = 0,valid_mth = 0;
    do
    {
        valid_input = valid_mth = 0;
        printf("\n Calendrier du mois (ex. Aout 2015) : ");
        if((valid_input = scanf("%14s %d",month,ptr_year)) < 0)
            exit( EXIT_FAILURE );
        if(!(valid_input == 2))
            printf(" Donnees invalides !\n"
		" Evitez les caracteres accentues comme dans 'Aout 2015'\n");
        else
            valid_mth = valid_month(month);
        if(!valid_mth)
            printf(" '%s' n'est pas un mois valide !\n"
            " Evitez les caracteres accentues comme dans 'Aout 2015'\n",month);
        while(getchar() != '\n')
            ;
    }
    while(!valid_mth);
    return valid_mth;
}
///////////////////////////////////// THE END OF FUCTION //////////////////////////////////////

///m///////////////////////////////////////////////////////////////////////////////////////////
///                                                                                         ///
///   input_year is a helper function designed to safely get a numeric year from the user   ///
///   keyboard.                                                                             ///
///                                                                                         ///
///b///////////////////////////////////////////////////////////////////////////////////////////
void input_year(int * ptr_year)
{
    int valid = 0;
    do
    {
        printf("\n Calendrier de l'an : ");
        if((valid = scanf("%d",ptr_year)) < 0)
            exit( EXIT_FAILURE );
        if(!valid)
            printf(" Donnee invalide ! Entrer une annee en numerique !\n");
        while(getchar() != '\n')
            ;
    }
    while(!valid);
}
//////////////////////////////////////// END OF THE FUNCTION //////////////////////////////

///b///////////////////////////////////////////////////////////////////////////////////////
///                                                                                     ///
///    Function name: month_size(year,month)                                            ///
///                                                                                     ///
///    Utility:                                                                         ///
///            This function gives the number of days of the month received as          ///
///            the 2nd paremeter. month should be from the range [1,12]. The year       ///
///            parameter is there because of February. Use any year value for others    ///
///            months.                                                                  ///
///    Warnings:                                                                        ///
///           - leap years has their Frebruary month days number at 29 instead of the   ///
///             usual 28.                                                               ///
///           - In Gregorian Calendar a leap year is a year that is divisible by 4,     ///
///             but centuries that are not divisible by 400 are excluded.               ///
///                                                                                     ///
///m///////////////////////////////////////////////////////////////////////////////////////
int month_size(const int year, const int month)
{
    // a value of month < 1 or > 12 result in unexpeced return value
    if (month == 2)
        return (((year % 4 == 0) && (year % 100)) || !(year % 400)) ? 29 : 28;
    return (((month % 2) && (month < 8))||((!(month % 2)) && (month > 7))) ? 31 : 30;
}
//////////////////////////////////////// END OF THE FUNCTION //////////////////////////////

///b/////////////////////////////////////////////////////////////////////////////////////////
///                                                                                       ///
///   function name : print_calendar_on                                                   ///
///   This overload of the function print_calendar_on, uses the other to print the        ///
///   gregorian calendar of the given year, on the screen or to output it on a file.      ///
///                                                                                       ///
///m/////////////////////////////////////////////////////////////////////////////////////////
void print_calendar_on(FILE* output_stream, const int year)
{
    if(output_stream != stdout)
        fprintf(output_stream,"\n Calendrier de l'an %d\n\n",year);
    for (int current_month = 1; current_month < 13; current_month++)
        print_month_calendar_on(output_stream,year,current_month);
    fprintf(output_stream,"\n");
}
//////////////////////////////////////// END OF THE FUNCTION //////////////////////////////

///b/////////////////////////////////////////////////////////////////////////////////////////
///                                                                                       ///
///   function name : print_calendar_on                                                   ///
///   This overload of the function print_calendar_on, prints the gregorian calendar      ///
///   of the specified month for the given year, on the screen or outputs it on a file.   ///
///                                                                                       ///
///   /!\  This function was renamed print_month_calendar_on due to the lake of           ///
///        functions overloading in c langage.                                            ///
///                                                                                       ///
///m/////////////////////////////////////////////////////////////////////////////////////////
void print_month_calendar_on(FILE* output_stream, const int year, const int month)
{
    const int wk_days_b4_z_1st = week_days_before_month(year,month);
    const int month_days = month_size(year,month);
    fprintf(output_stream,"\n  %s %d\n\n",months[month-1],year);
    int i = 0;
    for (i = 0; i < 7; i++) fprintf(output_stream,"%3.1s",week_days[i]);
    fprintf(output_stream,"\n");
    for (i = 0; i < wk_days_b4_z_1st; i++) fprintf(output_stream,"%3.1s"," ");
    char day[3];
    for (i = 1; i <= month_days; i++)
    {
        do {
            sprintf(day,"%2d",i);
            fprintf(output_stream,"%3.2s", day);
            i++;
        }while((wk_days_b4_z_1st + i - 1) % 7 && !(i > month_days));
        i--;
        fprintf(output_stream,"\n");
    }
    fprintf(output_stream,"\n");
}
//////////////////////////////////////// END OF THE FUNCTION ///////////////////////////////////////

///m/////////////////////////////////////////////////////////////////////////////////////////
///                                                                                      ////
///       Utility:                                                                       ////
///               the valid_date function return True if the date given by the user is   ////
///               valid in the Gregorian Calendar. Otherwise its return False.           ////
///       Example:                                                                       ////
///              valid_date(1900,2,29) return 0 (False).                                 ////
///                                                                                      ////
///b/////////////////////////////////////////////////////////////////////////////////////////
int valid_date(const int year, const int month, const int day)
{
    return (day>0)&&(day<=month_size(year,month));
}
//////////////////////////////////////////// = FIN = /////////////////////////////////////////

///b/////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                   ///
///    valid_month check if the characters string m is a valid month name and return a numeric month  ///
///    from [1,12] corresponding to m. Otherwise, it return 0 for invalid month.                      ///
///    Note. - If m is october, 10 will be returned                                                   ///
///            vie courante.                                                                          ///
///          - m's characters shouldn't have accents.                                                 ///
///          - Do not care about character casse. Ex. m="AoUT" still return 8.                        ///
///                                                                                                   ///
///m/////////////////////////////////////////////////////////////////////////////////////////////////////
int valid_month(char*m)
{
    int i;
    for (i=0;i<strlen(m);i++)m[i]=(i!=0)?tolower(m[i]):toupper(m[i]);
    for (i=0;i<12;i++) if (strcmp(months[i],m)==0) return (i+1);
    return 0;
}
/////////////////////////////////////////// END OF FONCTION //////////////////////////////////////////////

///b///////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                             ///
///     Function name : week_day_for(year,month,day)                                            ///
///                                                                                             ///
///     Given a date from the Gregorian calendar, the function week_day_for tells what's        ///
///     its corresponding week day by returning the week day index in week_days array.          ///
///                                                                                             ///
///     This function could be an overload of 'week_days_before', because it does exactly       ///
///     the similar thing as week_days_before functions but for any date.                       ///
///                                                                                             ///
///     All this functions return the number of days the come before the concerned date in      ///
///     its week.                                                                               ///
///                                                                                             ///
///m///////////////////////////////////////////////////////////////////////////////////////////////
int week_day_for(const int year, const int month, const int day)
{
    if(!valid_date(year, month, day)) return -1;
    return (day - 1 + week_days_before_month(year, month)) % 7;
}
////////////////////////////////////////// END OF FUNCTION /////////////////////////////////////////////

///b//////////////////////////////////////////////////////////////////////////////////////////
///                                                                                        ///
///       Function name : week_days_before(year)                                           ///
///                                                                                        ///
///       For a given numeric year this function return the number of days in the same     ///
///       week as January 1st and that come before. (Gregorian Calendar)                   ///
///                                                                                        ///
///m//////////////////////////////////////////////////////////////////////////////////////////
int week_days_before(const int year)
{
    // Year 1900 is our reference point because we count years from 1900 upward or downward.
    // We choose it because its days starts on Monday.

    // in a range notation like [1900, year[ the symbol [ before a number means that the number is
    // included in the range but placed at after it, it means the exclusion of number.
    // it goes inversely for the symbol ] in a range notation (exclusion before /
    // inclusion after).

    // years in the range [1900, year[ if year >= 1900
    // otherwise
    // years in the range [year,1900[
    const int years = (year >= 1900) ? year - 1900 : 1900 - year;

    // (if year >= 1900) we have the range [1900,year[
    // by convention a century is a year which ends with at minimum two zeros.
    // to count the year 1900 as a century we must add 100 to years
    // or nothing if year < 1900 because the year 1900 is then not in
    // the range [year,1900[
    // /!\ the century is given substracted by 1 because the 1st century
    // /!\ is already in the range [1900,year[
    const int century = (year >= 1900) ? 99 : 0;
    const int centuries = (years + century) / 100;

    // as precedently, we must add 4 to count 1900 as Julian Calendar leap year
    // Julian Calendar leap year are divisible by 4
    // Note that all centuries are valid leap year in the Julian Calendar
    // /!\ the quadrennial is given substracted by 1 because the 1st quadrennial
    // /!\ is already in the range [1900,year[
    const int quadrennial = (year >= 1900) ? 3 : 0;
    const int quadrennials = (years + quadrennial) / 4; // julian_leap_years

    // in gregorian calendar leap centuries are divisible by 400.
    // to extract centuries that are valid leap year in a gregorian calendar
    // from the range [1900, year[ or the range [year,1900[ we have to correctly
    // select the first leap century (of the concerned range) that is near the
    // reference point 1900, that is 200O for [1900, year[ or 1600 for [year,1900[.
    // to correctly do that selection we must add to years (400-(fist_leap_century
    // - 1900)) for the range [1900, year[ or (400-(1900-fist_leap_century))
    // for [year,1900[.
    // brief : 300 for the range [1900, year[ or 100 for [year,1900[
    // /!\ the values are given each substracted by 1 because the 1st leap century
    // /!\ is already in the range [1900,year[ or in the range [year,1900[
    // /!\ 100 is given unchanged to also count the year 1900 which is among the years
    // /!\ that make up the 1st gregorian leap century in the range [year,1900[
    const int leap_century = (year >= 1900) ? 299 : 100;
    const int leap_centuries = (years + leap_century) / 400; // gregorian_leap_centuries
    const int leap_years = quadrennials - (centuries - leap_centuries); // gregorian_leap_years

    // days before January the 1st of year
    const int days = leap_years * 366 + (years - leap_years) * 365;
    return (year >= 1900) ? days % 7 : (7-(days % 7)) % 7;
}
/*
Alternative implementation (expensive)

int week_days_before(int year)
{
    int days = 0, i;
    if (year >= 1900)
        for (i = year - 1; i >= 1900; i--)
            days += (((i % 4 == 0) && (i % 100)) || !(i % 400)) ? 366 : 365;
    else
        for (i = year; i < 1900; i++)
            days += (((i % 4 == 0) && (i % 100)) || !(i % 400)) ? 366 : 365;
    return (year >= 1900) ? days % 7 : (7-(days % 7)) % 7;
}
*/
//////////////////////////////////////// END OF THE FUNCTION //////////////////////////////

///b//////////////////////////////////////////////////////////////////////////////////////////
///                                                                                        ///
///       Function name : week_days_before(year,month)                                     ///
///                                                                                        ///
///       Do the same as week_days_before(year) but not only for January.                  ///
///                                                                                        ///
///       Given a numeric year and a numeric month from the range [1,12] this function     ///
///       return the number of days in the same week as the 1st of the given month and     ///
///       that come before it. (Gregorian Calendar)                                        ///
///                                                                                        ///
///       /!\  This function was renamed week_days_before_month due to the lake of         ///
///            functions overloading in c langage.                                         ///
///                                                                                        ///
///m//////////////////////////////////////////////////////////////////////////////////////////
int week_days_before_month(const int year, int month)
{
    // a value of month < 1 or > 12 result in unexpeced return value
    int days = week_days_before(year);
    if(month == 1) return days;
    month--;// remove the last month
    const int months_up_to_jully = (month >= 7) ? 7 : month;
    const int remained_months = (month >= 7) ? month - 7 : 0;
    // we added 1 (to months_up_to_jully and to remained_months), to also count the first month
    // of both months_up_to_jully and remained_months.
    const int months_of_31_days = (months_up_to_jully + 1) / 2 + (remained_months + 1) / 2;
    // we must substract 1 to not count february
    const int months_of_30_days = (month != 1) ? month - months_of_31_days - 1 : 0;
    days += months_of_31_days * 31 + months_of_30_days * 30;
    // add 29 for leap year otherwise add 28 (Gregorian Calendar)
    if (month > 1) days += (((year % 4 == 0) && (year % 100)) || !(year % 400)) ? 29 : 28;
    return days % 7;
}
/*
Alternative implementation (Almost as cheap as the previous but a bit expensive)

int week_days_before_month(const int year, const int month)
{
    // a value of month < 1 or > 12 result in unexpeced return value
    int days = week_days_before(year);
    if (month != 1)
        for (int i = 1;i < month; i++)
            days += month_size(year,i);
    return days % 7;
}
*/
//////////////////////////////////////// END OF THE FUNCTION //////////////////////////////

