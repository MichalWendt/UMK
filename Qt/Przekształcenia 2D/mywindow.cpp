#include "mywindow.h"
#include <cmath>
#include "ui_mywindow.h"
#include <QDebug>

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
    oryginal = new QImage(szer,wys,QImage::Format_RGB32);
    kopia = new QImage(":/turtle.jpg");
    zamaluj();
    *img = kopia->copy();
    *oryginal = kopia->copy();
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}

void MyWindow::zamaluj()
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 255;
            ptr[szer*4*i + 4*j + 1] = 255;
            ptr[szer*4*i + 4*j + 2] = 255;
        }
    }
}

void MyWindow::zamaluj_kopie()
{
    unsigned char *ptr;
    ptr = kopia->bits();

    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 255;
            ptr[szer*4*i + 4*j + 1] = 255;
            ptr[szer*4*i + 4*j + 2] = 255;
        }
    }
}

void MyWindow::wyzeruj(){
    int i,j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            przesuniecie[i][j] = 0;
            MacierzSkal[i][j] = 0;
            MacierzObrot[i][j] = 0;
            MacierzPochylenie[i][j] = 0;
            wynik[i][j] = 0;
        }
    }
}

void MyWindow::Przesuniecie(){
    przesuniecie[0][0] = 1;
    przesuniecie[0][2] = pion;
    przesuniecie[1][1] = 1;
    przesuniecie[1][2] = poziom;
    przesuniecie[2][2] = 1;
}

void MyWindow::Scal(){
    MacierzSkal[0][0] = skalowanieOX;
    MacierzSkal[1][1] = skalowanieOY;
    MacierzSkal[2][2] = 1;
    MacierzSkal[0][2] = (szer/2.0)*(1-skalowanieOX);
    MacierzSkal[1][2] = (wys/2.0)*(1-skalowanieOY);
}

void MyWindow::Obrot(){
    MacierzObrot[0][0] = cos(obrot);
    MacierzObrot[0][1] = -sin(obrot);
    MacierzObrot[0][2] = (szer/2.0)*(1-cos(obrot))+(wys/2.0)*(sin(obrot));
    MacierzObrot[1][0] = sin(obrot);
    MacierzObrot[1][1] = cos(obrot);
    MacierzObrot[1][2] = (wys/2.0)*(1-cos(obrot))-(szer/2.0)*(sin(obrot));
    MacierzObrot[2][2] = 1;
}

void MyWindow::Pochylenie(){
    MacierzPochylenie[0][0] = 1 + pochylenieOX*pochylenieOY;
    MacierzPochylenie[0][1] = pochylenieOX;
    MacierzPochylenie[1][0] = pochylenieOY;
    MacierzPochylenie[1][1] = 1;
    MacierzPochylenie[2][2] = 1;
    MacierzPochylenie[0][2] = -(szer/2.0)*pochylenieOX*pochylenieOY - pochylenieOX*(wys/2.0);
    MacierzPochylenie[1][2] = -(szer/2.0)*pochylenieOY;
}

double MyWindow::Interpolacja(int x, int y, double dx){
    return (1-dx)*x+dx*y;
}

void MyWindow::Mnozenie(double dane[3][3]){
    int i,j,k;
    double s;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            s = 0;
            for(k = 0; k < 3; k++){
                s += wynik[i][k] * dane[k][j];
            }
            pomoc[i][j] = s;
        }
    }
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            wynik[i][j] = pomoc[i][j];
        }
    }
}

void MyWindow::przeksztalcanie(){
    int i,j;
    double a,b;
    int x,y,xn,yn;
    unsigned char *ptr,*org;
    zamaluj();
    ptr = img->bits();
    org = oryginal->bits();
    wyzeruj();
    Scal();
    Obrot();
    Pochylenie();
    Przesuniecie();
    wynik[0][0] = 1;
    wynik[1][1] = 1;
    wynik[2][2] = 1;
    Mnozenie(MacierzSkal);
    Mnozenie(MacierzObrot);
    Mnozenie(MacierzPochylenie);
    Mnozenie(przesuniecie);
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            x = a = wynik[0][0] * i + wynik[0][1] * j + wynik[0][2];
            y = b = wynik[1][0] * i + wynik[1][1] * j + wynik[1][2];
            xn = x + 1;
            yn = y + 1;
            if(xn == wys)
                xn--;
            if(yn == szer)
                yn--;
            if(x >= 0 && y >= 0 && x < wys && y < szer){
                a = a - x;
                b = b - y;
                ptr[szer*4*i + 4*j] = round(Interpolacja(Interpolacja(org[szer*4*x + 4*y],org[szer*4*xn + 4*y],a),Interpolacja(org[szer*4*x + 4*yn],org[szer*4*xn + 4*yn],a),b));
                ptr[szer*4*i + 4*j + 1] = round(Interpolacja(Interpolacja(org[szer*4*x + 4*y + 1],org[szer*4*xn + 4*y + 1],a),Interpolacja(org[szer*4*x + 4*yn + 1],org[szer*4*xn + 4*yn + 1],a),b));
                ptr[szer*4*i + 4*j + 2] = round(Interpolacja(Interpolacja(org[szer*4*x + 4*y + 2],org[szer*4*xn + 4*y + 2],a),Interpolacja(org[szer*4*x + 4*yn + 2],org[szer*4*xn + 4*yn + 2],a),b));
            }
        }
    }
    update();
}

void MyWindow::on_pushButton_clicked()
{
    obrot = 0;
    pion = 0;
    poziom = 0;
    krzywapion = 0;
    krzywapoziom = 0;
    skalowanieOX = 1;
    skalowanieOY = 1;
    pochylenieOX = 0;
    pochylenieOY = 0;
    ui->szerokosc->setValue(0);
    ui->wysokosc->setValue(0);
    ui->verticalSlider->setValue(50);
    ui->horizontalSlider->setValue(50);
    ui->scalwys->setValue(50);
    ui->scalszer->setValue(50);
    ui->rotacja->setValue(0);
    *img = oryginal->copy();
}

void MyWindow::on_szerokosc_valueChanged(int value)
{
    poziom = -value;
    przeksztalcanie();
}

void MyWindow::on_wysokosc_valueChanged(int value)
{
    pion = value;
    przeksztalcanie();
}

void MyWindow::on_rotacja_sliderMoved(int position)
{
    obrot = M_PI * (position)/180.0;
    przeksztalcanie();
}

void MyWindow::on_horizontalSlider_valueChanged(int value)
{
    if(value < 50){
        pochylenieOY = ((50 - value)/50.0);
    } else {
        pochylenieOY = 1-(value/50.0);
    }
    przeksztalcanie();
}

void MyWindow::on_verticalSlider_valueChanged(int value)
{
    if(value < 50){
        pochylenieOX = - ((50 - value)/50.0);
    } else {
        pochylenieOX = (value/50.0) - 1;
    }
    przeksztalcanie();
}

void MyWindow::on_scalwys_valueChanged(int value)
{
    skalowanieOX = 50.0 / (double) value;
    przeksztalcanie();
}

void MyWindow::on_scalszer_valueChanged(int value)
{
    skalowanieOY = 50.0 / (double) value;
    przeksztalcanie();
}
