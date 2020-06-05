%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "y.tab.h"
%}
 
digit           [0-9]
digits          {digit}+
plus            "+"
minus           "-"
mnoz            "*"
dziel           "/"
nawias_l        "("
nawias_p        ")"
separtor        "|"
numer           {digits}
%%
 
{numer}		    { yylval.liczba = strtol(yytext,NULL,10); return WYMIERNA;}
{separtor}      { return SEPARATOR; }
{plus}          { return PLUS; }
{minus}         { return MINUS; }
{mnoz}          { return MNOZ; }
{dziel}         { return DZIEL; }
{nawias_l}      { return OTW; }
{nawias_p}      { return ZAM; }
\n              { return yytext[0]; }
.               { /* pomijaj niedopasowane znaki */ }
%%
