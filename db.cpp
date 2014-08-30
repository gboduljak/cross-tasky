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
    _db.setDatabaseName("./todosDb.db");
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
      qDebug()<<qry.lastQuery();
      return true;
  }
  qCritical()<<qry.lastError();
  return false;
}

bool Db::Open()
{
   auto task=[&](){
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
       return result;
   };

   return Task::run<bool>(task).await();
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

Todo* Db::Get(const QString &title) const
{
    auto task=[&](){
        Todo * todo = new Todo();
        QSqlQuery qry;
        QString qryStr=QString("SELECT * FROM Todos WHERE Title='%1'").arg(title);
        if(qry.exec(qryStr))
        {
           while(qry.next())
           {
               todo->setId(qry.value(0).toInt());
               todo->setTitle(qry.value(1).toString());
               todo->setDescription(qry.value(2).toString());
               if(qry.value(3).toInt()==0)
               {
                   todo->setCompleted(false);
               }
               else todo->setCompleted(true);
           }

        }
        return todo;
    };

    return Task::run<Todo*>(task).await();

}

QSqlQueryModel *Db::GetTable() const
{
    auto task=[&](){
        QSqlQuery qry;
        QSqlQueryModel * model= new QSqlQueryModel;
        if(qry.exec("SELECT * FROM Todos"))
        {
            model->setQuery(qry);
        }
        return model;
    };

    return Task::run<QSqlQueryModel *>(task).await();
}

bool Db::Insert(const Todo &todo)
{
    auto task=[&](){
        QSqlQuery qry;
        QString qryStr;

        if(todo.isCompleted()){
            qryStr = QString(("INSERT INTO Todos(Id,Title,Description,IsCompleted) VALUES (NULL,'%1','%2',1);")).arg(todo.title(),todo.description());
        }
        else
        {
            qryStr = QString(("INSERT INTO Todos(Id,Title,Description,IsCompleted) VALUES (NULL,'%1','%2',0);")).arg(todo.title(),todo.description());
        }
        if(qry.exec(qryStr))
        {
            _lastInsertId=qry.lastInsertId().toInt();
            return true;
        }

        qDebug()<<qry.lastQuery();
        return false;
    };

    return Task::run<bool>(task).await();

}

bool Db::Update(int id, QString &newTitle, QString &newDescription, bool newIsCompleted)
{
    auto task =[&](){
        QString qryStr;
        if(newIsCompleted)
        {
            qryStr=QString("UPDATE Todos SET Title='%1', Description='%2', IsCompleted=1 WHERE Id=%3;").arg(newTitle,newDescription,QString::number(id));
        }
        else
        {
             qryStr=QString("UPDATE Todos SET Title='%1', Description='%2', IsCompleted=0 WHERE Id=%3;").arg(newTitle,newDescription,QString::number(id));
        }
        //
        if(this->executeQuery(qryStr))
        {
             return true;
        }
        return false;
    };

    return Task::run<bool>(task).await();
}

bool Db::Delete(const QString &title) const
{
    auto task =[&](){
        QString qryStr=QString("DELETE FROM Todos WHERE Title = '%1'").arg(title);
        return this->executeQuery(qryStr);
    };

    return Task::run<bool>(task).await();

}

bool Db::ClearDatabase() const
{
    auto task =[&](){
        return this->executeQuery("DELETE FROM Todos");
    };
    return Task::run<bool>(task).await();
}

int Db::lastInsertId()
{
    return _lastInsertId;
}






