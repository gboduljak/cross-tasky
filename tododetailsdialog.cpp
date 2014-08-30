#include "tododetailsdialog.h"
#include "ui_tododetailsdialog.h"
#include <QMouseEvent>
#include <QDebug>

TodoDetailsDialog::TodoDetailsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TodoDetailsDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setSizeGripEnabled(true);
}

TodoDetailsDialog::~TodoDetailsDialog()
{
    delete ui;
}

void TodoDetailsDialog::setTitle(const QString &title)
{
    if(_title != title )
    {
        _title=title;
    }
    ui->titleLabel_2->setText(QString("Title : %1").arg(_title));
}

void TodoDetailsDialog::setDescription(const QString &description)
{
    if(_description != description )
    {
        _description= description;
    }
    ui->descriptionLabel->setText(QString("Description : %1").arg(_description));

}

void TodoDetailsDialog::setId(const int &id)
{
    if(_id!= id)
    {
        _id=id;
    }
    ui->idLabel->setText(QString("ID : %1").arg(QString::number(id)));
}

void TodoDetailsDialog::setIsCompleted(const bool isCompleted)
{
    if(_isCompleted!=isCompleted)
    {
        _isCompleted=isCompleted;
    }
    if(_isCompleted)
    {
       ui->checkBox->setChecked(true);
    }else ui->checkBox->setChecked(false);

}



void TodoDetailsDialog::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void TodoDetailsDialog::mouseMoveEvent(QMouseEvent *event) {
    try
    {
         move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
         throw 0;
    }
    catch(int &ex)
    {
          qDebug()<<ex;
          return;
    }
}
