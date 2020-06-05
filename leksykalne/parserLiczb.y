%{
    #include <stdio.h>
    #include <stdlib.h>
 
    int yyerror();
    int numExpressions = 0;
    
    
    
    int NWD(int a, int b)
	{
		if(b!=0)
			return NWD(b,a%b);
		
		return a;
	}
		
%}
 
 
%union {
  struct {
     int licznik;
     int mianownik;
  }t;
  int liczba
}
 
%token LICZBA WYMIERNA PLUS MINUS MNOZ DZIEL OTW ZAM SEPARATOR
 
%%
 
calosc :
    | calosc wiersz
    ;
 
wiersz : '\n'
    | wyrazenie '\n' { printf("wartosc = %d | %d\n",$<t.licznik>1 / NWD($<t.licznik>1 , $<t.mianownik>1 ), $<t.mianownik>1 / NWD($<t.licznik>1 , $<t.mianownik>1 )); ++numExpressions; }
 
wyrazenie : wyrazenie PLUS skladnik { $<t.licznik>$ = $<t.licznik>1 * $<t.mianownik>3 + $<t.licznik>3 * $<t.mianownik>1; $<t.mianownik>$ = ($<t.mianownik>3 *  $<t.mianownik>1);}
    | wyrazenie MINUS skladnik { $<t.licznik>$ = $<t.licznik>1 * $<t.mianownik>3 - $<t.licznik>3 * $<t.mianownik>1; $<t.mianownik>$ = ($<t.mianownik>3 *  $<t.mianownik>1);}
    | skladnik { $<t.licznik>$ = $<t.licznik>1; $<t.mianownik>$ = $<t.mianownik>1; }
    ;
 
skladnik : skladnik MNOZ ulamek { $<t.licznik>$ = ($<t.licznik>1 * $<t.licznik>3); $<t.mianownik>$ = ($<t.mianownik>3 *  $<t.mianownik>1);}
    | skladnik DZIEL ulamek { $<t.licznik>$ = ($<t.licznik>1 *  $<t.mianownik>3); $<t.mianownik>$ = ($<t.licznik>3 *  $<t.mianownik>1); }
    | ulamek
    ;
 
ulamek : liczba SEPARATOR liczba { $<t.licznik>$ = $<t.licznik>1; $<t.mianownik>$ = $<t.licznik>3;}
         | OTW wyrazenie ZAM { $<t.licznik>$ = $<t.licznik>2; $<t.mianownik>$ = $<t.mianownik>2;  }

liczba : WYMIERNA  { $<t.licznik>$ = $<t.licznik>1;}
	    | MINUS WYMIERNA { $<t.licznik>$ = -$<t.licznik>2;}
    ;
%%
 
int main(int argc, char* argv[]){
   
    yyparse();
    printf("\tPrzeczytano %d poprawnych wyrazen\n\n",numExpressions);
    return 0;
}
 
int yyerror(char *s) {
    printf("Blad: %s\n", s);
}
