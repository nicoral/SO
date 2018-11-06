#ifndef DIALOG_H
#define DIALOG_Hq
#include "processcontrolblock.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QDialog>
#include <QPointF>
#include <QPainter>
#include <iostream>
#include <QMainWindow>

using namespace std;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void drawCircle(int,int);
    void drawProceso(int);
    void clear();
    void Cambio_estado(int,int);
    ~Dialog();
    int cant=0;

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


private:
    ProcessControlBlock *PCB=new ProcessControlBlock();
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    ///putY m_putYTransaccion;
    int m_posX=0;
    int m_posY=0;
    int m_ordenes=1;
    int tam=20;
    ///transacciones m_schedule;
};

#endif // DIALOG_H
