#include <cmath>
#include <QTime>
#include <unistd.h>
#include <QDateTime>
#include <QKeyEvent>
#include "mywindow.h"
#include "ui_mywindow.h"

static int szerokosc = 501;
static int wysokosc = 501;
static int Widz = 500;

MyWindow::MyWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MyWindow)   //konstruktor okna aplikacji
{
    ui->setupUi(this);
    timer = new QTimer(this);   //timer klay QTimer
    connect(timer,SIGNAL(timeout()),this,SLOT(funkcjazegar())); //połączenie timera z funckją
    timer ->start(1000);    //uruchomienie timera z odstępem jeden sekundy
    szer = ui->rysujFrame->width(); //ustawienie szerokości i wysokości okna rysunku
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();    //określenie początkowych współrzędnych
    poczY = ui->rysujFrame->y();
    img = new QImage(szer,wys,QImage::Format_RGB32);
    czysc();        //funkcja czysząca obraz
    rysowanie();    //funkcja tworząca i nakładająca obiekty na scene
}

MyWindow::~MyWindow()   //destruktor okna oplikacji
{
    delete ui;
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}

void MyWindow::czysc()  //funckja czyszcząca obraz (wybielająca pixele)
{
    unsigned char *ptr;
    ptr = img->bits();
    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
}

int minZtrzech(int a, int b, int c)   //pomocnicza funkcja licząca minimum trzech zmiennych
{
    if(a < b && a < c) return a;
    if(b < c) return b;
    return c;
}

int maksZtrzech(int a, int b, int c)   //pomocnicza funkcja licząca maksimum trzech zmiennych
{
    if(a > b && a > c) return a;
    if(b > c) return b;
    return c;
}

struct Color    //struktura określająca kolor danego punktu
{
    double R,G,B;   //zmienna czerwona, zielona, niebieska
    Color() : R(0), G(0), B(0) {}  //konsutruktor wyzerowany (czarny kolor)
    Color(double value) : R(value), G(value), B(value) {}  //konstruktor z pojedynczą wartością
    Color(double red, double green, double blue) : R(red), G(green), B(blue) {}    //konstruktor z różnymi wartościami
    Color operator + (Color kolor) { return Color(R+kolor.R,G+kolor.G,B+kolor.B); }   //operatory dodawania i mnożenia kolorów przez liczbę
    Color operator * (Color kolor) { return Color(R*kolor.R,G*kolor.G,B*kolor.B); }
    double getBlue() { return min(1.0,B)*255; }  //zwracanie obliczonej wartości niebieskiej, zielonej, czerwonej
    double getGreen() { return min(1.0,G)*255; }
    double getRed() { return min(1.0,R)*255; }
};

void rysujPiksel(int x, int y, Color kolor, unsigned char *ptr)    //funckja ustawiająca kolor piksela
{
    if(x >= 0 && y >= 0 && x < szerokosc && y < wysokosc) //sprawdzamy czy piksel znajduję się w obszarze ramki
    {
        ptr[szerokosc * 4 * y + 4 * x] = static_cast<unsigned char>(kolor.getBlue());   //ustawiamy konkretne kolor rzutowane na chara
        ptr[szerokosc * 4 * y + 4 * x + 1] = static_cast<unsigned char>(kolor.getGreen());
        ptr[szerokosc * 4 * y + 4 * x + 2] = static_cast<unsigned char>(kolor.getRed());
    }
}

struct Vector2D  //struktura wektora dwóch zmiennych
{
    double x,y; //dwie wspołrzędne wektora 2D
    Vector2D() : x(0), y(0) {}   //konstruktor wektora "pustego"
    Vector2D(double x, double y) : x(x), y(y) {} //konstruktor dwóch zmiennych
};

struct Vector3D  //struktura wektora trzech zmiennych
{
    double x,y,z;   //trzy wspołrzędne wektora 3D
    double dlugosc() const { return sqrt(x*x + y*y + z*z); }    //obliczanie długości wektora w 3D
    bool operator == (const Vector3D & v) const { return x - v.x == 0.0 && y - v.y == 0.0 && z - v.z == 0.0; }
    Vector3D() : x(0), y(0), z(0) {} //konstruktor wektora "pustego"
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {} //konstruktor trzech zmiennych
    Vector3D operator + (const Vector3D & v) const { return Vector3D(x+v.x, y+v.y, z+v.z); } //operatory dodawania, odejmowania, mnożenia i dzielenia wektora przez liczbę
    Vector3D operator - (const Vector3D & v) const { return Vector3D(x-v.x, y-v.y, z-v.z); }
    Vector3D operator * (double liczba) const { return Vector3D(x*liczba, y*liczba, z*liczba); }
    Vector3D operator / (double liczba) const { return Vector3D(x/liczba, y/liczba, z/liczba); }
    Vector3D normalize() const { double dl = dlugosc(); return Vector3D(x/dl,y/dl,z/dl); }  //normalizacja wektora (sprowadzanie dlugosci do 1)
    Vector3D cross(Vector3D v) { return Vector3D((y * v.z) - (z * v.y),(z * v.x) - (x * v.z),(x * v.y) - (y * v.x)); }  //iloczyn wektorowy
    Vector2D toVector2D(int Dwidza) const   //rzutowanie wektora 3D na 2D
    {
        double pom = 1.0 - z / Dwidza;  //obliczenie wartości zmiany wektora osi OZ
        if(pom == 0.0)pom = 0.0001;     //unikanie wartości zero
        return Vector2D(static_cast<int>(x / pom),static_cast<int>(y / pom));   //zwracamy wektor 2D
    }
    void skalowanieOX(double value){ x *= value; }   //funkcja skalowania wektora w osi OX
    void skalowanieOY(double value){ y *= value; }   //funkcja skalowania wektora w osi OY
    void skalowanieOZ(double value){ z *= value; }   //funkcja skalowania wektora w osi OZ
    void obrotOX(double value) //funkcja obrotu wektora w osi OX
    {
        const double kat = M_PI * (value / 180.0);  //przeliczanie kąta na radiany
        const double pomY = cos(kat) * y - sin(kat) * z, pomZ = cos(kat) * z + sin(kat) * y;    //obliczanie nowych współrzędnych po obrocie
        z = pomZ; y = pomY;
    }
    void obrotOY(double value) //funkcja obrotu wektora w osi OY
    {
        const double kat = M_PI * (value / 180.0);  //przeliczanie kąta na radiany
        const double pomZ = cos(kat) * z - sin(kat) * x, pomX = cos(kat) * x + sin(kat) * z;    //obliczanie nowych współrzędnych po obrocie
        z = pomZ; x = pomX;
    }
    void obrotOZ(double value) //funkcja obrotu wektora w osi OZ
    {
        const double kat = M_PI * (value / 180.0);  //przeliczanie kąta na radiany
        const double pomX = cos(kat) * x - sin(kat) * y, pomY = cos(kat) * y + sin(kat) * x;    //obliczanie nowych współrzędnych po obrocie
        x = pomX; y = pomY;
    }
};

