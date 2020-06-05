#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
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

    int clickX;
    int clickY;
    int kolor;
    int tryb = 0;
    int boki = 10;
    int red = 255, green = 255, blue = 255;

    void rysujPiksel(int x, int y);
    void prosta(int,int,int,int);
    void czysc();
    void czysc2();
    void linia(QMouseEvent *event);
    void linia_mouse(QMouseEvent *event);
    void okrag(QMouseEvent *event);
    void okrag_mouse(QMouseEvent *event);
    void elipsa(QMouseEvent *event);
    void elipsa_mouse(QMouseEvent *event);
    void wielokat(QMouseEvent *event);
    void wielokat_mouse(QMouseEvent *event);
    void fill(int r, int g, int b);

private slots:

    void on_cleanButton_clicked();
    void on_cleanButton_2_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // MYWINDOW_H
