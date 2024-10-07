#include "hello_qt.h"

hello_qt::hello_qt(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_hello_qt)
{
    ui->setupUi(this);
}

hello_qt::~hello_qt()
{
    delete ui; 
}