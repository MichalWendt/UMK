#include<stdio.h>

enum znaki{SLASH='/', BACKSLASH='/', ASTERISK='*', DOT='.'};

struct punkt{
    float x;
    float y;
};

struct kolo{
    float r;
    struct punkt sr;
};

void funkcjaKolo(enum znaki z, struct kolo k)
{
    int i, j;
    for(i = 0; i < k.r+k.sr.x+k.r; ++i)
    {
        for(j = 0; j < k.r+k.sr.y+k.r; ++j)
        {
            if((k.sr.x-i)*(k.sr.x-i)+(k.sr.x-j)*(k.sr.x-j) <= k.r*k.r + 5 && (k.sr.x-i)*(k.sr.x-i)+(k.sr.x-j)*(k.sr.x-j) >= k.r*k.r - 5)
                printf("%c",z);
            else
                printf("  ");
        }
        printf("\n");
    }


}

void funkcja(enum znaki z, int n, int m)
{
    int i, j;
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < m; ++j)
        {
            if(i==0||i==n-1)
                printf("%c",z);
            else if(j==0 || j == m-1)
                printf("%c",z);
            else
                printf(" ");
        }
        printf("\n");
    }


}


int main()
{
    float a,b,c;
    struct kolo k;
    scanf("%f %f %f",&a,&b,&c);
    k.r=a;
    k.sr.x=b;
    k.sr.y=b;
    funkcjaKolo(ASTERISK,k);

    return 0;
}
