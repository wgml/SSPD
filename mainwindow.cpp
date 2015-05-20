#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dummy.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Dummy master;
}

MainWindow::~MainWindow()
{
    delete ui;
}
