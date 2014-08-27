#include "createtodo.h"
#include "ui_createtodo.h"
#include <QString>
#include <QMessageBox>

CreateTodo::CreateTodo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTodo)
{
    ui->setupUi(this);
    _db= new Db();

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
      newTodo->setDescription(ui->titleText->toPlainText());
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
    return true;
}
