#ifndef TODODETAILSDIALOG_H
#define TODODETAILSDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QString>

namespace Ui {
class TodoDetailsDialog;
}

class TodoDetailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TodoDetailsDialog(QWidget *parent = 0);
    ~TodoDetailsDialog();
    void setTitle(const QString &title);
    void setDescription(const QString &description);
    void setId(const int &id);
    void setIsCompleted(const bool isCompleted);

private:
    int _id;
    QString _title;
    QString _description;
    bool _isCompleted;
    Ui::TodoDetailsDialog *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
};

#endif // TODODETAILSDIALOG_H
