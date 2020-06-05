#include "mywindow.h"
#include "ui_mywindow.h"
#include <cmath>

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);

    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    img = new QImage(szer,wys,QImage::Format_RGB32);
    copy = new QImage(szer,wys,QImage::Format_RGB32);
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_exitButton_clicked()
{
    qApp->quit();
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    p.drawImage(poczX,poczY,*img);
}

void MyWindow::on_draw1Button_clicked()
{
    rysuj1();
    update();
}

void MyWindow::on_draw2Button_clicked()
{
    rysuj2();
    update();
}

void MyWindow::rysuj1()
{
    unsigned char *ptr;
        ptr = img->bits();
        szer = img->width();
        wys = img->height();

        int i,j;
        for(i=0;i<wys;i++)
        {
                for(j=0;j<szer ;j++)
                {
                        ptr[szer*4*i + 4*j]=0;
                        ptr[szer*4*i + 4*j + 1] = 0;
                        ptr[szer*4*i + 4*j + 2] = 0;
                }
        }
}

void MyWindow::rysuj2()
{
    unsigned char *ptr;
        ptr = img->bits();
        szer = img->width();
        wys = img->height();

        int i,j;
        for(i=0;i<wys;i++)
        {
                for(j=0; j<szer; j++)
                {
                        ptr[szer*4*i + 4*j] = 255;
                        ptr[szer*4*i + 4*j + 1] = 255;
                        ptr[szer*4*i + 4*j + 2] = 255;
                }
        }
}

void MyWindow::rysujPixel(int x, int y)
{
    unsigned char *ptr;
        ptr = img->bits();
        if(x >= 0 && y >= 0 && x < szer && y < wys){
            ptr[szer * 4 * y + 4 * x] = kolor;
            ptr[szer * 4 * y + 4 * x + 1] = kolor;
            ptr[szer * 4 * y + 4 * x + 2] = kolor;
        }
}