static Vector3D gracz(0,0,500);  //wektor naszej pozycji (widza)
static Vector3D swiatlo(0,0,500);   //wektor pozycji światła

struct Light    //struktura opisująca światło
{
    Vector3D pozycja;  //wektor opisujący pozycje światła
    Color saturacja;   //kolor oświetlonego punktu(w zależności od nasilenia światła)
    Light(Vector3D pozycja, Color saturacja = Color(1,1,1)) : pozycja(pozycja) , saturacja(saturacja) {}  //konstruktor przyjmujący pozycje oraz kolor
};

int** triangleValue(Vector3D normalny1, Vector3D normalny2, Vector3D *normalnylewa, Vector3D *normalnyprawa, Vector3D punktlewy, Vector3D punktprawy,
                    Vector3D *zbiorlewych, Vector3D *zbiorprawych, int **tab, int Xpoczatku, int Ypoczatku, int Xkonca, int Ykonca)
{
    /* normalny1 = wektor normalny
     * normalny2 = wektor normalny
     * normalnylewa = zbior wektorow normalnych lewej krawedzi
     * normalnyprawa = zbior wektorow normalnych prawej krawedzi
     * punktlewy = lewy punk na krawedzi w R3
     * punktprawy = lewy punk na krawedzi w R3
     * zbiorlewych = zbior punktow w R3 lewej krawedzi
     * zbiorprawych = zbior punktow w R3 lewej krawedzi
    */
    int pom, i; //zmienne pomocnicze
    double a, b;    //zmienne prostej
    if(abs(Ypoczatku - Ykonca) > abs(Xpoczatku - Xkonca)) //jezeli bok jest wyzszy niz szerszy
    {
        if(Ypoczatku > Ykonca)   //zamiana wspolzendnych aby poczatkowe byly mniejsze
        {
            swap(punktlewy,punktprawy);
            swap(normalny1, normalny2);
            swap(Xpoczatku,Xkonca);
            swap(Ypoczatku,Ykonca);
        }
        a = (Xkonca - Xpoczatku) / static_cast<double>(Ykonca - Ypoczatku);   //obliczanie współczynnik nachylenia
        b = Xpoczatku - a * Ypoczatku;    //obliczanie wartości wolnej
        for(i = max(0,Ypoczatku); i <= min(wysokosc-1,Ykonca); i++)  //iterujemy po wysokości pikseli
        {
            pom = static_cast<int>(a * i + b);  //obliczanie punktu na prostej w 2D
            if(pom < tab[i][0]) //jezeli punkt prostej znajduje się w obszarze lewej krawędzi
            {
                tab[i][0] = pom;    //zapisujemy go do tablicy
                normalnylewa[i] = normalny1 - (normalny1 - normalny2) * (static_cast<double>(Ypoczatku - i) / static_cast<double>(Ypoczatku - Ykonca));  //wektor normalny lewej krawędzi
                zbiorlewych[i] = punktlewy - (punktlewy - punktprawy) * (static_cast<double>(Ypoczatku - i) / static_cast<double>(Ypoczatku - Ykonca));   //wektor w R3 z lewej krawędzi
            }
            if(pom > tab[i][1]) //blizej prawej krawędzi (ale nie przekracza)
            {
                tab[i][1] = pom;    //zapisujemy go do tablicy
                normalnyprawa[i] = normalny1 - (normalny1 - normalny2) * (static_cast<double>(Ypoczatku - i) / static_cast<double>(Ypoczatku - Ykonca));    //wektor normalny prawej krawędzi
                zbiorprawych[i] = punktlewy - (punktlewy - punktprawy) * (static_cast<double>(Ypoczatku - i) / static_cast<double>(Ypoczatku - Ykonca));    //wektor w R3 z prawej krawędzi
            }
        }
    }
    else    //jezeli bok jest szerszy niz wyzszy
    {
        if(Xpoczatku > Xkonca)   //zamiana wspolzendnych aby poczatkowe byly mniejsze
        {
            swap(Xpoczatku,Xkonca);
            swap(Ypoczatku,Ykonca);
            swap(normalny1, normalny2);
            swap(punktlewy,punktprawy);
        }
        a = (Ykonca - Ypoczatku) / static_cast<double>(Xkonca - Xpoczatku); //obliczanie współczynnik nachylenia
        b = Ypoczatku - a * Xpoczatku;  //obliczanie wartości wolnej
        for(i = Xpoczatku; i <= Xkonca; i++)  //iterujemy po szerokości pikseli
        {
            pom = static_cast<int>(a * i + b);  //obliczanie punktu na prostej w 2D
            if(pom < 0 || pom >= wysokosc)continue;
            if(i < tab[pom][0]) //jezeli punkt prostej znajduje się w obszarze lewej krawędzi
            {
                tab[pom][0] = i;    //zapisujemy go do tablicy
                normalnylewa[pom] = normalny1 - (normalny1 - normalny2) * (static_cast<double>(Xpoczatku - i) / static_cast<double>(Xpoczatku - Xkonca));   //wektor normalny lewej krawędzi
                zbiorlewych[pom] = punktlewy - (punktlewy - punktprawy) * (static_cast<double>(Xpoczatku - i) / static_cast<double>(Xpoczatku - Xkonca));   //wektor w R3 z lewej krawędzi
            }
            if(i > tab[pom][1]) //blizej prawej krawędzi (ale nie przekracza)
            {
                tab[pom][1] = i;    //zapisujemy go do tablicy
                normalnyprawa[pom] = normalny1 - (normalny1 - normalny2) * (static_cast<double>(Xpoczatku - i) / static_cast<double>(Xpoczatku - Xkonca));  //wektor normalny prawej krawędzi
                zbiorprawych[pom] = punktlewy - (punktlewy - punktprawy) * (static_cast<double>(Xpoczatku - i) / static_cast<double>(Xpoczatku - Xkonca));  //wektor w R3 z prawej krawędzi
            }
        }
    }
    return tab; //zwracamy dwuwymiarową tablice wspolrzednych boków trójkąta
}

