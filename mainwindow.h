#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "db.h"
#include "todo.h"
#include "createtodo.h"
#include "tododetailsdialog.h"
#include "tableviewdialog.h"
#include "todoeditdialog.h"

#include <QList>
#include <QListWidgetItem>

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

    void on_detailsButton_clicked();

    void on_todosList_itemDoubleClicked(QListWidgetItem *item);

    void on_actionClear_Database_triggered();

    void on_todosList_itemSelectionChanged();

    void on_actionTable_View_triggered();

    void on_deleteButton_clicked();

    void on_editButton_clicked();

private:
    void loaded();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    Ui::MainWindow *ui;
    Db *_db;
    Todo * _todo;
    CreateTodo * _createTodoDialog;
    TodoEditDialog * _todoEditDialog;
    TodoDetailsDialog * _todoDetailsDialog;
    TableViewDialog * _tableViewDialog;
};

#endif // MAINWINDOW_H