void MyWindow::prosta(int startx, int starty, int koniecx, int koniecy){
    double a, b;
    int pom;
    int i;
    if(abs(startx - koniecx) > abs(starty - koniecy)){
        if(startx > koniecx){
            pom = startx;
            startx = koniecx;
            koniecx = pom;
            pom = starty;
            starty = koniecy;
            koniecy = pom;
        }
        a = (koniecy - starty) / (double) (koniecx - startx);
        b = starty - a * startx;
        for(i = startx; i <= koniecx; i++){
            pom = a * i + b;
            rysujPixel(i,pom);
        }
    } else {
        if(starty > koniecy){
            pom = startx;
            startx = koniecx;
            koniecx = pom;
            pom = starty;
            starty = koniecy;
            koniecy = pom;
        }
        a = (koniecx - startx) / (double) (koniecy - starty);
        b = startx - a * starty;
        for(i = starty; i <= koniecy; i++){
            pom = a * i + b;
            rysujPixel(pom,i);
        }
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int pom;
    double a, b, w;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(aktuX < 0 || aktuY < 0){
        return;
    }
    useX = aktuX;
    useY = aktuY;
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    unsigned char *ptr;
    ptr = img->bits();
    endX = x;
    endY = y;
    // Jezeli wyjechalismy poza zakres to nadajemy maksymalne wartosci osiaglane w danym miejscu
    if(endX < 0){
        endX = 0;
    }
    if(endX > szer){
        endX = szer - 1;
    }
    if(endY < 0){
        endY = 0;
    }
    if(endY > wys){
        endY = wys - 1;
    }
    if(aktuX > endX){
        pom = aktuX;
        aktuX = endX;
        endX = pom;
        pom = aktuY;
        aktuY = endY;
        endY = pom;
    }
    // Jezeli jest wieksza roznica x'ow miedzy y'kami to liczymy traktujac x jako dziedzine
    if(abs(endX - aktuX) > abs(endY - aktuY)){
        a = (endY - aktuY) / (double)(endX - aktuX);
        b = aktuY - a * aktuX;
        for(int i = aktuX;i >= 0 && i <= endX && i < szer; i++){
            // Ustawiamy kolor kliknietego piksela na bialy lub czarny
            w = a * i + b;
            pom = round(w);
            rysujPixel(i,pom);
        }
    } else {
        if(aktuY > endY){
            pom = aktuX;
            aktuX = endX;
            endX = pom;
            pom = aktuY;
            aktuY = endY;
            endY = pom;
        }
        if(endY - aktuY != 0){
            a = (endX - aktuX) / (double)(endY - aktuY);
        }
        else {
            a = 0;
        }
        b = aktuX - a * aktuY;
        for(int i = aktuY; i >= 0 && i <= endY && i < wys; i++){
            // Ustawiamy kolor kliknietego piksela na bialy lub czarny
            w = a * i + b;
            pom = round(w);
            rysujPixel(pom,i);
        }
    }
    aktuX = useX;
    aktuY = useY;
    // Odswiezamy komponent
    update();
}


void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int pom;
    double a, b, w;
    *img = copy->copy();
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku

    useX = aktuX;
    useY = aktuY;
    x -= poczX;
    y -= poczY;
    unsigned char *ptr;
    ptr = img->bits();


    endX = x;
    endY = y;
    // Jezeli jest wieksza roznica x'ow miedzy y'kami to liczymy traktujac x jako dziedzine
    if(endX < 0){
        endX = 0;
    }
    if(endX > szer){
        endX = szer - 1;
    }
    if(endY < 0){
        endY = 0;
    }
    if(endY > wys){
        endY = wys - 1;
    }
    if(aktuX > endX){
        pom = aktuX;
        aktuX = endX;
        endX = pom;
        pom = aktuY;
        aktuY = endY;
        endY = pom;
    }
    if(abs(endX - aktuX) > abs(endY - aktuY)){
        a = (endY - aktuY) / (double)(endX - aktuX);
        b = aktuY - a * aktuX;
        for(int i = aktuX;i >= 0 && i <= endX && i < szer; i++){
            // Ustawiamy kolor kliknietego piksela na bialy lub czarny
            w = a * i + b;
            pom = round(w);
            rysujPixel(i,pom);
        }
    } else {
        if(aktuY > endY){
            pom = aktuX;
            aktuX = endX;
            endX = pom;
            pom = aktuY;
            aktuY = endY;
            endY = pom;
        }
        a = (endX - aktuX) / (double)(endY - aktuY);
        b = aktuX - a * aktuY;
        for(int i = aktuY; i >= 0 && i <= endY && i < wys; i++){
            // Ustawiamy kolor kliknietego piksela na bialy lub czarny
            w = a * i + b;
            pom = (int)round(w);
            rysujPixel(pom,i);
        }
    }
    aktuX = useX;
    aktuY = useY;
    // Odswiezamy komponent
    update();
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    startX = event->x();
    startY = event->y();
    szer = img->width();
    wys = img->height();

    startX -= poczX;
    startY -= poczY;

    *copy = img->copy();
    unsigned char *ptr;
    ptr = img->bits();

    // Sprawdzamy ktory przycisk myszy zostal klkniety
    if(event->button() == Qt::LeftButton)
    {
        // jezeli lewy to ustawiamy kolor na czarny
        kolor = 0;
    }
    else
    {
        // jezeli prawy to ustawiamy kolor na bialy
        kolor = 255;
    }

    if ((startX>=0)&&(startY>=0)&&(startX<szer)&&(startY<wys))
    {
        aktuX = startX;
        aktuY = startY;
        if(pX == -1 && pY == -1)
        {
            pX = startX;
            pY = startY;
            lX = startX;
            lY = startY;
        }

        if(startX-10 < pX && startX+10>pX && startY-10 < pY && startY+10>pY)
        {
            prosta(lX,lY,pX,pY);
            pX = pY = -1;
        }
        else
        {
            prosta(startX,startY,lX,lY);
            lX = startX;
            lY = startY;
        }

    }
    else
    {
            aktuX = -1;
            aktuY = -1;
    }
}
