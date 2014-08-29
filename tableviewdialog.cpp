#include "tableviewdialog.h"
#include "ui_tableviewdialog.h"
#include <QMouseEvent>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QList>

#include "todo.h"

TableViewDialog::TableViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableViewDialog)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setSizeGripEnabled(true);
    ui->setupUi(this);
    _db=new Db();
    if(!_db->Open()){
         QMessageBox::critical(this,"Error","Database didn't open' :(");
         this->close();
    }
    loaded();
}

void TableViewDialog::loaded()
{
   QList<Todo*> list = _db->Get();
   populateTable();
   for(int i=0; i< list.count(); ++i)
   {
      populateList(*list[i]);
   }

}

void TableViewDialog::populateTable()
{
    ui->tableView->setModel(_db->GetTable());
}

void TableViewDialog::populateList(Todo &todo)
{
    ui->listWidget->clear();
    QListWidgetItem * item = new QListWidgetItem;
    QString temp=QString(("%1")).arg(todo.title());
    item->setText(temp);
    item->setIcon(QIcon(":/icon-list.png"));
    QSize size;
    size.setHeight(45);
    item->setSizeHint(size);
    ui->listWidget->addItem(item);
}

void TableViewDialog::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void TableViewDialog::mouseMoveEvent(QMouseEvent *event) {
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




TableViewDialog::~TableViewDialog()
{
    delete ui;
    delete _db;
}



void TableViewDialog::on_refreshButton_clicked()
{
    populateTable();
    loaded();
}
