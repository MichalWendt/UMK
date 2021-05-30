#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a=7;
    if(a++>7){
        ++a;
    }
    printf("%d\n",a);

    int b = 7;
    if ((b == 0) && (++b == 8)){
        b = 0;
        }
    printf("b: %d\n",b);

    int c = 0;
    if ((++c) && (--c)){
            c = 12;
    }
     printf("c: %d\n",c);

    int d = 1;
    if ((d++) || (d == 123)){
            d = 12;
    }
    printf("d: %d\n",d);

    int e, f;
    f = e = 3;
    e++;
    e=e + 3;
    printf("e: %d f: %d\n",e, f);

    int g, h;
    g = (h = 3, h++, h + 3);
     printf("g: %d h: %d\n",g, h);

    return 0;
}
