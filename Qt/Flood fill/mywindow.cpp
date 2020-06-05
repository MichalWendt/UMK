#include "mywindow.h"
#include <cmath>
#include <stack>
#include <QColorDialog>
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

void MyWindow::on_cleanButton_2_clicked()
{
   czysc2();
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
            ptr[szer*4*i + 4 * j] = 255;
            ptr[szer*4*i + 4 * j + 1] = 255;
            ptr[szer*4*i + 4 * j + 2] = 255;
        }
    }
}

void MyWindow::czysc2()
{
    unsigned char *ptr;
    ptr = img->bits();
    int i,j;

    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4 * j] = 0;
            ptr[szer*4*i + 4 * j + 1] = 0;
            ptr[szer*4*i + 4 * j + 2] = 0;
        }
    }
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    x -= poczX;
    y -= poczY;
    int r,g,b;
    *copy = img->copy();

    unsigned char *ptr;
    ptr = img->bits();

    if((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
    {
        clickX = x;
        clickY = y;
        if(tryb == 4)
        {
            b = ptr[szer*4*y + 4 * x];
            g = ptr[szer*4*y + 4 * x + 1];
            r = ptr[szer*4*y + 4 * x + 2];
            if(r != red || g != green || b != blue)
            {
               fill(r,g,b);
            }
        }
    }
    else
    {
        clickX = -1;
        clickY = -1;
    }

    update();
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(tryb == 0)
    {
        linia(event);
    }
    if(tryb == 1)
    {
        okrag(event);
    }
    if(tryb == 2)
    {
        elipsa(event);
    }
    if(tryb == 3)
    {
        wielokat(event);
    }
}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(tryb == 0)
    {
        linia_mouse(event);
    }
    if(tryb == 1)
    {
        okrag_mouse(event);
    }
    if(tryb == 2)
    {
        elipsa_mouse(event);
    }
    if(tryb == 3)
    {
        wielokat_mouse(event);
    }
}

void MyWindow::on_radioButton_clicked()
{
    tryb = 0;
}
void MyWindow::on_radioButton_2_clicked()
{
    tryb = 1;
}
void MyWindow::on_radioButton_3_clicked()
{
    tryb = 2;
}
void MyWindow::on_radioButton_4_clicked()
{
    tryb = 3;
}
void MyWindow::on_pushButton_2_clicked()
{
    tryb = 4;
}
void MyWindow::on_spinBox_valueChanged(int arg1)
{
    boki = arg1;
}

void MyWindow::on_pushButton_clicked()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid())
    {
        red = color.red();
        blue = color.blue();
        green = color.green();
    }
}

void MyWindow::rysujPiksel(int x, int y)
{
    unsigned char *ptr;
    ptr = img->bits();
    if(x >= 0 && y >= 0 && x < szer && y < wys)
    {
        ptr[szer * 4 * y + 4 * x] = blue;
        ptr[szer * 4 * y + 4 * x + 1] = green;
        ptr[szer * 4 * y + 4 * x + 2] = red;
    }
}

void MyWindow::linia(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int pom;
    double a, b, w;

    if(clickX < 0 || clickY < 0)
    {
        return;
    }
    useX = clickX;
    useY = clickY;
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    if(endX < 0)
    {
        endX = 0;
    }
    if(endX > szer)
    {
        endX = szer - 1;
    }
    if(endY < 0)
    {
        endY = 0;
    }
    if(endY > wys)
    {
        endY = wys - 1;
    }
    if(clickX > endX)
    {
        pom = clickX;
        clickX = endX;
        endX = pom;
        pom = clickY;
        clickY = endY;
        endY = pom;
    }

    if(abs(endX - clickX) > abs(endY - clickY))
    {
        a = (endY - clickY) / (double)(endX - clickX);
        b = clickY - a * clickX;
        for(int i = clickX;i >= 0 && i <= endX && i < szer; i++)
        {
            w = a * i + b;
            pom = round(w);
            rysujPiksel(i, pom);
        }
    }
    else
    {
        if(clickY > endY)
        {
            pom = clickX;
            clickX = endX;
            endX = pom;
            pom = clickY;
            clickY = endY;
            endY = pom;
        }
        if(endY - clickY != 0)
        {
            a = (endX - clickX) / (double)(endY - clickY);
        }
        else
        {
            a = 0;
        }
        b = clickX - a * clickY;
        for(int i = clickY; i >= 0 && i <= endY && i < wys; i++)
        {
            w = a * i + b;
            pom = round(w);
            rysujPiksel(pom, i);
        }
    }
    clickX = useX;
    clickY = useY;
    update();
}