inline double scalar(const Vector3D & a, const Vector3D & b){return (a.x * b.x + a.y * b.y + a.z * b.z);}   //funckja obliczająca wektor skalarną

struct Trojkat //struktura opisująca jeden trójkąt sfery
{
    Vector3D A, B, C;   //trzy wektory opisujące wierzchołki trójkata
    Vector3D NormA,NormB,NormC;  //trzy wektory normalne dla wierzcholkow
    Color kolor;    //kolor trójkąta
    Trojkat() {}   //konstruktor pusty
    Trojkat(Vector3D A, Vector3D B, Vector3D C, Color kolor) : A(A), B(B), C(C), kolor(kolor) {}  //konstruktor do zamalowania powierzchni trojkata
    Trojkat operator + (Vector3D move){return Trojkat(A + move, B + move, C + move, kolor);}    //operatory dodawania wartości przesunięcia do trójkąta
    Trojkat operator += (Vector3D move){return Trojkat(A + move, B + move, C + move, kolor);}
    void setNormal(Vector3D NA, Vector3D NB, Vector3D NC) { NormA = NA; NormB = NB; NormC = NC; } //normalizacja wektorów trójkąta (sprowadzanie dlugosci boków do 1)
    void skalowanieOX(double value) {A.skalowanieOX(value);B.skalowanieOX(value);C.skalowanieOX(value);}    //skalowanie trójkąta o wartość osi x
    void skalowanieOY(double value) {A.skalowanieOY(value);B.skalowanieOY(value);C.skalowanieOY(value);}    //skalowanie trójkąta o wartość osi y
    void skalowanieOZ(double value) {A.skalowanieOZ(value);B.skalowanieOZ(value);C.skalowanieOZ(value);}    //skalowanie trójkąta o wartość osi z
    void obrotOX(double value) {A.obrotOX(value);B.obrotOX(value);C.obrotOX(value);NormA.obrotOX(value);NormB.obrotOX(value);NormC.obrotOX(value);}   //obrót trójkąta o wartość osi x
    void obrotOY(double value) {A.obrotOY(value);B.obrotOY(value);C.obrotOY(value);NormA.obrotOY(value);NormB.obrotOY(value);NormC.obrotOY(value);}   //obrót trójkąta o wartość osi y
    void obrotOZ(double value) {A.obrotOZ(value);B.obrotOZ(value);C.obrotOZ(value);NormA.obrotOZ(value);NormB.obrotOZ(value);NormC.obrotOZ(value);}   //obrót trójkąta o wartość osi z
    void render(QImage* img, double** Zbufor, Light light)  //funkcja renderująca pojedynczy trójkąt
    {
        if(scalar((A-B).cross(C-B), B - gracz) < 0)   //jeżeli ściana jest widoczna
        {
            Vector2D pozA = A.toVector2D(Widz), pozB = B.toVector2D(Widz), pozC = C.toVector2D(Widz);   //rzutowanie wierzcholków na 2D
            int **tab = new int*[static_cast<unsigned long long>(wysokosc)];    //dwuwymiarowa tablica przechowująca lewe i prawe krawędzie trójkąta
            Vector3D *wektorylewe = new Vector3D[static_cast<unsigned long long>(wysokosc)];    //zbior wektorow normalnych lewej krawedzi
            Vector3D *wektoryprawe = new Vector3D[static_cast<unsigned long long>(wysokosc)];   //zbior wektorow normalnych prawej krawedzi
            Vector3D *punktylewe = new Vector3D[static_cast<unsigned long long>(wysokosc)];     //zbior punktow w R3 lewej krawedzi
            Vector3D *punktyprawe = new Vector3D[static_cast<unsigned long long>(wysokosc)];    //zbior punktow w R3 lewej krawedzi
            Vector3D R, V, N, L;
            Vector3D POMwektorylewe, POMwektoryprawe, POMpunktylewe, POMpunktyprawe, Pozycja;

            int i, j;   //pomocnicze liczniki
            for(i = 0; i < wysokosc; i++)   //iterujemy po całej wysokości naszego obrazu (oznaczamy że trójkąt jest pusty)
            {
                tab[i] = new int[2];
                tab[i][0] = szerokosc;  //lewa krawędź po prawej
                tab[i][1] = -1;         //prawa po lewej
            }
            pozA.x = pozA.x + 250; pozA.y = 250 - pozA.y;   //centrowanie względem środka
            pozB.x = pozB.x + 250; pozB.y = 250 - pozB.y;   //i odwracamy oś OY
            pozC.x = pozC.x + 250; pozC.y = 250 - pozC.y;   //aby dodatnie wartości były na górze
            tab = triangleValue(NormA, NormB, wektorylewe, wektoryprawe, A, B, punktylewe, punktyprawe, tab, static_cast<int>(pozA.x), static_cast<int>(pozA.y), static_cast<int>(pozB.x), static_cast<int>(pozB.y)); //dla wierzchołka zapisujemy wartości punktów na bokach
            tab = triangleValue(NormA, NormC, wektorylewe, wektoryprawe, A, C, punktylewe, punktyprawe, tab, static_cast<int>(pozA.x), static_cast<int>(pozA.y), static_cast<int>(pozC.x), static_cast<int>(pozC.y));
            tab = triangleValue(NormC, NormB, wektorylewe, wektoryprawe, C, B, punktylewe, punktyprawe, tab, static_cast<int>(pozC.x), static_cast<int>(pozC.y), static_cast<int>(pozB.x), static_cast<int>(pozB.y));
            for(j = max(0,minZtrzech(static_cast<int>(pozA.y), static_cast<int>(pozB.y),static_cast<int>(pozC.y))); j <= min(wysokosc - 1,maksZtrzech(static_cast<int>(pozA.y),static_cast<int>(pozB.y),static_cast<int>(pozC.y))); j++)    //edycja oświetlenia
            {
                POMwektorylewe = wektorylewe[j]; POMwektoryprawe = wektoryprawe[j];   //normalne w 3D
                POMpunktylewe = punktylewe[j]; POMpunktyprawe = punktyprawe[j];   //punkty w 3D
                for(i = max(0,tab[j][0]); i <= min(szerokosc-1,tab[j][1]); i++) //iterujemy od lewej do prawej ściany
                {
                    N = POMwektorylewe; Pozycja = POMpunktylewe;
                    if(tab[j][0] != tab[j][1])  //jeżeli nie jesteśmy w wierzchołku
                    {
                        N = POMwektoryprawe - ((POMwektoryprawe - POMwektorylewe) * static_cast<double>(tab[j][1] - i) / static_cast<double>(tab[j][1] - tab[j][0]));  //wektor normalnyw danym punkcie
                        Pozycja = POMpunktyprawe - ((POMpunktyprawe - POMpunktylewe) * static_cast<double>(tab[j][1] - i) / static_cast<double>(tab[j][1] - tab[j][0]));    //wyliczenie punkty w R3 dla odwzorowania w R2
                    }
                    if(Zbufor[i][j] < Pozycja.z)    //czy obiekt jest dalej niż aktualna pozycja
                    {
                        Zbufor[i][j] = Pozycja.z;
                        L = light.pozycja - Pozycja;
                        R = N.normalize() * scalar(N.normalize(),L.normalize()) * 2.0 - L.normalize();
                        V = gracz - Pozycja;
                        L = L.normalize();
                        N = N.normalize();
                        R = R.normalize();
                        V = V.normalize();
                        double ambient = 0.111;
                        double diffuse = max(0.0,scalar(N,L));
                        double specular = pow(max(0.0,scalar(R,V)),25);
                        rysujPiksel(i,j,kolor * Color(ambient + diffuse + specular) * light.saturacja,img->bits());
                    }
                }
            }
        }
    }
};

