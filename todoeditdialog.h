#ifndef TODOEDITDIALOG_H
#define TODOEDITDIALOG_H

#include <QDialog>

#include "todo.h"
#include "db.h"
#include <QMouseEvent>
#include <QString>

namespace Ui {
class TodoEditDialog;
}

class TodoEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TodoEditDialog(QWidget *parent = 0);
    void setTitle(const QString &title);
    void setDescription(const QString &description);
    void setId(const int &id);
    void setIsCompleted(const bool isCompleted);

    ~TodoEditDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::TodoEditDialog *ui;
    int _id;
    QString _title;
    QString _description;
    bool _isCompleted;

    Db * _db;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    bool checkRequiredFields();
};

#endif // TODOEDITDIALOG_H
