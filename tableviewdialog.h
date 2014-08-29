#ifndef TABLEVIEWDIALOG_H
#define TABLEVIEWDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "todo.h"
#include "db.h"

namespace Ui {
class TableViewDialog;
}

class TableViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableViewDialog(QWidget *parent = 0);
    ~TableViewDialog();

private slots:
    void on_refreshButton_clicked();

private:
    void loaded();
    void populateTable();
    void populateList(Todo &todo);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    Ui::TableViewDialog *ui;
    Db *_db;
};

#endif // TABLEVIEWDIALOG_H
