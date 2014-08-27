#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "db.h"
#include "todo.h"
#include "createtodo.h"

#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_refreshButton_clicked();

    void on_createButton_clicked();

private:
    void loaded();
    Ui::MainWindow *ui;
    Db *_db;
    QList<Todo> * _todos;
    CreateTodo * _createTodoDialog;
};

#endif // MAINWINDOW_H