void MyWindow::linia_mouse(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int pom;
    double a, b, w;
    *img = copy->copy();

    useX = clickX;
    useY = clickY;
    x -= poczX;
    y -= poczY;

    endX = x;
    endY = y;
    if(endX < 0)
    {
        endX = 0;
    }
    if(endX > szer)
    {
        endX = szer - 1;
    }
    if(endY < 0)
    {
        endY = 0;
    }
    if(endY > wys)
    {
        endY = wys - 1;
    }
    if(clickX > endX)
    {
        pom = clickX;
        clickX = endX;
        endX = pom;
        pom = clickY;
        clickY = endY;
        endY = pom;
    }
    if(abs(endX - clickX) > abs(endY - clickY))
    {
        a = (endY - clickY) / (double)(endX - clickX);
        b = clickY - a * clickX;
        for(int i = clickX;i >= 0 && i <= endX && i < szer; i++)
        {

            w = a * i + b;
            pom = round(w);
            rysujPiksel(i, pom);
        }
    }
    else
    {
        if(clickY > endY)
        {
            pom = clickX;
            clickX = endX;
            endX = pom;
            pom = clickY;
            clickY = endY;
            endY = pom;
        }
        a = (endX - clickX) / (double)(endY - clickY);
        b = clickX - a * clickY;
        for(int i = clickY; i >= 0 && i <= endY && i < wys; i++)
        {

            w = a * i + b;
            pom = (int)round(w);
            rysujPiksel(pom, i);
        }
    }
    clickX = useX;
    clickY = useY;

    update();
}

