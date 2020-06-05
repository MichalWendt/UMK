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
    QImage *copy;

    int szer;
    int wys;
    int poczX;
    int poczY;
    int licznik = -1;
    int linii = 0;
    std::vector<std::pair<int, int> > punkty;
    std::vector<std::pair<int, int> >::iterator przesun;
    bool kontorla = false;
    bool usun = false;
    void prosta(int, int, int, int, int, int, int);

    void czysc();
    void sprawdz(int x, int y);
    void rysujPiksel(int x, int y, int r, int g, int b);
    void rysujPunkty(int x, int y);
    void punkt();
    void krzywe();

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void on_pushButton_clicked();
};

#endif // MYWINDOW_H
