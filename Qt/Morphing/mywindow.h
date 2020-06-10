#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <vector>
#include <utility>

using namespace std;
namespace Ui {
    class MyWindow;
}

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MyWindow(QWidget *parent = 0);

    ~MyWindow();

private:

    Ui::MyWindow *ui;

    QImage *img;
    QImage *img2;
    QImage *img3;
    QImage **wynik;
    QImage *copy;
    QImage *copy2;
    int szer;
    int wys;
    int poczX,poczX2,poczX3;
    int poczY,poczY2,poczY3;
    unsigned long long licznik = 1;
    unsigned long long podzial = 2;
    pair<int,int> **punkty;
    pair<int,int> **punkty2;
    int moveX = 0,moveY = 0;
    bool kontorla = false;
    bool kontorla2 = false;


    void prosta(int, int, int, int, int, int, int);
    void prosta2(int, int, int, int, int, int, int);

    void sprawdz(int x, int y);
    void sprawdz2(int x, int y);

    void rysujPiksel(int x, int y, int r, int g, int b);
    void rysujPiksel2(int x, int y, int r, int g, int b);
    void rysujPiksel3(int x, int y, int r, int g, int b, int i);

    void rysujPunkty(int x, int y, int r, int g, int b);
    void rysujPunkty2(int x, int y, int r, int g, int b);

    void punkt();
    void krzywe();
    void punkt2();
    void krzywe2();
    void Morphing(int s, pair<int,int> A, pair<int,int> B, pair<int,int> C, pair<int,int> At, pair<int,int> Bt, pair<int,int> Ct);
    void czysc();

    double Interpolacja(int x,int y,double dx);

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_2_valueChanged(int arg1);
};

#endif
