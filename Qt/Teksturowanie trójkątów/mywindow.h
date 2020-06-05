#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <vector>
#include <utility>

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
    QImage *copy;
    QImage *copy2;

    int szer;
    int wys;
    int poczX,poczX2;
    int poczY,poczY2;
    int licznik = 0;
    int licznik2 = 0;
    std::vector<std::pair<int, int>> punkty;
    std::vector<std::pair<int, int>> punkty2;
    std::vector<std::pair<int, int>>::iterator przesun;
    std::vector<std::pair<int, int>>::iterator przesun2;
    bool kontorla = false;
    bool kontorla2 = false;
    void prosta(int, int, int, int, int, int, int);
    void prosta2(int, int, int, int, int, int, int);
    void sprawdz(int x, int y);
    void sprawdz2(int x, int y);
    void rysujPiksel(int x, int y, int r, int g, int b);
    void rysujPiksel2(int x, int y, int r, int g, int b);
    void rysujPunkty(int x, int y);
    void rysujPunkty2(int x, int y);
    void punkt();
    void punkt2();
    void krzywe();
    void krzywe2();
    void Teksturowanie();
    void czysc();
    double Interpolacja(int x,int y,double dx);

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

};

#endif
