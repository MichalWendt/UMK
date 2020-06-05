#include "mywindow.h"
#include <cmath>
#include <vector>
#include "ui_mywindow.h"

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

void MyWindow::czysc()
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
    first = true;
    punkty.clear();
}

void MyWindow::rysujPiksel(int x, int y){
    unsigned char *ptr;
    ptr = img->bits();
    if(x >= 0 && y >= 0 && x < szer && y < wys){
        ptr[szer * 4 * y + 4 * x] = kolor;
        ptr[szer * 4 * y + 4 * x + 1] = 0;
        ptr[szer * 4 * y + 4 * x + 2] = 0;
    }
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    x -= ui->rysujFrame->x();
    y -= ui->rysujFrame->y();
    *copy = img->copy();

    if((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
    {
        if(first)
        {
            startX = x;
            startY = y;
            endX = x;
            endY = y;
            first = false;
        }
        clickX = x;
        clickY = y;
        if((abs(startX - x) + abs(startY - y)) < 10)
        {
            clickX = startX;
            clickY = startY;
        }
        punkty.push_back(make_pair(clickX,clickY));
        linia();

    } else {
        return;
    }
    // Odswiezamy komponent
    update();
}

void MyWindow::linia(){
    int useX;
    int useY;
    int pom;
    double a, b, w;
    *img = copy->copy();
    useX = clickX;
    useY = clickY;

    int i,j;
    for(i=(startY - 5); i<(startY + 5); i++)
    {
        for(j=(startX - 5); j<(startX + 5); j++)
        {
            kolor = 255;
            rysujPiksel(j,i);
            kolor = 0;
        }
    }
    if(clickX > endX){
        pom = clickX;
        clickX = endX;
        endX = pom;
        pom = clickY;
        clickY = endY;
        endY = pom;
    }
    if(abs(endX - clickX) > abs(endY - clickY)){
        a = (endY - clickY) / (double)(endX - clickX);
        b = clickY - a * clickX;
        for(int i = clickX;i >= 0 && i <= endX && i < szer; i++){
            w = a * i + b;
            pom = round(w);
            rysujPiksel(i,pom);
        }
    } else {
        if(clickY > endY){
            pom = clickX;
            clickX = endX;
            endX = pom;
            pom = clickY;
            clickY = endY;
            endY = pom;
        }
        if(endY - clickY != 0){
            a = (endX - clickX) / (double)(endY - clickY);
        }
        else {
            a = 0;
        }
        b = clickX - a * clickY;
        for(int i = clickY; i >= 0 && i <= endY && i < wys; i++){
            w = a * i + b;
            pom = round(w);
            rysujPiksel(pom,i);
        }
    }
    endX = useX;
    endY = useY;
    update();
}

void MyWindow::on_pushButton_clicked()
{
    img->fill(0xffffff);
    kolor = 0;
    int i, j, k;
    int x;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<(int)punkty.size(); j++)
        {
            if(j == (int)punkty.size() - 1)
            {
                if((i <= punkty[j].second && i > punkty[0].second) || (i > punkty[j].second && i <= punkty[0].second))
                {
                    if(punkty[0].second - punkty[j].second == 0)
                    {
                        x = punkty[j].first;
                    }
                    else
                    {
                        x = punkty[j].first + (i - punkty[j].second) * ((punkty[0].first - punkty[j].first) / static_cast<double>(punkty[0].second - punkty[j].second));
                    }
                    przeciecia.push_back(x);
                }
            }
            else if((i <= punkty[j].second && i > punkty[j+1].second) || (i > punkty[j].second && i <= punkty[j+1].second))
            {
                if(punkty[j+1].second - punkty[j].second == 0)
                {
                    x = punkty[j].first;
                }
                else
                {
                    x = punkty[j].first + (i - punkty[j].second) * ((punkty[j+1].first - punkty[j].first) / static_cast<double>(punkty[j+1].second - punkty[j].second));
                }
                przeciecia.push_back(x);
            }

        }
        sort(przeciecia.begin(), przeciecia.end());
        for(j=0; j<(int)przeciecia.size(); j++)
        {
            if(j % 2 == 0)
            {
                if(j == (int)przeciecia.size() - 1)
                {

                }
                else
                {
                    for(k=przeciecia[j]; k<=przeciecia[j+1]; k++)
                    {
                        rysujPiksel(k,i);
                    }
                }
            }
        }
    przeciecia.clear();
  }
    update();
}
