#include "db.h"
#include "todo.h"

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include "todo.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QString>
#include "task.h"
#include <QDebug>
#include <QSqlError>

Db::Db()
{
    _todos=new QList<Todo>();
    _db=QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName("todosDb.db");
}

Db::~Db()
{
    delete _todos;
}

bool Db::executeQuery(const QString &cmd ) const
{
  QSqlQuery qry;
  if(qry.exec(cmd))
  {
      return true;
  }
  return false;
}

bool Db::Open()
{
    bool result =_db.open();
    QSqlQuery qry;
      if(qry.exec("CREATE TABLE IF NOT EXISTS Todos (Id INTEGER PRIMARY KEY AUTOINCREMENT, Title CHAR(100), Description TEXT, IsCompleted INT);"))
      {
          qDebug()<<qry.lastQuery();

      }
      else
      {
          qCritical()<<qry.lastError();
      }

    /*if(qry.exec("INSERT INTO Todos VALUES(NULL,'works','thanks god',5);"))
    {
        qDebug()<<qry.lastQuery();

    }
    else
    {
        qCritical()<<qry.lastError();
    }*/
    return result;
}

QList<Todo*> Db::Get()
{
   auto task = [](){
       QList<Todo*> list;
       QSqlQuery qry;
       if(qry.exec("SELECT * FROM Todos"))
       {
         while(qry.next())
         {
             Todo * todo = new Todo();
             todo->setId(qry.value(0).toInt());
             todo->setTitle(qry.value(1).toString());
             todo->setDescription(qry.value(2).toString());
             if(qry.value(3).toInt()==0)
             {
                todo->setCompleted(false);
             }
             else
             {
                todo->setCompleted(true);
             }

               list.push_back(todo);
         }
       }
       return list;
   };
  return Task::run<QList<Todo*>>(task).await();
}

bool Db::Insert(const Todo &todo) const
{
    auto task=[&](){
        QSqlQuery qry;
        QString qryStr;

        if(todo.isCompleted()){
            qryStr = QString(("INSERT INTO Todos(Id,Title,Description,IsCompleted) VALUES (NULL,'%1','%2'',0);")).arg(todo.title(),todo.description());
        }
        else
        {
            qryStr = QString(("INSERT INTO Todos(Id,Title,Description,IsCompleted) VALUES (NULL,'%1','%2',1);")).arg(todo.title(),todo.description());
        }
        if(qry.exec(qryStr))
        {
            return true;
        }
        qDebug()<<qry.lastQuery();
        return false;
    };

    return Task::run<bool>(task).await();

}