struct Object   //bazowa struktura obiekt
{
    Vector3D center;
    Object() {} //konstruktor pusty
    Object(Vector3D center) : center(center) {} //konstruktor ze zmienna srodek obiektu
    virtual void render(QImage* img, double** Zbufor, Light light) = 0;
    virtual ~Object();
};

Object::~Object(){} //destruktor obiektu

struct Wall : public Object //struktura opisujaca sciany 3D
{
    Trojkat gorny,dolny;   //dwa trojkaty imitujace prostokat
    Wall(){}    //konstruktor pusty
    Wall(Vector3D A, Vector3D B, Vector3D C, Vector3D D, Color kolor): gorny(A,B,C,kolor), dolny(C,D,A,kolor) {}   //konstruktor 4 wektorow(wierzcholkow) oraz wypelniania kolorem
    void skalowanieOX(double value) { gorny.skalowanieOX(value); dolny.skalowanieOX(value); }  //funckje skalowania sciany
    void skalowanieOY(double value) { gorny.skalowanieOY(value); dolny.skalowanieOY(value); }
    void skalowanieOZ(double value) { gorny.skalowanieOZ(value); dolny.skalowanieOZ(value); }
    void obrotOX(double value) { gorny.obrotOX(value); dolny.obrotOX(value); }   //funkcje obrotu ściany
    void obrotOY(double value) { gorny.obrotOY(value); dolny.obrotOY(value); }
    void obrotOZ(double value) { gorny.obrotOZ(value); dolny.obrotOZ(value); }
    void setNormal(Vector3D NormA, Vector3D NormB, Vector3D NormC, Vector3D NormD)  //normalizacja trójkątów (sprowadzanie dlugosci boków do 1)
    {
        gorny.NormA = dolny.NormC = NormA;
        gorny.NormB = NormB;
        gorny.NormC = dolny.NormA = NormC;
        dolny.NormB = NormD;
    }
    void render(QImage* img, double** Zbufor, Light oswietlenie)    //renderowanie obu trójkątów wraz z ich oświetleniem i teksturą
    {
        gorny.render(img, Zbufor, oswietlenie);
        dolny.render(img, Zbufor, oswietlenie);
    }
};

