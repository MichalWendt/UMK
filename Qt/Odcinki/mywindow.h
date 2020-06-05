#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <cmath>
#include <QImage>
#include <QMouseEvent>

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
    QImage *copy;

    int szer;
    int wys;
    int poczX;
    int poczY;
    double startX;
    double startY;
    double aktuX;
    double aktuY;
    int kolor = 0;
    int pX = -1,pY = -1, lX, lY;

    void rysuj1();
    void rysuj2();
    void rysujPixel(int,int);
    void prosta(int,int,int,int);

private slots:
    void on_draw2Button_clicked();
    void on_draw1Button_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

};

#endif // MYWINDOW_H
