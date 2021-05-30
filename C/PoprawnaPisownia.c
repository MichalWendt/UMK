#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

int main()
{
    FILE *in;
    FILE *out;
    char a,b,c='a';
    int spc=0;
    in = fopen("bledny.txt","r");
    out = fopen("poprawiony.txt","w");
    if((a=getc(in))!= EOF){
        b=a;
        putc(toupper(a),out);
    }

    while((a=getc(in)) != EOF){
        printf("A: %c, B: %c, C: %c \n",a,b,c);


        if(a==' ' && b!=' '){

             c=b;
             b=a;
        }
        else if(c=='.' || c=='!' || c=='?'){

            c=b;
            b=a;
            putc(toupper(a),out);
        }
        else if(a==' ' && b==' '){

             b=a;
        }
        else{

            putc(tolower(a),out);
            c=b;
            b=a;
        }
    }
    close(in);
    close(out);

    return 0;
}