struct Sphere : public Object   //struktura opisujaca sfere
{
    QVector <Trojkat> trojkaty;   //sfera sklada sie z trojkatow
    Sphere(Vector3D center, double R, double stacks, double sectors, Color kolor) : Object(center)    //konstruktor przyjmujący jednolity kolor
    {
        QVector <Vector3D> Points;  //zbiór punktów
        QVector <Vector3D> Normal;  //zbiór normalnych
        double sectorstep = 2 * M_PI / sectors; //dzielenie mapy na sektory pionowe
        double stackstep = M_PI / stacks;   //dzielenie mapy na sektory poziome
        double alfa, beta;  //zmienne kątów
        double normals = static_cast<double>(1.0f) / R; //wektor normalny bazowy
        double x, y, z; //współrzędne
        int i, j;   //zmienne pomocnicze
        int k1, k2; //pozycje kolejnych warst sfery
        for(i = 0; i <= stacks; i++)    //iterowanie po poziomych
        {
            alfa = M_PI / 2.0 - i * stackstep;  //obliczanie kąta alfa
            z = R * sin(alfa);  //współrzędna z
            for(j = 0; j <= sectors; j++)   //iterowanie po pionowych
            {
                beta = j * sectorstep;  //obliczanie kąta beta
                x = R * cos(alfa) * cos(beta);  //współrzędna x
                y = R * cos(alfa) * sin(beta);  //współrzędna y
                Points.push_back(Vector3D(x,y,z));  //dodawanie wektorów do tablicy punktów
                Normal.push_back((Vector3D(x,y,z) * normals));      //dodawanie wektorów do zbioru normalnych
            }
        }
        for(i = 0; i < stacks; i++) //iterowanie po poziomych
        {
            k1 = i * static_cast<int>(sectors + 1);     //wskaźnik na pierwszy element poziomu z sektora aktualnego
            k2 = k1 + static_cast<int>(sectors) + 1;    //wskaźnik na pierwszy element poziomu z sektora następnego
            for(j = 0; j < sectors; j++, k1++, k2++)    //iterowanie po pionowych
            {
                if(i != 0)  //jeżeli jesteś na szczycie kuli
                {
                    Trojkat tmp(Points[k2],Points[k1],Points[k1+1],kolor);  //tworzymy pojedynczy trójkąt
                    tmp.setNormal(Normal[k2],Normal[k1],Normal[k1+1]);
                    trojkaty.push_back(tmp);
                }
                if(i != static_cast<int>(stacks - 1))   //tworzymy kwadrat i dzielimy go na dwa trójkąty
                {
                    Trojkat tmp(Points[k2 + 1],Points[k2],Points[k1 + 1],kolor);
                    tmp.setNormal(Normal[k2 + 1],Normal[k2],Normal[k1 + 1]);
                    trojkaty.push_back(tmp);
                }
            }
        }
    }
    void move(Vector3D value) { center = center + value; }   //funkcja poruszająca sferę o wektor
    void skalowanieOX(double value) { for(int i = 0; i < trojkaty.size(); i++) trojkaty[i].skalowanieOX(value); }   //funckje skalujące sferę względem osi ox,oy,oz
    void skalowanieOY(double value) { for(int i = 0; i < trojkaty.size(); i++) trojkaty[i].skalowanieOY(value); }
    void skalowanieOZ(double value) { for(int i = 0; i < trojkaty.size(); i++) trojkaty[i].skalowanieOZ(value); }
    void obrotOX(double value) { for(int i = 0; i < trojkaty.size(); i++) trojkaty[i].obrotOX(value); } //funkcje obrazające sferę względem osi ox,oy,oz
    void obrotOY(double value) { for(int i = 0; i < trojkaty.size(); i++) trojkaty[i].obrotOY(value); }
    void obrotOZ(double value) { for(int i = 0; i < trojkaty.size(); i++) trojkaty[i].obrotOZ(value); }
    void render(QImage* img, double** Zbufor, Light light); //funkcja renderująca obraz na sferze
    ~Sphere() {}    //destruktor sfery
};

void Sphere::render(QImage* img, double** Zbufor, Light light)  //funckaj renderująca sferę
{
    for(int i = 0; i < trojkaty.size(); i++)   //dla wszystkich trójkątów naszej sfery
    {
        Trojkat tmp = trojkaty[i] + center; //przesuwanie względem środka
        tmp.setNormal(trojkaty[i].NormA, trojkaty[i].NormB, trojkaty[i].NormC);  //ustawianie normalnych
        tmp.render(img,Zbufor,light);   //renderowanie
    }
}

struct Scene    //struktura scena
{
    double** Zbufor;    //zmienna tablicy dwuwymiarowej
    Color background;   //zmienna koloru
    QVector <Object*> objects;  //zmienna obiektów nałozonych na scene
    Light light;        //zmienna oświetlenia
    Scene(Color background = Color(), Light light = Light(gracz)) : background(background), light(light) //konstruktor przyjmujący jednolity kolor tła
    {
        Zbufor = new double*[static_cast<unsigned long long>(wysokosc)];
        for(int i = 0; i < wysokosc; i++) //poruszamy się po całej wysokości
        {
            Zbufor[i] = new double[static_cast<unsigned long long>(szerokosc)];
            for(int j = 0; j < szerokosc; j++)  //oraz szerokości
            {
                Zbufor[i][j] = -static_cast<double>(INFINITY);
            }
        }
    }
    void addObject(Object* item) { objects.push_back(item); }   //funkcja dodająca nowy obiekt do sceny
    QImage* render()    //funkcja renderująca scene
    {
        QImage *img = new QImage(szerokosc,wysokosc,QImage::Format_RGB32);
        int i,j;
        for(i = 0; i < wysokosc; i++) //poruszamy się po całej wysokości
        {
            for(j = 0; j < szerokosc; j++)  //oraz szerokości
            {
                rysujPiksel(i,j,background,img->bits());   //ustawiamy kolejne piksele naszego obrarazu
            }
        }
        for(i = 0; i < objects.size(); i++) //sprawdzamy wszystkie obiekty dodane do sceny
        {
            objects[i]->render(img,Zbufor,light);
        }
        return img; //wzracamy gotowy obraz sceny
    }
};

void MyWindow::on_draw1Button_clicked() //przycisk do rysowania mapy nr 1
{
    mapa = 1;
    first = true;
    time = 0;
    rysowanie();
}

