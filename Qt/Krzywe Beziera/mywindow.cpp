#include "mywindow.h"
#include "ui_mywindow.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

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
    czysc();
    *copy = img->copy();

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

void MyWindow::on_cleanButton_clicked()
{
    czysc();
    update();
}

void MyWindow::on_pushButton_clicked()
{
    *img = copy->copy();
    krzywe();
    punkty.clear();
    linii = 0;
    licznik = -1;
    kontorla = false;
    *copy = img->copy();
    update();
}

void MyWindow::czysc()
{
    unsigned char *ptr;
    ptr = img->bits();
    licznik = -1;
    linii = 0;
    kontorla = false;
    punkty.clear();
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
    *copy = img->copy();
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    *img = copy->copy();
    x -= poczX;
    y -= poczY;

    if(event->button() == Qt::LeftButton)
    {
        if((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
        {

        }
    }
    else
    {
        if((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
        {
            sprawdz(x,y);
        }

    }
    krzywe();
    punkt();
    update();
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    *img = copy->copy();
    x -= poczX;
    y -= poczY;

    if(event->button() == Qt::LeftButton)
    {
        if((x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
                punkty.push_back(std::make_pair(x,y));
                licznik++;
                if(licznik % 3 == 0 && licznik != 0){
                    linii++;
                }
        }
    }
    else if(event->button() == Qt::MiddleButton)
    {
        if(kontorla == true && (x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
            pair<int, int> przesuniety;
            przesuniety = std::make_pair(x,y);
            *przesun = przesuniety;
            kontorla = false;
        }
    }
    else
    {
        sprawdz(x,y);
        if(kontorla){
            punkty.erase(przesun);
            if(licznik % 3 == 0 && licznik != 0){
                linii--;
            }
            licznik--;
            kontorla = false;
        }
    }
    krzywe();
    punkt();
    update();
}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    *img = copy->copy();
    x -= poczX;
    y -= poczY;

    if(event->button() == Qt::LeftButton)
    {

    }
    else
    {
        if(kontorla == true && (x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
            pair<int, int> przesuniety;
            przesuniety = std::make_pair(x,y);
            *przesun = przesuniety;
        }
    }
    krzywe();
    punkt();
    update();
}

void MyWindow::rysujPunkty(int x, int y){
    int i,j;
    for(i = x - 5; i <= x + 5; i++){
        for(j = y - 5; j <= y + 5; j++){
            rysujPiksel(i,j,(linii*25)%255,(linii+50)%255,(linii*10)%255);
        }
    }
}

void MyWindow::rysujPiksel(int x, int y, int r, int g, int b){
    unsigned char *ptr;
    ptr = img->bits();
    if(x >= 0 && y >= 0 && x < szer && y < wys){
        ptr[szer * 4 * y + 4 * x] = b;
        ptr[szer * 4 * y + 4 * x + 1] = g;
        ptr[szer * 4 * y + 4 * x + 2] = r;
    }
}

void MyWindow::prosta(int startx, int starty, int koniecx, int koniecy,int r, int g, int c){
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
            rysujPiksel(i,pom,r,g,c);
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
            rysujPiksel(pom,i,r,g,c);
        }
    }
}
void MyWindow::sprawdz(int x, int y){
    for(vector<pair<int, int> >::iterator it = punkty.begin(); it != punkty.end(); it++){
        if(it->first + 5 >= x && it->first - 5 <= x && it->second + 5 >= y && it->second - 5 <= y){
            przesun = it;
            kontorla = true;
            return;
        }
    }
}

void MyWindow::punkt(){
    if(punkty.empty())
        return;
    for(vector<pair<int, int> >::iterator it = punkty.begin(); it != punkty.end(); it++){
        rysujPunkty(it->first,it->second);
    }
}

void MyWindow::krzywe(){
    pair<int,int> p1,p2,p3,p4;
    int x, y, a, b;
    int i = 0;
    double t;
    if(punkty.empty())
        return;
    vector<pair<int, int> >::iterator it = punkty.begin();
    p1 = *it;
    for(vector<pair<int, int> >::iterator it = punkty.begin() + 1; i < linii; i++, it += 3)
    {
        p2 = *(it);
        p3 = *(it + 1);
        p4 = *(it + 2);
        for(t = 0; t <= 1; t += 0.001){
            x = (double)(p1.first * (1 - t) * (1 - t) * (1 - t) + 3 * (1 - t) * (1 - t) * t * p2.first + 3 * (1 - t) * t * t * p3.first + t * t * t * p4.first);
            y = (double)(p1.second * (1 - t) * (1 - t) * (1 - t) + 3 * (1 - t) * (1 - t) * t * p2.second + 3 * (1 - t) * t * t * p3.second + t * t * t *p4.second);
            if(t > 0){
                prosta(a, b, x, y, 0, 0, 0);
            }
            a = x;
            b = y;
        }
        p1 = p4;
    }
}
