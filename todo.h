#ifndef TODO_H
#define TODO_H

#include <QString>

class Todo
{
public:
    Todo();
    Todo( int id, QString &title, QString &description,  bool isCompleted );
    ~Todo();

   const int id()const;
   const QString title() const;
   const QString description() const;
   const bool isCompleted() const;

   void setId(const int &id);
   void setTitle(QString &newTitle);
   void setDescription(QString &newDescription);
   void setCompleted(bool newIsCompleted);

private:
    int _id;
    QString  _title;
    QString  _description;
    bool _isCompleted;
};


#endif // TODO_H
