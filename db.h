#ifndef DB_H
#define DB_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QList>
#include "todo.h"
#include "task.h"

class Db
{
public:
    Db();
    ~Db();
    QList<Todo*> Get();
    Todo * Get(const QString &title) const;
    QSqlQueryModel * GetTable() const;
    bool executeQuery(const QString &cmd) const;
    bool Open();
    bool Insert(const Todo &todo);
    bool Update(int id,QString &newTitle, QString &newDescription, bool newIsCompleted);
    bool Delete(const QString &title) const;
    bool ClearDatabase() const;
    int lastInsertId();

private:
    int _lastInsertId;
    QSqlDatabase  _db;
    QList<Todo> * _todos;
};

#endif // DB_H
