#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QList>
#include <QMessageBox>
#include <QSize>
#include <QAction>
#include <QDebug>
#include "db.h"
#include "todo.h"
#include "createtodo.h"
#include <QMouseEvent>
#include "tododetailsdialog.h"
#include "tableviewdialog.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint); //Set window with no title bar
    this->setWindowFlags(Qt::FramelessWindowHint); //Set a frameless window

    _db=new Db();
    _todo=new Todo();

    this->setWindowTitle("CrossTasky - Tasks");

    loaded();


}


void MainWindow::loaded()
{
    if(_db->Open())
    {
      ui->dbLabel->setText("Database opened");
      on_refreshButton_clicked();
    }
    else
    {
       ui->dbLabel->setText("Database failed to open. :(");
    }


}



MainWindow::~MainWindow()
{
    delete ui;
    delete _db;
    delete _todo;
    delete _createTodoDialog;
}

void MainWindow::on_refreshButton_clicked()
{
    ui->todosList->clear();
    QList<Todo*> todos = _db->Get();

    for(int i=0;i<todos.count();++i)
    {
       QListWidgetItem * item = new QListWidgetItem;
       QString temp=QString(("%1")).arg(todos[i]->title());
       item->setText(temp);
       item->setIcon(QIcon(":/icon-list.png"));
       QSize size;
       size.setHeight(45);
       item->setSizeHint(size);
       ui->todosList->addItem(item);
    }
    todos.clear();
}

void MainWindow::on_createButton_clicked()
{
    _createTodoDialog=new CreateTodo(this);
    _createTodoDialog->show();

}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
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


void MainWindow::on_detailsButton_clicked()
{
    if(ui->todosList->currentItem())
    {
        _todoDetailsDialog= new TodoDetailsDialog(this);
        _todoDetailsDialog->setId(_todo->id());
        _todoDetailsDialog->setTitle(_todo->title());
        _todoDetailsDialog->setDescription(_todo->description());
        _todoDetailsDialog->setIsCompleted(_todo->isCompleted());
        _todoDetailsDialog->show();
    }

}

void MainWindow::on_todosList_itemDoubleClicked(QListWidgetItem *item)
{
    _todo = _db->Get(item->text());
    emit ui->detailsButton->clicked();
}

void MainWindow::on_actionClear_Database_triggered()
{
   if(_db->ClearDatabase())
   {
      ui->todosList->clear();
      QMessageBox::information(this,"Success","Database cleared.");
   }
}

void MainWindow::on_todosList_itemSelectionChanged()
{
    _todo = _db->Get(ui->todosList->currentItem()->text());
}

void MainWindow::on_actionTable_View_triggered()
{
    _tableViewDialog=new TableViewDialog(this);
    _tableViewDialog->show();
}

void MainWindow::on_deleteButton_clicked()
{
    if(ui->todosList->currentItem())
    {
        if(_db->Delete(_todo->title()))
        {
            emit ui->refreshButton->clicked();
            QMessageBox::information(this,"Success","The task was deleted.");
        }
    }
}

void MainWindow::on_editButton_clicked()
{
    if(ui->todosList->currentItem())
    {
        _todoEditDialog= new TodoEditDialog(this);
        _todoEditDialog->setId(_todo->id());
        _todoEditDialog->setTitle(_todo->title());
        _todoEditDialog->setDescription(_todo->description());
        _todoEditDialog->setIsCompleted(_todo->isCompleted());
        _todoEditDialog->show();
    }


}
