#include "mywindow.h"
#include "ui_mywindow.h"

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
    obrazy[0] = new QImage(":/picture_1.jpg");
    obrazy[1] = new QImage(":/picture_2.jpg");
    obrazy[2] = new QImage(":/picture_3.jpg");
    obrazy[3] = new QImage(":/picture_4.jpg");
    obrazy[4] = new QImage(":/picture_5.jpg");
    obrazy[5] = new QImage(":/picture_6.jpg");
    zamaluj();
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

void MyWindow::zamaluj()
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;

    for(i = 0; i < wys; i++)
    {
        for(j = 0; j < szer; j++)
        {
            ptr[szer*4*i + 4*j] = 255;
            ptr[szer*4*i + 4*j + 1] = 255;
            ptr[szer*4*i + 4*j + 2] = 255;
        }
    }
    update();
}

// ------------------- tryby mieszania
int MyWindow::Normal(int b)
{
    return b;
}

int MyWindow::Average(int a, int b)
{
    return ((a+b)/2);
}

int MyWindow::Multiply(int a, int b)
{
    return ((a*b) >> 8);
}

int MyWindow::Screen(int a, int b)
{
    return (255 - (((255-a) * (255-b)) >> 8));
}

int MyWindow::Darken(int a, int b)
{
    return (a < b ? a : b);
}

int MyWindow::Lighten(int a, int b)
{
    return (a > b ? a : b);
}

int MyWindow::Difference(int a, int b)
{
    return (abs(a-b));
}

int MyWindow::Overlay(int a, int b)
{
    return (a < 128 ? (a*b) >> 7 : 255 - ((255-a) * (255-b) >> 7));
}

int MyWindow::HardLight (int a, int b)
{
    return (b < 128 ? (a*b) >> 7 : 255 - ((255-b) * (255-a) >> 7));
}

int MyWindow::Sum(int a, int b)
{
    return (a+b)%256;
}

int MyWindow::Xor(int a, int b)
{
    return (a^b);
}

int MyWindow::And(int a, int b)
{
    return (a&b);
}

int MyWindow::Or(int a, int b)
{
    return (a|b);
}

// --------------- funkcja mieszajaca
void MyWindow::blend()
{
    int i,j;
    int obraz;
    int R,G,B;
    int R2,G2,B2;
    double alfa,pom;
    unsigned char *podstawa;
    unsigned char *nalozony;
    zamaluj();
    for(obraz = 5; obraz >= 0; obraz--)
    {
        if(pokazuje[obraz])
        {
            alfa = moc[obraz] / 100.0;
            pom = 1.0 - alfa;
            for(i = 0; i < wys; i++)
            {
                podstawa = img->scanLine(i);
                nalozony = obrazy[obraz]->scanLine(i);
                for(j = 0; j < szer; j++)
                {
                   R = podstawa[4 * j + 2];
                   G = podstawa[4 * j + 1];
                   B = podstawa[4 * j];
                   R2 = nalozony[4 * j + 2];
                   G2 = nalozony[4 * j + 1];
                   B2 = nalozony[4 * j];
                   switch(tryb[obraz])
                   {
                       case 0 :
                           R2 = Normal(R2);
                           G2 = Normal(G2);
                           B2 = Normal(B2);
                           break;

                       case 1:
                           R2 = Average(R,R2);
                           G2 = Average(G,G2);
                           B2 = Average(B,B2);
                           break;

                       case 2:
                           R2 = Multiply(R,R2);
                           G2 = Multiply(G,G2);
                           B2 = Multiply(B,B2);
                           break;

                       case 3:
                           R2 = Screen(R,R2);
                           G2 = Screen(G,G2);
                           B2 = Screen(B,B2);
                           break;

                       case 4:
                           R2 = Darken(R,R2);
                           G2 = Darken(G,G2);
                           B2 = Darken(B,B2);
                           break;

                       case 5:
                           R2 = Lighten(R,R2);
                           G2 = Lighten(G,G2);
                           B2 = Lighten(B,B2);
                           break;

                       case 6:
                           R2 = Difference(R,R2);
                           G2 = Difference(G,G2);
                           B2 = Difference(B,B2);
                           break;

                       case 7:
                           R2 = Overlay(R,R2);
                           G2 = Overlay(G,G2);
                           B2 = Overlay(B,B2);
                           break;

                       case 8:
                           R2 = HardLight(R,R2);
                           G2 = HardLight(G,G2);
                           B2 = HardLight(B,B2);
                           break;

                       case 9:
                           R2 = Sum(R,R2);
                           G2 = Sum(G,G2);
                           B2 = Sum(B,B2);
                           break;

                       case 10:
                           R2 = Xor(R,R2);
                           G2 = Xor(G,G2);
                           B2 = Xor(B,B2);
                           break;

                       case 11:
                           R2 = And(R,R2);
                           G2 = And(G,G2);
                           B2 = And(B,B2);
                           break;

                       case 12:
                           R2 = Or(R,R2);
                           G2 = Or(G,G2);
                           B2 = Or(B,B2);
                           break;
                   }
                   // wzor na C = alfa * kolor pierwszoplanowy + (1-alfa) * kolor tla)
                   // odwrocilem aby miec niewidoczny obraz na 0 i widoczny na 100
                   podstawa[4 * j + 2] = alfa * R2 + pom * podstawa[4 * j + 2];
                   podstawa[4 * j + 1] = alfa * G2 + pom * podstawa[4 * j + 1];
                   podstawa[4 * j] = alfa * B2 + pom * podstawa[4 * j];
                }
            }
        }
    }
    update();
}