void MyWindow::on_draw2Button_clicked() //przycisk do rysowania mapy nr 2
{
    mapa = 2;
    first = true;
    time = 0;
    rysowanie();
}
void MyWindow::on_draw3Button_clicked() //przycisk do rysowania mapy nr 3
{
    mapa = 3;
    first = true;
    time = 0;
    rysowanie();
}

void MyWindow::funkcjazegar()   //funkcja wywoływana co sekundę i aktualizująca czas gry
{
    time = time + 1;
    ui->czas->setText(QString::number(time));
}

void MyWindow::rysowanie()    //funkcja aktualizująca scene
{
    Scene obraz(Color(0.5,0.5,1),Light(Vector3D(swiatloOX,swiatloOY,swiatloOZ), Color(RED,GREEN,BLUE)));    //tworzenie sceny

    Wall* scianalewo = new Wall(Vector3D(-250,-250,0),Vector3D(-248,-250,0),Vector3D(-250,250,0),Vector3D(-248,250,0),Color(1,1,1));    //tworzenie scian zewnętrznych
    Wall* scianagora = new Wall(Vector3D(-250,-250,0),Vector3D(-250,-248,0),Vector3D(250,-250,0),Vector3D(250,-248,0),Color(1,1,1));
    Wall* scianadol = new Wall(Vector3D(250,250,0),Vector3D(250,248,0),Vector3D(-250,250,0),Vector3D(-250,248,0),Color(1,1,1));
    Wall* scianaprawo = new Wall(Vector3D(250,-250,0),Vector3D(248,-250,0),Vector3D(250,250,0),Vector3D(248,250,0),Color(1,1,1));

    if(mapa == 1)   //przypadek wyboru pierwszej mapy
    {
        Sphere* gracz = new Sphere(Vector3D(0,0,0), 40, poziome, pionowe, Color(0.8,0.0,0.9));  //tworzenie sfery

        Wall* sciana = new Wall(Vector3D(-250,-125,0),Vector3D(0,-125,0),Vector3D(0,-127,0),Vector3D(-250,-127,0),Color(1,1,1));    //tworzenie scian wewnętrznych
        Wall* sciana2 = new Wall(Vector3D(125,-125,0),Vector3D(250,-125,0),Vector3D(125,-127,0),Vector3D(250,-127,0),Color(1,1,1));
        Wall* sciana3 = new Wall(Vector3D(-125,0,0),Vector3D(250,0,0),Vector3D(-125,-2,0),Vector3D(250,-2,0),Color(1,1,1));
        Wall* sciana4 = new Wall(Vector3D(-125,250,0),Vector3D(-125,125,0),Vector3D(-123,250,0),Vector3D(-123,125,0),Color(1,1,1));
        Wall* sciana5 = new Wall(Vector3D(125,250,0),Vector3D(125,125,0),Vector3D(123,250,0),Vector3D(123,125,0),Color(1,1,1));
        Wall* sciana6 = new Wall(Vector3D(0,0,0),Vector3D(0,125,0),Vector3D(-2,0,0),Vector3D(-2,125,0),Color(1,1,1));
        Wall* meta = new Wall(Vector3D(140,140,0),Vector3D(220,140,0),Vector3D(140,150,0),Vector3D(220,150,0),Color(0,1,0));    //tworzenie mety

        if(((abs(przesuniecieOX + 250)) < 45)   //dotknięcie ściany
         || ((abs(przesuniecieOX - 250)) < 45)
         || ((abs(przesuniecieOY + 250)) < 45)
         || ((abs(przesuniecieOY - 250)) < 45)
         || ((abs(przesuniecieOX + 125)) < 45 && (przesuniecieOY > 125))
         || ((abs(przesuniecieOX - 125)) < 45 && (przesuniecieOY > 125))
         || ((abs(przesuniecieOX + 0)) < 45 && (przesuniecieOY < 125 && przesuniecieOY > 0))
         || ((abs(przesuniecieOY + 125)) < 45 && (przesuniecieOX < 0 || przesuniecieOX > 125))
         || ((abs(przesuniecieOY + 125)) < 45 && (przesuniecieOX > 125))
         || ((abs(przesuniecieOY + 0)) < 45 && (przesuniecieOX > -125)))
        {
            przesuniecieOX = -200;  //cofnięcie gracza na początek
            przesuniecieOY = -200;
            time = 0;
        }
        obraz.addObject(sciana);    //dodanie ścian oraz pola mety do sceny
        obraz.addObject(sciana2);
        obraz.addObject(sciana3);
        obraz.addObject(sciana4);
        obraz.addObject(sciana5);
        obraz.addObject(sciana6);
        obraz.addObject(meta);
        if((abs(przesuniecieOY - 140)) < 5 && (przesuniecieOX > 125))   //dojście do mety
        {
            przesuniecieOX = -200;  //ustawiamy gracza na początku planszy
            przesuniecieOY = -200;
            ostatni = time;
            time = 0;
            ui->czasostatni->setText(QString::number(ostatni)); //zapisanie czasu i dodanie go do ekranu
        }
        if(first == true)   //jeżeli to nasza pierwsza gra
        {
            przesuniecieOX = -200;  //ustawiamy gracza na początku planszy
            przesuniecieOY = -200;
            first = false;
        }
        gracz->obrotOX(obrotOX);    //obracanie, przesuwanie i skalowanie gracza
        gracz->obrotOZ(obrotOZ);
        gracz->obrotOY(obrotOY);
        gracz->move(Vector3D(przesuniecieOX,przesuniecieOY,przesuniecieOZ));
        gracz->skalowanieOX(skalowanieOX);
        gracz->skalowanieOY(skalowanieOY);
        gracz->skalowanieOZ(skalowanieOZ);

        obraz.addObject(gracz); //dodanie gracza do sceny
    }
    else if(mapa == 2)  //wybór drugiej mapy
    {
        Sphere* gracz = new Sphere(Vector3D(0,0,0), 40, poziome, pionowe, Color(0.8,0.0,0.9));  //tworzenie sfery

        Wall* sciana = new Wall(Vector3D(-125,250,0),Vector3D(-125,-125,0),Vector3D(-123,250,0),Vector3D(-123,-125,0),Color(1,1,1));    //tworzenie scian wewnętrznych
        Wall* sciana2 = new Wall(Vector3D(125,250,0),Vector3D(125,-125,0),Vector3D(123,250,0),Vector3D(123,-125,0),Color(1,1,1));
        Wall* sciana3 = new Wall(Vector3D(0,-250,0),Vector3D(0,125,0),Vector3D(-2,-250,0),Vector3D(-2,125,0),Color(1,1,1));
        Wall* meta = new Wall(Vector3D(-140,-140,0),Vector3D(-220,-140,0),Vector3D(-140,-220,0),Vector3D(-220,-220,0),Color(0.0,0.5,0.0));

        if(((abs(przesuniecieOX + 250)) < 45)
         || ((abs(przesuniecieOX - 250)) < 45)
         || ((abs(przesuniecieOY + 250)) < 45)
         || ((abs(przesuniecieOY - 250)) < 45)
         || ((abs(przesuniecieOX + 125)) < 45 && (przesuniecieOY > -125))
         || ((abs(przesuniecieOX - 125)) < 45 && (przesuniecieOY > -125))
         || ((abs(przesuniecieOX + 0)) < 45 && (przesuniecieOY < 125)))
        {
            przesuniecieOX = 200;   //cofnięcie gracza na początek
            przesuniecieOY = 200;
            time = 0;
        }

        obraz.addObject(sciana);    //dodanie ścian oraz pola mety do sceny
        obraz.addObject(sciana2);
        obraz.addObject(sciana3);
        obraz.addObject(meta);
        if((abs(przesuniecieOY + 140)) < 5 && (przesuniecieOX < -125))   //dojście do mety
        {
            przesuniecieOX = 200;  //ustawiamy gracza na początku planszy
            przesuniecieOY = 200;
            ostatni = time;
            time = 0;
            ui->czasostatni->setText(QString::number(ostatni)); //zapisanie czasu i dodanie go do ekranu
        }
        if(first == true)   //jeżeli to nasza pierwsza gra
        {
            przesuniecieOX = 200;   //ustawiamy gracza na początku planszy
            przesuniecieOY = 200;
            first = false;
        }
        gracz->obrotOX(obrotOX);    //obracanie, przesuwanie i skalowanie gracza
        gracz->obrotOZ(obrotOZ);
        gracz->obrotOY(obrotOY);
        gracz->move(Vector3D(przesuniecieOX,przesuniecieOY,przesuniecieOZ));
        gracz->skalowanieOX(skalowanieOX);
        gracz->skalowanieOY(skalowanieOY);
        gracz->skalowanieOZ(skalowanieOZ);

        obraz.addObject(gracz); //dodanie gracza do sceny
    }
    else if(mapa == 3)  //przypadek wyboru 3 mapy
    {
        if(first == true)   //jeżeli to pierwsze wyświetlanie
        {
            przesuniecieOX = 0; //zerujemy pozycje kul
            przesuniecieOY = 0;
            first = false;
        }
        Sphere* kula1 = new Sphere(Vector3D(-105,85,0), 100, poziome, pionowe, Color(1.0,0,0)); //tworzymy nowe sfery w odpowiednich miejscach
        Sphere* kula2 = new Sphere(Vector3D(105,85,0), 100, poziome, pionowe, Color(0,1.0,0));
        Sphere* kula3 = new Sphere(Vector3D(0,-85,0), 100, poziome, pionowe, Color(0,0,1.0));

        kula1->obrotOX(obrotOX);    //przesynięcie,obrucenie i skalowanie sfer
        kula1->obrotOZ(obrotOZ);
        kula1->obrotOY(obrotOY);
        kula1->move(Vector3D(przesuniecieOX,przesuniecieOY,przesuniecieOZ));
        kula1->skalowanieOX(skalowanieOX);
        kula1->skalowanieOY(skalowanieOY);
        kula1->skalowanieOZ(skalowanieOZ);

        kula2->obrotOX(obrotOX);
        kula2->obrotOZ(obrotOZ);
        kula2->obrotOY(obrotOY);
        kula2->move(Vector3D(przesuniecieOX,przesuniecieOY,przesuniecieOZ));
        kula2->skalowanieOX(skalowanieOX);
        kula2->skalowanieOY(skalowanieOY);
        kula2->skalowanieOZ(skalowanieOZ);

        kula3->obrotOX(obrotOX);
        kula3->obrotOZ(obrotOZ);
        kula3->obrotOY(obrotOY);
        kula3->move(Vector3D(przesuniecieOX,przesuniecieOY,przesuniecieOZ));
        kula3->skalowanieOX(skalowanieOX);
        kula3->skalowanieOY(skalowanieOY);
        kula3->skalowanieOZ(skalowanieOZ);

        obraz.addObject(kula1); //dodanie sfer do sceny
        obraz.addObject(kula2);
        obraz.addObject(kula3);
    }
    obraz.addObject(scianalewo);    //dodanie scian zewnetrznych do sceny
    obraz.addObject(scianagora);
    obraz.addObject(scianadol);
    obraz.addObject(scianaprawo);
    img = obraz.render();   //wyrenderowanie obrazu zapełnionej sceny
    update();   //aktualizacja obrazu
}


