#include "createtodo.h"
#include "ui_createtodo.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QMainWindow>

CreateTodo::CreateTodo(QWidget *parent) : QDialog(parent),
    ui(new Ui::CreateTodo)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setSizeGripEnabled(true);

    ui->setupUi(this);

    _db= new Db();

    if(!_db->Open()){
         QMessageBox::critical(this,"Error","Database didn't open' :(");
         this->close();
    }
    if(!_db->Open()){
         QMessageBox::critical(this,"Error","Database didn't open' :(");
         this->close();
    }


}



CreateTodo::~CreateTodo()
{
    delete ui;
    delete _db;
}


void CreateTodo::on_createButton_clicked()
{
   if(checkRequiredFields())
   {
      Todo * newTodo =new Todo();
      newTodo->setTitle(ui->titleText->toPlainText());
      newTodo->setDescription(ui->descriptionText->toPlainText());
      if(ui->isCompletedCheckBox->isChecked())
      {
          newTodo->setCompleted(true);
      }
      else newTodo->setCompleted(false);
      if(_db->Insert(*newTodo))
      {
          QMessageBox::information(this,"Success","The new task is created.");
      }
      else QMessageBox::critical(this,"Error","Insert failed :(");

      delete newTodo;

      this->close();


   }
}

bool CreateTodo::checkRequiredFields()
{
    if(ui->titleText->toPlainText()=="" || ui->descriptionText->toPlainText()=="")
    {
        QMessageBox::critical(this, "Error", "Please enter the title and the description");
        return false;
    }
    else if(ui->titleText->toPlainText().count()>50)
    {
         QMessageBox::critical(this, "Error", "The title must be be under 50 characters.");
         return false;
    }
    return true;
}


void CreateTodo::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void CreateTodo::mouseMoveEvent(QMouseEvent *event) {
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
