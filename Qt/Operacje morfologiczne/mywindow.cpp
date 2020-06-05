#include "mywindow.h"
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
    kopia = new QImage(szer,wys,QImage::Format_RGB32);
    oryginal = new QImage(szer,wys,QImage::Format_RGB32);
    czysc();
    *kopia = *oryginal = img->copy();
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

void MyWindow::on_exitButton_clicked()
{
    qApp->quit();
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
}

void MyWindow::toBinary(){
    unsigned char *ptr;
    int i,j;
    int r,g,b;
    ptr = img->bits();
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            b = ptr[szer*4*i + 4*j];
            g = ptr[szer*4*i + 4*j + 1];
            r = ptr[szer*4*i + 4*j + 2];
            r = 0.299 * r + 0.587 * g + 0.114 * b;
            if(r < 128){
                r = 0;
            }
            else {
                r = 255;
            }
            ptr[szer*4*i + 4*j] = r;
            ptr[szer*4*i + 4*j + 1] = r;
            ptr[szer*4*i + 4*j + 2] = r;
        }
    }
    update();
}

void MyWindow::on_comboBox_currentIndexChanged(int index)
{
    rozmiar = 1 + index;
}

bool MyWindow::check_black(int x, int y){
    unsigned char *ptr;
    if(x < 0 || x >= wys || y < 0 || y >= szer)
        return false;
    ptr = img->bits();
    if(ptr[szer*4*x + 4*y] == 0 &&
            ptr[szer*4*x + 4*y + 1] == 0 &&
                ptr[szer*4*x + 4*y + 2] == 0)
        return true;
   return false;
}

bool MyWindow::check_white(int x, int y){
    unsigned char *ptr;
    if(x < 0 || x >= wys || y < 0 || y >= szer)
        return true;
    ptr = img->bits();
    if(ptr[szer*4*x + 4*y] == 0 &&
            ptr[szer*4*x + 4*y + 1] == 0 &&
                ptr[szer*4*x + 4*y + 2] == 0)
        return false;
   return true;
}

void MyWindow::on_pushButton_3_clicked()
{
    // Dyladacja
    *kopia = img->copy();
    unsigned char *ptr;
    unsigned char *org;
    int i,j,k,n;
    bool wykonaj;
    ptr = kopia->bits();
    org = img->bits();
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            if(org[szer*4*i + 4*j] == 255 &&
                    org[szer*4*i + 4*j + 1] == 255 &&
                        org[szer*4*i + 4*j + 2] == 255)
            {
                for(n =  - rozmiar, wykonaj = false; !wykonaj && n <= rozmiar; n++){
                    for(k = - rozmiar; k <= rozmiar; k++){
                        if(check_black(i+n,j+k)){
                            ptr[szer*4*i + 4*j] = 0;
                            ptr[szer*4*i + 4*j + 1] = 0;
                            ptr[szer*4*i + 4*j + 2] = 0;
                            wykonaj = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    *img = kopia->copy();
    update();
}

void MyWindow::on_pushButton_4_clicked()
{
    // Erozja
    *kopia = img->copy();
    unsigned char *ptr;
    unsigned char *org;
    int i,j,k,n;
    bool wykonaj;
    ptr = kopia->bits();
    org = img->bits();
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            if(org[szer*4*i + 4*j] == 0 &&
                    org[szer*4*i + 4*j + 1] == 0 &&
                        org[szer*4*i + 4*j + 2] == 0)
            {
                for(n =  - rozmiar, wykonaj = false; !wykonaj && n <= rozmiar; n++){
                    for(k = - rozmiar; k <= rozmiar; k++){
                        if(check_white(i+n,j+k)){
                            ptr[szer*4*i + 4*j] = 255;
                            ptr[szer*4*i + 4*j + 1] = 255;
                            ptr[szer*4*i + 4*j + 2] = 255;
                            wykonaj = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    *img = kopia->copy();
    update();
}

void MyWindow::on_pushButton_1_clicked()
{
    QString plik = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.jpg *.png *.jpeg *.bmp *.gif)"));
    if(QString::compare(plik,QString()) != 0){
        delete img;
        delete oryginal;
        delete kopia;
        img = new QImage(plik);
        oryginal = new QImage(plik);
        kopia = new QImage(plik);
        toBinary();
        *oryginal = img->copy();
        *kopia = img->copy();
    }
}

void MyWindow::on_pushButton_2_clicked()
{
    *img = oryginal->copy();
    update();
}

void MyWindow::on_pushButton_5_clicked()
{
    on_pushButton_4_clicked();
    on_pushButton_3_clicked();
}

void MyWindow::on_pushButton_6_clicked()
{
    on_pushButton_3_clicked();
    on_pushButton_4_clicked();
}
