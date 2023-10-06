# calendar
calendar is a small console app that provide
gregorian calendar for any year or
month you supply. You can even get the week
day for any date you supply to the program.

this app sources are provided here for
learning purpose, and aim the beginner
programmer.

the app can be used in interactive mode but
you can avoid that by supplying arguments:

app 2023
app 8 2023
app 17 8 2023

the year is always supplied the last.
if supplied, the month is always near the
year. you can also supply the month in
french but without accents :

app Aout 2023

numeric month support isn't supplied in 
interactive mode, you must give the month
in french without accents.

there is a test module that verify if the
days in the gregorian calendar follow each
other correctly.

testapp 60000

will test the integrity of 120001, 60000
upward and 60000 downward the 1900, and
the year 1900 itself.

/!\ the test module also contain a main
    function.
