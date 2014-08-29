#include "todo.h"

Todo::Todo()
{
    _isCompleted=false;
}

Todo::Todo(int id, QString &title, QString &description, bool isCompleted)
{
    _id=id;
    _title=title;
    _description=description;
    _isCompleted=isCompleted;
}

const int Todo::id() const
{
    return _id;
}

const QString Todo::title() const
{
    return _title;
}
const QString Todo::description() const
{
    return _description;
}

const bool Todo::isCompleted()const
{
    return _isCompleted;
}

void Todo::setId(const int &id)
{
    if(_id!= id )
    {
        _id=id;
    }
}

void Todo::setTitle(QString &newTitle)
{
    if(_title != newTitle )
    {
        _title=newTitle;
    }
}
void Todo::setDescription(QString &newDescription)
{
    if(_description != newDescription )
    {
        _description=newDescription;
    }
}

void Todo::setCompleted(bool newIsCompleted)
{
    if(_isCompleted!=newIsCompleted)
    {
        _isCompleted=newIsCompleted;
    }
}


Todo::~Todo()
{

}







