#include <stdio.h>
#include <math.h>
#define M_PI acos(-1.0)

void wysokosc_podstawa() {
    int pole, a, h;
    printf("Podaj podstawe i wysokosc: ");
    scanf("%d %d", &a, &h);
    pole = a * h /2;

    printf("Pole = %d\n", pole);
}

void boki() {
    int pole, a, b, c, p;
    printf("Podaj dlugosci bokow: ");
    scanf("%d %d %d", &a, &b, &c);

    p = (a + b + c)/2;
    pole = sqrt( p * (p-a)*(p-b)*(p-c) );
    printf("Pole = %d\n", pole);

}

void boki_kat() {
    float pole, a, b, kat, radian, sinus;
    printf("Podaj boki i kat: ");
    scanf("%f %f %f", &a, &b, &kat);

    radian = kat * (M_PI / 180);
    sinus = sin(radian);
    pole = a * b / 2 * sinus;

    printf("Pole = %f\n", pole);
}

enum opcje {WYJSCIE, WYSOKOSC_PODSTAWA, BOKI, BOKI_KAT};

int main(int argc, char **argv) {

    enum opcje sposob;

    printf("Ktorym sposobem chcesz obliczyc pole? \n0 wyjscie \n1 wysokosc - podstawa\n2 boki \n3 boki kat\n");

    do {
        scanf("%d", &sposob);
        switch(sposob) {

            case WYSOKOSC_PODSTAWA:
                wysokosc_podstawa();
                break;

            case BOKI:
                boki();
                break;

            case BOKI_KAT:
                boki_kat();
                break;

            case WYJSCIE:
                break;
        }
    } while(sposob != 0);


}
