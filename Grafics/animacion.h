#ifndef ANIMACION_H
#define ANIMACION_H
#include <QWidget>

class animacion : public QWidget
{
    Q_OBJECT
public:
    animacion(QWidget *parent=0);
protected:
    ///void paintEvent(QPaintEvent *event);
};

#endif // ANIMACION_H
