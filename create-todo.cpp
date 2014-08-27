#include "create-todo.h"
#include "ui_create-todo.h"

CreateTodo::CreateTodo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTodo)
{
    ui->setupUi(this);
}

CreateTodo::~CreateTodo()
{
    delete ui;
}
