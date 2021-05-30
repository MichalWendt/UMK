#include <stdio.h>

int main(void){
    char *c, txt[] = "Paella!";
    c = &txt[1];
    while (2 == 2){
        if (*c-- == 'e')
            break;
    }
    printf("%s\n", c);
    return 0;
}
