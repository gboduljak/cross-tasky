#ifndef CREATETODO_H
#define CREATETODO_H

#include <QDialog>
#include "db.h"

namespace Ui {
class CreateTodo;
}

class CreateTodo : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTodo(QWidget *parent = 0);
    ~CreateTodo();

private slots:
    void on_createButton_clicked();

private:
    Ui::CreateTodo *ui;
    Db * _db;
    bool checkRequiredFields();
};

#endif // CREATETODO_H
