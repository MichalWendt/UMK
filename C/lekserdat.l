%{
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
    char separator;
    int dzien;
    int miesiac;
    int rok;
    char NazwaMiesiaca[11];
    char nazwa_pliku[30];
    char* yytext;
    char* zamianamiesiaca(int m)
    {
        if(m == 1)
        {
            return "styczen";
        }
        if(m == 2)
        {
            return "luty";
        }
        if(m == 3)
        {
            return "marzec";
        }
        if(m == 4)
        {
            return "kwiecien";
        }
        if(m == 5)
        {
            return "maj";
        }
        if(m == 6)
        {
            return "czerwiec";
        }
        if(m == 7)
        {
            return "lipiec";
        }
        if(m == 8)
        {
            return "sierpien";
        }
        if(m == 9)
        {
            return "wrzesien";
        }
        if(m == 10)
        {
            return "pazdziernik";
        }
        if(m == 11)
        {
            return "listopad";
        }
        if(m == 12)
        {
            return "grudzien";
        }
    }
%}
 
wyra1_data {wyra_dzien}{wyra_separator}{wyra_miesiac}{wyra_separator}{wyra_rok}
 
wyra2_data {wyra_dzien}{wyra_separator}{wyra_MiesiacSlownie}{wyra_separator}{wyra_rok}

wyra_dzien ([0-2][0-9]|(3)[0-1]|[1-9])
 
wyra_miesiac (((0)[1-9])|((1)[0-2])|[1-9])
 
wyra_MiesiacSlownie ("styczen"|"luty"|"marzec"|"kwiecien"|"maj"|"czerwiec"|"lipiec"|"sierpien"|"wrzesien"|"pazdziernik"|"listopad"|"grudzien")
 
wyra_rok (([0-9][0-9][0-9][0-9])|([0-9][0-9]))

wyra_separator ("."|"-"|"/")
  
%%
 
{wyra1_data} {
    sscanf(yytext,"%d%[/.-]%d%[/.-]%d", &dzien, &separator, &miesiac, &separator, &rok);
    if(dzien > 10) {
        printf("%d-", dzien);
    }
    else {
        printf("0%d-", dzien);
    }
    printf("%s-", zamianamiesiaca(miesiac));
    if(rok % 100 > 10) {
        printf("%d", rok % 100);
    }
    else {
        printf("0%d", rok % 100);
    }
 }

{wyra2_data} {
    sscanf(yytext,"%d%[/.-]%[a-zA-Z]%[/.-]%d", &dzien, &separator, NazwaMiesiaca, &separator, &rok);
    if(dzien > 10) {
        printf("%d-", dzien);
    }
    else {
        printf("0%d-", dzien);
    }
    printf("%s-", NazwaMiesiaca);
    if(rok % 100 > 10) {
        printf("%d", rok % 100);
    }
    else {
        printf("0%d", rok % 100);
    }
 }

%%
 
 int main(int argc, char* argv[]) {
    printf("Prosze podac nazwe pliku z datami\n");
    scanf("%s", nazwa_pliku);
    strcat(nazwa_pliku,".txt");
    if((yyin=fopen(nazwa_pliku, "r")) == NULL)
    {
        printf ("Nie moge otworzyc pliku %s do odczytu\n",nazwa_pliku);
        exit(1);
    }
    else
    {
        yylex();
    }
    return 0;
 }
