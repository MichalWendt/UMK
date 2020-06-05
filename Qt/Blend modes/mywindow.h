#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QImage>

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
    QImage *obrazy[6];
    bool pokazuje[6]={true,false,false,false,false,false};
    int tryb[6]={0,0,0,0,0,0};
    int moc[6]={0,0,0,0,0,0};
    int szer;
    int wys;
    int poczX;
    int poczY;

    void zamaluj();
    void blend();
    int Normal(int b);
    int Average(int a, int b);
    int Multiply(int a, int b);
    int Screen(int a, int b);
    int Darken(int a, int b);
    int Lighten(int a, int b);
    int Difference(int a, int b);
    int Overlay(int a, int b);
    int HardLight(int a, int b);
    int Sum(int a, int b);
    int Xor(int a, int b);
    int And(int a, int b);
    int Or(int a, int b);

private slots:
    void paintEvent(QPaintEvent*);
    void on_exitButton_clicked();

    void on_checkBox_1_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);
    void on_checkBox_5_stateChanged(int arg1);
    void on_checkBox_6_stateChanged(int arg1);
    void on_comboBox_1_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(int index);
    void on_comboBox_3_currentIndexChanged(int index);
    void on_comboBox_4_currentIndexChanged(int index);
    void on_comboBox_5_currentIndexChanged(int index);
    void on_comboBox_6_currentIndexChanged(int index);
    void on_verticalSlider_1_valueChanged(int value);
    void on_verticalSlider_2_valueChanged(int value);
    void on_verticalSlider_3_valueChanged(int value);
    void on_verticalSlider_4_valueChanged(int value);
    void on_verticalSlider_5_valueChanged(int value);
    void on_verticalSlider_6_valueChanged(int value);
};

#endif
