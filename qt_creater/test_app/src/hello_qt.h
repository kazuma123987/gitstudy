#pragma once
#include "ui_hello_qt.h"
#include <QMainWindow>

class hello_qt : public QMainWindow {
    Q_OBJECT
    
public:
    hello_qt(QWidget* parent = nullptr);
    ~hello_qt();

private:
    Ui_hello_qt* ui;
};