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

    int szer;
    int wys;
    int poczX;
    int poczY;

    void czysc();
    void hsv(int value, double S, double V, int *r, int *g, int *b);
    int min(int,int);
    int max(int,int);

private slots:
    void on_exitButton_clicked();
    void paintEvent(QPaintEvent*);

    void on_verticalSlider_valueChanged(int value);
    void on_verticalSlider_2_valueChanged(int value);
    void on_verticalSlider_3_valueChanged(int value);
    void on_verticalSlider_4_valueChanged(int value);
    void on_verticalSlider_5_valueChanged(int value);
    void on_verticalSlider_6_valueChanged(int value);
};

#endif
