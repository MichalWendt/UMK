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

    // Deklaracja destruktora
    ~MyWindow();

private:

    Ui::MyWindow *ui;
    QImage *img;
    QImage *copy;
    int szer;
    int wys;
    int poczX;
    int poczY;
    int aktuX;
    int aktuY;
    int tryb = 1;
    int kolor = 0;
    int boki = 0;
    int pX = -1,pY = -1, lX, lY;
    void rysuj1();
    void rysuj2();
    void rysujPixel(int,int);
    void okrag(QMouseEvent *event);
    void okrag_mouse(QMouseEvent *event);
    void elipsa(QMouseEvent *event);
    void elipsa_mouse(QMouseEvent *event);
    void prosta(int,int,int,int);
    void wielokat(QMouseEvent *event);
    void wielokat_mouse(QMouseEvent *event);
private slots:

    void on_draw2Button_clicked();
    void on_draw1Button_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void on_radioButton_1_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_spinBox_valueChanged(int arg1);
};

#endif // MYWINDOW_H
