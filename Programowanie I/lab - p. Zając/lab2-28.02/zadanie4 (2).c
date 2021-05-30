#include<stdio.h>
#include<stdlib.h>

int main(int argc, char ** argv)
{
    int i;
    int min=strtol(argv[1], NULL, 10);
    int max=strtol(argv[1], NULL, 10);
    for(i=2;i<argc;i++)
    {
        if(min>strtol(argv[i], NULL, 10)) min=strtol(argv[i], NULL, 10);
        if(max<strtol(argv[i], NULL, 10)) max=strtol(argv[i], NULL, 10);
    }
    printf("Min: %d Max:  %d", min, max);
    return 0;
}
