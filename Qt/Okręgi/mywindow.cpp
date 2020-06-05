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

void MyWindow::on_radioButton_1_clicked()
{
    tryb = 1;
}
void MyWindow::on_radioButton_2_clicked()
{
    tryb = 2;
}
void MyWindow::on_radioButton_3_clicked()
{
    tryb = 3;
}
void MyWindow::on_spinBox_valueChanged(int arg1)
{
    boki = arg1;
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

// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    int x = event->x();
    int y = event->y();

    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku

    x -= poczX;
    y -= poczY;
    *copy = img->copy();


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

    // Sprawdzamy czy klikniecie nastapilo w granicach rysunku
    if ((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
    {
        aktuX = x;
        aktuY = y;
    } else {
        aktuX = -1;
        aktuY = -1;
    }

    // Odswiezamy komponent
    update();
}
void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(tryb == 1){
        okrag(event);
    }
    if(tryb == 2){
        elipsa(event);
    }
    if(tryb == 3){
        wielokat(event);
    }
}
void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(tryb == 1){
        okrag_mouse(event);
    }
    if(tryb == 2){
        elipsa_mouse(event);
    }
    if(tryb == 3){
        wielokat_mouse(event);
    }
}

void MyWindow::okrag(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(aktuX < 0 || aktuY < 0){
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    r = (aktuX - endX) * (aktuX - endX) + (aktuY - endY) * (aktuY - endY);
    for(x = 0; x * x <= r / 2; x++){
        y = sqrt(r - x * x);
        rysujPixel(aktuX + x,aktuY + y);
        rysujPixel(aktuX + x,aktuY + -y);
        rysujPixel(aktuX + -x,aktuY + y);
        rysujPixel(aktuX + -x,aktuY + -y);
        rysujPixel(aktuX + y,aktuY + x);
        rysujPixel(aktuX + y,aktuY + -x);
        rysujPixel(aktuX + -y,aktuY + x);
        rysujPixel(aktuX + -y,aktuY + -x);
    }
    update();
}
void MyWindow::okrag_mouse(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(aktuX < 0 || aktuY < 0){
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    r = (aktuX - endX) * (aktuX - endX) + (aktuY - endY) * (aktuY - endY);
    for(x = 0; x * x <= r / 2; x++){
        y = sqrt(r - x * x);
        rysujPixel(aktuX + x,aktuY + y);
        rysujPixel(aktuX + x,aktuY + -y);
        rysujPixel(aktuX + -x,aktuY + y);
        rysujPixel(aktuX + -x,aktuY + -y);
        rysujPixel(aktuX + y,aktuY + x);
        rysujPixel(aktuX + y,aktuY + -x);
        rysujPixel(aktuX + -y,aktuY + x);
        rysujPixel(aktuX + -y,aktuY + -x);
    }
    update();
}
void MyWindow::elipsa(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int a, b;
    double r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(aktuX < 0 || aktuY < 0){
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    a = abs(aktuX - endX);
    b = abs(aktuY - endY);
    for(r = 0; r < 2 * M_PI; r += 0.001){
        x = a * cos(r);
        y = b * sin(r);
        rysujPixel(aktuX + x,aktuY + y);
        rysujPixel(aktuX + x,aktuY + -y);
        rysujPixel(aktuX + -x,aktuY + y);
        rysujPixel(aktuX + -x,aktuY + -y);
    }
    update();
}
void MyWindow::elipsa_mouse(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int a, b;
    double r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(aktuX < 0 || aktuY < 0){
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    a = abs(aktuX - endX);
    b = abs(aktuY - endY);
    for(r = 0; r <= 2 * M_PI; r += 0.001){
        x = a * cos(r);
        y = b * sin(r);
        rysujPixel(aktuX + x,aktuY + y);
        rysujPixel(aktuX + x,aktuY + -y);
        rysujPixel(aktuX + -x,aktuY + y);
        rysujPixel(aktuX + -x,aktuY + -y);
    }
    update();
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

void MyWindow::wielokat(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int a, b;
    int xx,yy;
    double r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(aktuX < 0 || aktuY < 0){
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    a = abs(aktuX - endX);
    b = abs(aktuY - endY);
    x = a * cos(0);
    y = b * sin(0);
    for(r = 2 * M_PI / boki; r <= 2 * M_PI + 0.1; r += 2 * M_PI / boki){
        xx = a * cos(r);
        yy = b * sin(r);
        prosta(aktuX + x,aktuY + y,aktuX + xx,aktuY + yy);
        x = xx;
        y = yy;
    }
    update();
}
void MyWindow::wielokat_mouse(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int a, b;
    int xx,yy;
    double r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(aktuX < 0 || aktuY < 0){
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    a = abs(aktuX - endX);
    b = abs(aktuY - endY);
    x = a * cos(0);
    y = b * sin(0);
    for(r = 2 * M_PI / boki; r <= 2 * M_PI + 0.1; r += 2 * M_PI / boki){
        xx = a * cos(r);
        yy = b * sin(r);
        prosta(aktuX + x,aktuY + y,aktuX + xx,aktuY + yy);
        x = xx;
        y = yy;
    }
    update();
}