// ---------- pokazywanie lub ukrywanie obrazow
void MyWindow::on_checkBox_1_stateChanged(int status)
{
    pokazuje[0] = status;
    blend();
}

void MyWindow::on_checkBox_2_stateChanged(int status)
{
    pokazuje[1] = status;
    blend();
}

void MyWindow::on_checkBox_3_stateChanged(int status)
{
    pokazuje[2] = status;
    blend();
}

void MyWindow::on_checkBox_4_stateChanged(int status)
{
    pokazuje[3] = status;
    blend();
}

void MyWindow::on_checkBox_5_stateChanged(int status)
{
    pokazuje[4] = status;
    blend();
}
void MyWindow::on_checkBox_6_stateChanged(int status)
{
    pokazuje[5] = status;
    blend();
}

// ----------------ustawianie trybu mieszania
void MyWindow::on_comboBox_1_currentIndexChanged(int index)
{
    tryb[0] = index;
    blend();
}

void MyWindow::on_comboBox_2_currentIndexChanged(int index)
{
    tryb[1] = index;
    blend();
}

void MyWindow::on_comboBox_3_currentIndexChanged(int index)
{
    tryb[2] = index;
    blend();
}

void MyWindow::on_comboBox_4_currentIndexChanged(int index)
{
    tryb[3] = index;
    blend();
}

void MyWindow::on_comboBox_5_currentIndexChanged(int index)
{
    tryb[4] = index;
    blend();
}
void MyWindow::on_comboBox_6_currentIndexChanged(int index)
{
    tryb[5] = index;
    blend();
}

// ------------ suwaki nasilenia obrazu
void MyWindow::on_verticalSlider_1_valueChanged(int przezroczystosc)
{
    moc[0] = przezroczystosc;
    blend();
}

void MyWindow::on_verticalSlider_2_valueChanged(int przezroczystosc)
{
    moc[1] = przezroczystosc;
    blend();
}

void MyWindow::on_verticalSlider_3_valueChanged(int przezroczystosc)
{
    moc[2] = przezroczystosc;
    blend();
}

void MyWindow::on_verticalSlider_4_valueChanged(int przezroczystosc)
{
    moc[3] = przezroczystosc;
    blend();
}

void MyWindow::on_verticalSlider_5_valueChanged(int przezroczystosc)
{
    moc[4] = przezroczystosc;
    blend();
}

void MyWindow::on_verticalSlider_6_valueChanged(int przezroczystosc)
{
    moc[5] = przezroczystosc;
    blend();
}
