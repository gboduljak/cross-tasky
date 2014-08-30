#include "todoeditdialog.h"
#include "ui_todoeditdialog.h"
#include "db.h"

#include <QMouseEvent>
#include <QString>
#include <QMessageBox>
#include <QDebug>

TodoEditDialog::TodoEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TodoEditDialog)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setSizeGripEnabled(true);
    ui->setupUi(this);
    _db= new Db();

    if(!_db->Open()){
         QMessageBox::critical(this,"Error","Database didn't open' :(");
         this->close();
    }
}

void TodoEditDialog::on_saveButton_clicked()
{
    if(checkRequiredFields())
    {
        if(_db->Update(_id,ui->titleText->toPlainText(),ui->descripitonText->toPlainText(),ui->checkBox->isChecked()))
        {
             QMessageBox::information(this,"Success","The todo has been saved.");
        }
        else
        {
             QMessageBox::critical(this,"Error","The todo hasn't been saved :(");
        }
        this->close();
    }
}


bool TodoEditDialog::checkRequiredFields()
{
    if(ui->titleText->toPlainText()=="" || ui->descripitonText->toPlainText()=="")
    {
        QMessageBox::critical(this, "Error", "Please enter the title and the description.");
        return false;
    }
    else if(ui->titleText->toPlainText().count()>50)
    {
         QMessageBox::critical(this, "Error", "The title must be be under 50 characters.");
         return false;
    }
    return true;
}

void TodoEditDialog::setTitle(const QString &title)
{
    if(_title != title )
    {
        _title=title;
    }
    ui->titleText->setPlainText(_title);
}

void TodoEditDialog::setDescription(const QString &description)
{
    if(_description != description )
    {
        _description= description;
    }
    ui->descripitonText->setPlainText(_description);

}

void TodoEditDialog::setId(const int &id)
{
    if(_id!= id)
    {
        _id=id;
    }
    ui->idTextEdit->setPlainText(QString::number(id));
}

void TodoEditDialog::setIsCompleted(const bool isCompleted)
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

void TodoEditDialog::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void TodoEditDialog::mouseMoveEvent(QMouseEvent *event) {

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


TodoEditDialog::~TodoEditDialog()
{
    delete ui;
    delete _db;
}


