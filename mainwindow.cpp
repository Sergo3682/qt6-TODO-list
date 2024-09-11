#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tasksmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new TasksModel)
{
    ui->setupUi(this);
    ui->tasksTableView->setModel(model);
    ui->tasksTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete model;
    delete ui;
}

