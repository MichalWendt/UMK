#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QFileDialog>
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

    QImage *img,*kopia,*oryginal;

    int szer;
    int wys;
    int poczX;
    int poczY;
    int rozmiar = 1;

    void czysc();
    void toBinary();
    bool check_black(int,int);
    bool check_white(int,int);

private slots:
    void paintEvent(QPaintEvent*);
    void on_exitButton_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
};

#endif