void MyWindow::okrag(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int r;

    if(clickX < 0 || clickY < 0)
    {
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    r = (clickX - endX) * (clickX - endX) + (clickY - endY) * (clickY - endY);
    for(x = 0; x * x <= r / 2; x++)
    {
        y = sqrt(r - x * x);
        rysujPiksel(clickX + x,clickY + y);
        rysujPiksel(clickX + x,clickY + -y);
        rysujPiksel(clickX + -x,clickY + y);
        rysujPiksel(clickX + -x,clickY + -y);
        rysujPiksel(clickX + y,clickY + x);
        rysujPiksel(clickX + y,clickY + -x);
        rysujPiksel(clickX + -y,clickY + x);
        rysujPiksel(clickX + -y,clickY + -x);
    }
    update();
}

void MyWindow::okrag_mouse(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int r;

    if(clickX < 0 || clickY < 0)
    {
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    r = (clickX - endX) * (clickX - endX) + (clickY - endY) * (clickY - endY);
    for(x = 0; x * x <= r / 2; x++)
    {
        y = sqrt(r - x * x);
        rysujPiksel(clickX + x,clickY + y);
        rysujPiksel(clickX + x,clickY + -y);
        rysujPiksel(clickX + -x,clickY + y);
        rysujPiksel(clickX + -x,clickY + -y);
        rysujPiksel(clickX + y,clickY + x);
        rysujPiksel(clickX + y,clickY + -x);
        rysujPiksel(clickX + -y,clickY + x);
        rysujPiksel(clickX + -y,clickY + -x);
    }
    update();
}

void MyWindow::elipsa(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int a, b;
    double r;

    if(clickX < 0 || clickY < 0)
    {
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    a = abs(clickX - endX);
    b = abs(clickY - endY);
    for(r = 0; r < 2 * M_PI; r += 0.001)
    {
        x = a * cos(r);
        y = b * sin(r);
        rysujPiksel(clickX + x,clickY + y);
        rysujPiksel(clickX + x,clickY + -y);
        rysujPiksel(clickX + -x,clickY + y);
        rysujPiksel(clickX + -x,clickY + -y);
    }
    update();
}

void MyWindow::elipsa_mouse(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int a, b;
    double r;

    if(clickX < 0 || clickY < 0)
    {
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    a = abs(clickX - endX);
    b = abs(clickY - endY);
    for(r = 0; r <= 2 * M_PI; r += 0.001)
    {
        x = a * cos(r);
        y = b * sin(r);
        rysujPiksel(clickX + x,clickY + y);
        rysujPiksel(clickX + x,clickY + -y);
        rysujPiksel(clickX + -x,clickY + y);
        rysujPiksel(clickX + -x,clickY + -y);
    }
    update();
}

void MyWindow::prosta(int startx, int starty, int koniecx, int koniecy)
{
    double a, b;
    int pom;
    int i;
    if(abs(startx - koniecx) > abs(starty - koniecy))
    {
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
        for(i = startx; i <= koniecx; i++)
        {
            pom = a * i + b;
            rysujPiksel(i,pom);
        }
    }
    else
    {
        if(starty > koniecy)
        {
            pom = startx;
            startx = koniecx;
            koniecx = pom;
            pom = starty;
            starty = koniecy;
            koniecy = pom;
        }
        a = (koniecx - startx) / (double) (koniecy - starty);
        b = startx - a * starty;
        for(i = starty; i <= koniecy; i++)
        {
            pom = a * i + b;
            rysujPiksel(pom,i);
        }
    }
}

void MyWindow::wielokat(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int a, b;
    int xx,yy;
    double r;

    if(clickX < 0 || clickY < 0)
    {
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    a = abs(clickX - endX);
    b = abs(clickY - endY);
    x = a * cos(0);
    y = b * sin(0);
    for(r = 2 * M_PI / boki; r <= 2 * M_PI + 0.1; r += 2 * M_PI / boki)
    {
        xx = a * cos(r);
        yy = b * sin(r);
        prosta(clickX + x,clickY + y,clickX + xx,clickY + yy);
        x = xx;
        y = yy;
    }
    update();
}

void MyWindow::wielokat_mouse(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int a, b;
    int xx,yy;
    double r;

    if(clickX < 0 || clickY < 0){
        return;
    }
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    endX = x;
    endY = y;
    a = abs(clickX - endX);
    b = abs(clickY - endY);
    x = a * cos(0);
    y = b * sin(0);
    for(r = 2 * M_PI / boki; r <= 2 * M_PI + 0.1; r += 2 * M_PI / boki)
    {
        xx = a * cos(r);
        yy = b * sin(r);
        prosta(clickX + x,clickY + y,clickX + xx,clickY + yy);
        x = xx;
        y = yy;
    }
    update();
}

void MyWindow::fill(int r, int g, int b){
    stack<pair<int, int>> stos;
    unsigned char *ptr;
    ptr = img->bits();
    int Rpunkt,Gpunkt,Bpunkt;
    int z,x;
    stos.push(make_pair(clickX,clickY));
    pair<int, int> punkt;
    while(!stos.empty())
    {
        punkt = stos.top();
        stos.pop();
        Bpunkt = ptr[szer*4*punkt.second + 4*punkt.first];
        Gpunkt = ptr[szer*4*punkt.second + 4*punkt.first + 1];
        Rpunkt = ptr[szer*4*punkt.second + 4*punkt.first + 2];

        if(r == Rpunkt && g == Gpunkt && b == Bpunkt)
        {
            z = x = punkt.first;
            Bpunkt = ptr[szer*4*punkt.second + 4 * z];
            Gpunkt = ptr[szer*4*punkt.second + 4 * z + 1];
            Rpunkt = ptr[szer*4*punkt.second + 4 * z + 2];
            while(r == Rpunkt && g == Gpunkt && b == Bpunkt && z >= 0)
            {
                z--;
                Bpunkt = ptr[szer*4*punkt.second + 4 * z];
                Gpunkt = ptr[szer*4*punkt.second + 4 * z + 1];
                Rpunkt = ptr[szer*4*punkt.second + 4 * z + 2];
            }
            Bpunkt = ptr[szer*4*punkt.second + 4 * x];
            Gpunkt = ptr[szer*4*punkt.second + 4 * x + 1];
            Rpunkt = ptr[szer*4*punkt.second + 4 * x + 2];
            while(r == Rpunkt && g == Gpunkt && b == Bpunkt && x < szer)
            {
                x++;
                Bpunkt = ptr[szer*4*punkt.second + 4 * x];
                Gpunkt = ptr[szer*4*punkt.second + 4 * x + 1];
                Rpunkt = ptr[szer*4*punkt.second + 4 * x + 2];
            }

            for(int i = z + 1; i < x; i++)
            {
                rysujPiksel(i,punkt.second);
                if(punkt.second + 1 < wys)
                {
                    Bpunkt = ptr[szer*4*(punkt.second+1) + 4 * i];
                    Gpunkt = ptr[szer*4*(punkt.second+1) + 4 * i + 1];
                    Rpunkt = ptr[szer*4*(punkt.second+1) + 4 * i + 2];
                    if(r == Rpunkt && g == Gpunkt && b == Bpunkt)
                    {
                        stos.push(make_pair(i,punkt.second+1));
                    }
                }
                if(punkt.second - 1 >= 0)
                {
                    Bpunkt = ptr[szer*4*(punkt.second-1) + 4 * i];
                    Gpunkt = ptr[szer*4*(punkt.second-1) + 4 * i + 1];
                    Rpunkt = ptr[szer*4*(punkt.second-1) + 4 * i + 2];


                    if(r == Rpunkt && g == Gpunkt && b == Bpunkt)
                    {
                        stos.push(make_pair(i,punkt.second-1));
                    }
                }
            }
        }
    }
}

