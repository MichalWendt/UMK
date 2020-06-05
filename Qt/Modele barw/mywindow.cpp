#include "mywindow.h"
#include "ui_mywindow.h"
#include <QDebug>
#include <math.h>

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

int MyWindow::min(int a, int b)
{
    if(a < b)
        return a;
    return b;
}

int MyWindow::max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}

void MyWindow::czysc()
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;

    for(i = 0; i < wys; i++)
    {
        for(j = 0; j < szer; j++)
        {
            ptr[szer*4*i + 4 * j] = 255; // Skladowa BLUE
            ptr[szer*4*i + 4 * j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4 * j + 2] = 255; // Skladowa RED
        }
    }
}

void MyWindow::on_verticalSlider_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;

    for(i = 0; i < wys; i++)
    {
        for(j = 0; j < szer; j++)
        {
            ptr[szer*4*i + 4 * j] = 255 - i/2; // Skladowa BLUE
            ptr[szer*4*i + 4 * j + 1] = j/2; // Skladowa GREEN
            ptr[szer*4*i + 4 * j + 2] = value; // Skladowa RED
        }
    }
    update();
}

void MyWindow::on_verticalSlider_2_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;

    for(i = 0; i < wys; i++)
    {
        for(j = 0; j < szer; j++)
        {
            ptr[szer*4*i + 4 * j] = 255 - i/2; // Skladowa BLUE
            ptr[szer*4*i + 4 * j + 1] = value; // Skladowa GREEN
            ptr[szer*4*i + 4 * j + 2] = j/2; // Skladowa RED
        }
    }
    update();
}

void MyWindow::on_verticalSlider_3_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    for(i = 0; i < wys; i++)
    {
        for(j = 0; j < szer; j++)
        {
            ptr[szer*4*i + 4 * j] = value; // Skladowa BLUE
            ptr[szer*4*i + 4 * j + 1] = j/2; // Skladowa GREEN
            ptr[szer*4*i + 4 * j + 2] = 255 - i/2; // Skladowa RED
        }
    }
    update();
}

void MyWindow::hsv(int H, double S, double V, int *R, int *G, int *B)
{
    double C, X, m, h1 = H/60.0;
    double r, g, b;
    C = V * S;
    X = C * (1.0 - abs(fmod(h1,2) - 1.0));
    if(h1>=0 && h1<1){r = C; g = X; b = 0;}
    if(h1>=1 && h1<2){r = X; g = C; b = 0;}
    if(h1>=2 && h1<3){r = 0; g = C; b = X;}
    if(h1>=3 && h1<4){r = 0; g = X; b = C;}
    if(h1>=4 && h1<5){r = X; g = 0; b = C;}
    if(h1>=5 && h1<6){r = C; g = 0; b = X;}
    m = V - C;
    *R = (r + m) * 255;
    *G = (g + m) * 255;
    *B = (b + m) * 255;

}

void MyWindow::on_verticalSlider_4_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    int r,g,b;

    for(i = 0; i < wys; i++)
    {
        for(j = 0; j < szer; j++)
        {
            hsv(value, 1.0*(szer - j)/szer,1.0*(wys - i)/wys,&r,&g,&b);
            ptr[szer*4*i + 4 * j] = b; // Skladowa BLUE
            ptr[szer*4*i + 4 * j + 1] = g; // Skladowa GREEN
            ptr[szer*4*i + 4 * j + 2] = r; // Skladowa RED
        }
    }
    update();
}

void MyWindow::on_verticalSlider_5_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    int r,g,b;

    for(i = 0; i < wys; i++)
    {
        for(j = 0; j < szer; j++)
        {
            hsv(360.0 * j/szer, value / 100.0,1.0*(wys - i)/wys,&r,&g,&b);
            ptr[szer*4*i + 4 * j] = b; // Skladowa BLUE
            ptr[szer*4*i + 4 * j + 1] = g; // Skladowa GREEN
            ptr[szer*4*i + 4 * j + 2] = r; // Skladowa RED
        }
    }
    update();
}

void MyWindow::on_verticalSlider_6_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    int r,g,b;

    for(i = 0; i < wys; i++)
    {
        for(j = 0; j < szer; j++)
        {
            hsv(360.0 * j/szer, 1.0 * i/wys, value / 100.0,&r,&g,&b);
            ptr[szer*4*i + 4 * j] = b; // Skladowa BLUE
            ptr[szer*4*i + 4 * j + 1] = g; // Skladowa GREEN
            ptr[szer*4*i + 4 * j + 2] = r; // Skladowa RED
        }
    }
    update();
}
