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
    int startX;
    int startY;
    int endX;
    int endY;
    bool first = true;
    int kolor = 0;

    std::vector<std::pair<int,int>> punkty;
    std::vector<int> przeciecia;

    void rysujPiksel(int x, int y);
    void czysc();
    void linia();

private slots:

    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void on_pushButton_clicked();
};

#endif // MYWINDOW_H
