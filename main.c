#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "calendar.h"

///b////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                          ///
///   exec_calendar is the main interface for the user. it offers many choices. You can get  ///
///   the calendar of the year you gave, on the screen and in a file. You even have the      ///
///   possibility to get the calendar of an isolate month, to know the week day of an old    ///
///   date (Perhaps your Birthday).                                                          ///
///                                                                                          ///
///m////////////////////////////////////////////////////////////////////////////////////////////
int exec_calendar(void)
{
    char c;
    printf("\n\n\n                  ======================\n");
    printf("                 || SERIVES CALENDRIER ||\n");
    printf("                  ======================\n\n");
    printf("\n                       VOUS POUVEZ : \n                       ===========\n\n");
    printf("   1. OBTENIR LE CALENDRIER D'UNE ANNEE DE VOTRE CHOIX.\n");
    printf("   2. OBTENIR LE CALENDRIER DU MOIS DE VOTRE CHOIX.\n");
    printf("   3. SAVOIR QUEL JOUR DE LA SEMAINE VOUS ETES NE(E).\n");
    printf("   4. AUTRE CHOSE POUR NE RIEN FAIRE.\n\n");
    printf(" Votre choix : ");
    c = tolower(getchar());
    while(c!='\n' && getchar()!='\n')
	    ;
    int year;
    char filename[45];filename[44] = '\0';
    FILE *output_stream;
    char month[15]; month[14] = '\0';
    int month_num;

    switch(c)
    {
    case '1':
        input_year(&year);
        print_calendar_on(stdout,year);
        // Comment the code bellow if you don't want to write the output to a file on
        // the hard disk. Don't comment the break statement.
        sprintf(filename,"year_%d.txt",year);
        output_stream = fopen(filename,"wt");
        if(output_stream == NULL) return 1;
        print_calendar_on(output_stream,year);
        fclose(output_stream);
        printf("Le fichier %s a ete cree.\n\n", filename);
        break;
    case '2':
        month_num = input_month(&year,month);
        print_month_calendar_on(stdout,year,month_num);
        // Comment the code bellow if you don't want to write the output to a file of
        // the hard disk. Don't comment the break statement.
        sprintf(filename,"%s_%d.txt",month,year);
        output_stream = fopen(filename,"wt");
        if(output_stream == NULL) return 1;
        print_month_calendar_on(output_stream,year,month_num);
        fclose(output_stream);
        printf("Le fichier %s a ete cree.\n\n", filename);
        break;
    case '3':
        extern const char *week_days[];
        int day;
        month_num = input_day(&year,month,&day);
        const int week_day = week_day_for(year,month_num,day);
        if(week_day != -1)
            printf("\n\n Le %d/%s/%d est un %s.\n\n",day,month,year,week_days[week_day]);
        break;
    default :
        break;
    }
    return 0;
}
////////////////////////////////////////// END OF FUNCTION /////////////////////////////////////////

///b////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                          ///
///   The main_parameters_handler function is a main function helper that gives to the user  ///
///   the possibility to supply needed data on the command line as program parameters.       ///
///                                                                                          ///
///   The program generates calendars for any numeric year or for a single month of the      ///
///   year you supply. It even outputs the week day for any date you give it.                ///
///                                                                                          ///
///   See the comment section of the main function to know how to supply program             ///
///   parameters.                                                                            ///
///                                                                                          ///
///m////////////////////////////////////////////////////////////////////////////////////////////
int main_parameters_handler(int argc, char *argv[])
{
    if (argc > 1)
    {
        int year;
        char filename[45];filename[44] = '\0';
        FILE *output_stream;
        extern const char *week_days[];
        extern const char *months[];
        argc = argc > 4 ? 4 : argc;
        int succeed = (sscanf(argv[argc-1],"%d",&year) == 1);
        if (succeed && argc > 2)
        {
                int month_num;
            if(((month_num = valid_month(argv[argc-2]))||
                    sscanf(argv[argc-2],"%d",&month_num)==1) && argc > 3)
            {
                int day;
                if (month_num < 0 || month_num > 12) month_num = 0;
                if(sscanf(argv[argc-3],"%d",&day) == 1)
                {
                    if(valid_date(year,month_num,day))
                    {
                            const int week_day = week_day_for(year,month_num,day);
                        printf("\n Le %d/%s/%d est un %s.\n\n",day,months[month_num - 1],year,week_days[week_day]);
                        return 0;
                        }
                    printf("\n Le %d %s %d n'est pas une date valide !\n",day,argv[argc-2],year);
                    printf(" Evitez les caracteres accentues !\n\n");
                }
                return 1;
            }
            if (month_num < 0 || month_num > 12) month_num = 0;
            if(month_num)
            {
                print_month_calendar_on(stdout,year,month_num);
                // Comment the code bellow if you don't want to write the output to a file of
                // the hard disk. Don't comment the break statement.
                sprintf(filename,"%s_%d.txt",months[month_num - 1],year);
                output_stream = fopen(filename,"wt");
                if(output_stream == NULL) return 1;
                print_month_calendar_on(output_stream,year,month_num);
                fclose(output_stream);
                printf("Le fichier %s a ete cree.\n\n", filename);
                return 0;
            }
            printf("\n %s n'est pas un mois valide !\n",argv[argc-2]);
            printf(" Evitez les caracteres accentues !\n\n");
            return 1;
        }
        if(!succeed)
        {
            printf("\n %s n'est pas une annee numerique valide !\n\n",argv[argc-1]);
            return 1;
        }
        print_calendar_on(stdout,year);
        // Comment the code bellow if you don't want to write the output to a file on
        // the hard disk. Don't comment the break statement.
        sprintf(filename,"year_%d.txt",year);
        output_stream = fopen(filename,"wt");
        if(output_stream == NULL) return 1;
        print_calendar_on(output_stream,year);
        fclose(output_stream);
        printf("Le fichier %s a ete cree.\n\n", filename);
        return 0;
    }
    return 1;
}
////////////////////////////////////////// END OF FUNCTION /////////////////////////////////////////

///b///////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                             ///
///   If you want to execute the program in the interactive mode, do not supply any parameter.  ///
///                                                                                             ///
///   The year is always supplied while using no interactive mode. It can even be supplied as   ///
////  the unique parameter. You have to always supply  it in numeric, in the last position.     ///
///   The month has to be supplied just before the year, in letters, using french language.     ///
///   You have to supply months without accents (e.g. Fevrier 2015).                            ///
///   You can even supply a complete date (e.g. 7 Aout 1996) to know its week day.              ///
///                                                                                             ///
///   You can also supply the month in numeric (Only in no interactive mode). Equivalents of    ///
///   the previous examples are (e.g. 2 2015) and (e.g. 7 8 1996).                              ///
///                                                                                             ///
///m///////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char*argv[])
{
    if (argc > 1)
        return main_parameters_handler(argc,argv);
    char c;
    do{
        c = 'x';
        exec_calendar();
        printf("\n Tapez r pour RETOURNER au menu precedant, AUTRE CHOSE pour QUITTER : ");
        c = tolower(getchar());
        while(c!='\n' && getchar()!='\n')
	        ;
        if (c != 'r') break;
    }while (1);
    return 0;
}
/////////////////////////////////////////////// = END = //////////////////////////////////////////

