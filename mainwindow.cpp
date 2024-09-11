#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tasksmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new TasksModel;
    ui->tasksTableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete model;
    delete ui;
}