void MyWindow::keyPressEvent(QKeyEvent *event)  //funkcja obsługująca klawiaturę
{
    if(event->key() == Qt::Key_W)   //przycisk ruchu w przód
    {
        obrotOX = obrotOX - 5;
        przesuniecieOY = przesuniecieOY + 5;
        rysowanie();
    }
    if(event->key() == Qt::Key_S)   //przycisk ruchu w tył
    {
        obrotOX = obrotOX + 5;
        przesuniecieOY = przesuniecieOY - 5;
        rysowanie();
    }
    if(event->key() == Qt::Key_A)   //przycisk ruchu w lewo
    {
        obrotOY = obrotOY - 5;
        przesuniecieOX = przesuniecieOX - 5;
        rysowanie();
    }
    if(event->key() == Qt::Key_D)   //przycisk ruchu w prawo
    {
        obrotOY = obrotOY + 5;
        przesuniecieOX = przesuniecieOX + 5;
        rysowanie();
    }
}

void MyWindow::on_horizontalSlider_valueChanged(int value)  //slider edycji przesunięcia osi OX kuli
{
    przesuniecieOX = value - 250;
    rysowanie();
}

void MyWindow::on_horizontalSlider_2_valueChanged(int value)    //slider edycji przesunięcia osi OY kuli
{
    przesuniecieOY = value - 250;
    rysowanie();
}

