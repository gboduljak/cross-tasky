#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QList>
#include <QMessageBox>
#include <QSize>
#include <QAction>
#include "db.h"
#include "todo.h"
#include "createtodo.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    _db=new Db();

    _todos=new QList<Todo>();

    ui->setupUi(this);

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
    delete _todos;
    delete _createTodoDialog;
}

void MainWindow::on_refreshButton_clicked()
{
    ui->todosList->clear();
    QList<Todo*> todos = _db->Get();

    for(int i=0;i<todos.count()-1;++i)
    {
       QListWidgetItem * item = new QListWidgetItem;
       QString temp=QString(("%1 - %2")).arg(QString::number(todos[i]->id()),todos[i]->title());
       item->setText(temp);
       item->setIcon(QIcon(":/icon-ok.jpg"));
       QSize size;
       size.setHeight(40);
       item->setSizeHint(size);
       ui->todosList->addItem(item);
    }
}

void MainWindow::on_createButton_clicked()
{
    _createTodoDialog=new CreateTodo(this);
    _createTodoDialog->show();

}
