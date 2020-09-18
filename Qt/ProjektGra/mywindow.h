#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QTimer>
#include <QKeyEvent>

using namespace std;


namespace Ui {
    class MyWindow;
}

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MyWindow(QWidget *parent = nullptr);
    ~MyWindow();

private:
    Ui::MyWindow *ui;
    QImage *img;
    QTimer *timer;
    int time;       //aktualny czas
    int ostatni;    //ostatni czas
    bool first = false; //czy to pierwsze wyświetlenie mapy
    int szer;       //wielkosc planszy
    int wys;
    int poziome = 20;   //ilosc scian sfery
    int pionowe = 20;
    int poczX;      //poczatek układu współrzędnych
    int poczY;
    int mapa = 3;   //wybór mapy

    int przesuniecieOX = 0; //przesunięcie sfery względem osi
    int przesuniecieOY = 0;
    int przesuniecieOZ = 0;
    int swiatloOX = 0;  //przesunięcie światła wzlędem osi
    int swiatloOY = 0;
    int swiatloOZ = 500;
    double skalowanieOX = 1;    //wielkość sfery
    double skalowanieOY = 1;
    double skalowanieOZ = 1;
    double obrotOX = 0; //obrót sfery względem własnych osi
    double obrotOY = 0;
    double obrotOZ = 0;
    double RED = 0.5;   //nasilenie kolorów na sferze
    double GREEN = 0.5;
    double BLUE = 0.5;

    // Funkcje
    void czysc();   //funckja czyszcząca obszar wyświetlany
    void rysowanie();   //funkcja dodająca obiekty do sceny (oraz tworząca scene i obiekty)
    void mapa1();   //funkcje wywołujące konkretne mapy
    void mapa2();
    void mapa3();

private slots:
    void keyPressEvent(QKeyEvent *event);   //funkcja obsługi klawiszy (W,S,A,D)
    void funkcjazegar();    //funkcja stopera
    void paintEvent(QPaintEvent*);
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_4_valueChanged(int value);
    void on_horizontalSlider_5_valueChanged(int value);
    void on_horizontalSlider_6_valueChanged(int value);
    void on_dial_valueChanged(int value);
    void on_dial_2_valueChanged(int value);
    void on_dial_3_valueChanged(int value);
    void on_pushButton_clicked();
    void on_gora_clicked();
    void on_dol_clicked();
    void on_prawo_clicked();
    void on_lewo_clicked();
    void on_draw1Button_clicked();
    void on_draw2Button_clicked();
    void on_draw3Button_clicked();
    void on_horizontalSlider_16_valueChanged(int value);
    void on_horizontalSlider_17_valueChanged(int value);
    void on_horizontalSlider_18_valueChanged(int value);
    void on_horizontalSlider_13_valueChanged(int value);
    void on_horizontalSlider_14_valueChanged(int value);
    void on_horizontalSlider_15_valueChanged(int value);
    void on_pushButton_3_clicked();
    void on_spinBox_valueChanged(int value);
    void on_spinBox_2_valueChanged(int value);
};

#endif // MYWINDOW_H