void MyWindow::on_horizontalSlider_3_valueChanged(int value)    //slider edycji przesunięcia osi OZ kuli
{
    przesuniecieOZ = value - 250;
    rysowanie();
}

void MyWindow::on_dial_valueChanged(int value)  //edycja obrotu względem osi OX
{
    obrotOX = value;
    rysowanie();
}

void MyWindow::on_dial_2_valueChanged(int value)    //edycja obrotu względem osi OY
{
    obrotOY = value;
    rysowanie();
}

void MyWindow::on_dial_3_valueChanged(int value)    //edycja obrotu względem osi OZ
{
    obrotOZ = value;
    rysowanie();
}

void MyWindow::on_horizontalSlider_4_valueChanged(int value)    //slider edycji skalowania osi OX kuli
{
    skalowanieOX = value / 250.0;
    rysowanie();
}

void MyWindow::on_horizontalSlider_5_valueChanged(int value)    //slider edycji skalowania osi OY kuli
{
    skalowanieOY = value / 250.0;
    rysowanie();
}

void MyWindow::on_horizontalSlider_6_valueChanged(int value)    //slider edycji skalowania osi OZ kuli
{
    skalowanieOZ = value / 250.0;
    rysowanie();
}

void MyWindow::on_pushButton_clicked()  //przycisk resetu kuli do usawień domyślnych
{
    przesuniecieOX = 0;
    przesuniecieOY = 0;
    przesuniecieOZ = 0;
    skalowanieOX = 1;
    skalowanieOY = 1;
    skalowanieOZ = 1;
    obrotOX = 0;
    obrotOY = 0;
    obrotOZ = 0;
    ui->horizontalSlider->setValue(250);
    ui->horizontalSlider_2->setValue(250);
    ui->horizontalSlider_3->setValue(250);
    ui->horizontalSlider_4->setValue(250);
    ui->horizontalSlider_5->setValue(250);
    ui->horizontalSlider_6->setValue(250);
    ui->spinBox->setValue(20);
    ui->spinBox_2->setValue(20);
    ui->dial->setValue(0);
    ui->dial_2->setValue(0);
    ui->dial_3->setValue(0);
    rysowanie();
}

void MyWindow::on_horizontalSlider_16_valueChanged(int value)   //slider edycji przesunięcia osi OX światła
{
    swiatloOX = value - 500;
    rysowanie();
}

void MyWindow::on_horizontalSlider_17_valueChanged(int value)   //slider edycji przesunięcia osi OY światła
{
    swiatloOY = value - 500;
    rysowanie();
}

void MyWindow::on_horizontalSlider_18_valueChanged(int value)   ///slider edycji przesunięcia osi OZ światła
{
    swiatloOZ = value - 500;
    rysowanie();
}

void MyWindow::on_horizontalSlider_13_valueChanged(int value)   //slider edycji nasilenia koloru czerwonego
{
    RED = value/255.0;
    rysowanie();
}

void MyWindow::on_horizontalSlider_14_valueChanged(int value)   //slider edycji nasilenia koloru zielonego
{
    GREEN = value/255.0;
    rysowanie();
}

void MyWindow::on_horizontalSlider_15_valueChanged(int value)   //slider edycji nasilenia koloru niebieskiego
{
    BLUE = value/255.0;
    rysowanie();
}

void MyWindow::on_pushButton_3_clicked()    //przycisk resetu światła do usawień domyślnych
{
    swiatloOX = 0;
    swiatloOY = 0;
    swiatloOZ = 500;
    RED = GREEN = BLUE = 0.5;
    ui->horizontalSlider_16->setValue(500);
    ui->horizontalSlider_17->setValue(500);
    ui->horizontalSlider_18->setValue(1000);
    ui->horizontalSlider_13->setValue(127);
    ui->horizontalSlider_14->setValue(127);
    ui->horizontalSlider_15->setValue(127);
    rysowanie();
}

void MyWindow::on_spinBox_valueChanged(int value)   //edycja ilości ścian poziomych
{
    poziome = value;
    rysowanie();
}

void MyWindow::on_spinBox_2_valueChanged(int value) //edycja ilości ścian pionowych
{
    pionowe = value;
    rysowanie();
}

void MyWindow::on_gora_clicked()    //funkcja obsługująca przycisk ruchu w górę
{
    obrotOX = obrotOX - 5;
    przesuniecieOY = przesuniecieOY + 5;
    rysowanie();
}

void MyWindow::on_dol_clicked()     //funkcja obsługująca przycisk ruchu w dół
{
    obrotOX = obrotOX + 5;
    przesuniecieOY = przesuniecieOY - 5;
    rysowanie();
}

void MyWindow::on_prawo_clicked()   //funkcja obsługująca przycisk ruchu w prawo
{
    obrotOY = obrotOY + 5;
    przesuniecieOX = przesuniecieOX + 5;
    rysowanie();
}

void MyWindow::on_lewo_clicked()    //funkcja obsługująca przycisk ruchu w lewo
{
    obrotOY = obrotOY - 5;
    przesuniecieOX = przesuniecieOX - 5;
    rysowanie();
}
