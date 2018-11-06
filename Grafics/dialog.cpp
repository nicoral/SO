#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}
void Dialog::drawProceso(int num)
{
    for(int i=0;i<num*(this->tam*3+10);i+=this->tam*3+10)
        drawCircle(0,i);
}

void Dialog::drawCircle(int posX,int posY){
    int tam=this->tam;
    QFont font;
    font.setPixelSize(10);
    font.setBold(false);
    font.setFamily("Nokia Pure Text");
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    QPen blackPen1(Qt::black);
    blackPen1.setWidth(tam/10);

        scene->addEllipse(posX,posY,tam,tam,blackPen,redBrush);
        scene->addEllipse(posX+tam*2,posY,tam,tam,blackPen,redBrush);
        scene->addEllipse(posX+tam*2,posY+tam*2,tam,tam,blackPen,redBrush);
        scene->addEllipse(posX+tam*4,posY,tam,tam,blackPen,redBrush);
        scene->addEllipse(posX+tam*6,posY,tam,tam,blackPen,redBrush);

        scene->addLine(posX+tam,posY+tam/2,posX+tam*2,posY+tam/2,blackPen1);
        scene->addLine(posX+tam*3,posY+tam/2,posX+tam*4,posY+tam/2,blackPen1);
        scene->addLine(posX+tam*5,posY+tam/2,posX+tam*6,posY+tam/2,blackPen1);
        scene->addLine(posX+tam*2+tam/2,posY+tam,posX+tam*2+tam/2,posY+tam*2,blackPen1);
        scene->addLine(posX+tam*3,posY+tam*2+tam/2,posX+tam*4+tam/2,posY+tam,blackPen1);

}
void Dialog::Cambio_estado(int estado,int proce)
{
       int x=((estado-1)*2)*this->tam,y=(proce-1)*(this->tam*3+10);
       QBrush yellowBrush(Qt::yellow);
       QPen blackPen(Qt::black);
       blackPen.setWidth(1);
       drawCircle(0,y);
       scene->addEllipse(x,y,this->tam,this->tam,blackPen,yellowBrush);
}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::clear()
{
    ui->lineEdit->clear();
    ui->lineEdit_3->clear();
}

void Dialog::on_pushButton_clicked()
{
    ofstream File("Infor.txt",std::ios_base::app);
    bool recur=ui->checkBox->isChecked();
    QString nom,tiem;
    nom=ui->lineEdit->text();
    tiem=ui->lineEdit_3->text();
    string* nombre;
    nombre=new string(nom.toStdString().c_str());
    int tiempo=tiem.toInt(),prio=ui->comboBox->currentText().toInt();
    Process *P=new Process(nombre,prio,tiempo,recur);
    P->print(File);
    PCB->addprocess(P);
    cant=cant+1;
    clear();
}

void Dialog::on_pushButton_2_clicked()
{
    close();
}


void Dialog::on_pushButton_3_clicked()
{
    drawProceso(cant);
    PCB->executeProcess();
    PCB->inform();

}
