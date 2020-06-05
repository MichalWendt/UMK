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
    QImage *img;
    QImage *kopia;
    QImage *oryginal;

    int szer;
    int wys;
    int poczX;
    int poczY;

    double obrot = 0;
    int pion = 0;
    int poziom = 0;
    int krzywapion = 0;
    int krzywapoziom = 0;
    double skalowanieOX = 1;
    double skalowanieOY = 1;
    double pochylenieOX = 0;
    double pochylenieOY = 0;
    double przesuniecie[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    double MacierzSkal[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    double MacierzObrot[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    double MacierzPochylenie[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    double wynik[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    double pomoc[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

    void zamaluj();
    void wyzeruj();
    void zamaluj_kopie();
    void przeksztalcanie();
    void Przesuniecie();
    void Obrot();
    void Scal();
    void Pochylenie();
    void Mnozenie(double dane[3][3]);
    double Interpolacja(int x, int y, double dx);

private slots:
    void paintEvent(QPaintEvent*);
    void on_szerokosc_valueChanged(int value);
    void on_wysokosc_valueChanged(int value);
    void on_rotacja_sliderMoved(int position);
    void on_horizontalSlider_valueChanged(int value);
    void on_scalszer_valueChanged(int value);
    void on_scalwys_valueChanged(int value);
    void on_verticalSlider_valueChanged(int value);
    void on_pushButton_clicked();
};

#endif
