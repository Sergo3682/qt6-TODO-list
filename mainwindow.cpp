#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tasksmodel.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new TasksModel)
    , contextMenu(new QMenu)
{
    ui->setupUi(this);
    initContextMenu();
    initToolBar();
    connect(ui->tasksTableView, &QWidget::customContextMenuRequested,
        this, &MainWindow::openContextMenu);

    model->loadTasksFromFile();

    ui->tasksTableView->setModel(model);
    ui->tasksTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tasksTableView->verticalHeader()->hide();
    ui->tasksTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete model;
    delete addAct;
    delete editAct;
    delete deleteAct;
    delete contextMenu;
    delete ui;
}

void MainWindow::openContextMenu(const QPoint &position)
{
    if (model->rowCount() == 0 || ui->tasksTableView->indexAt(position).row() < 0)
    {
        deleteAct->setEnabled(false);
        editAct->setEnabled(false);
    }
    else if (!deleteAct->isEnabled())
    {
        deleteAct->setEnabled(true);
        editAct->setEnabled(true);
    }
    contextMenu->popup(ui->tasksTableView->mapToGlobal(position));
    model->setCurrentIndex(ui->tasksTableView->indexAt(position));
}

void MainWindow::initContextMenu()
{
    addAct = new QAction("Add new...");
    editAct = new QAction("Edit...");
    deleteAct = new QAction("Delete");

    connect(addAct, &QAction::triggered, this, &MainWindow::on_addActTriggered);
    connect(editAct, &QAction::triggered, this, &MainWindow::on_editActTriggered);
    connect(deleteAct, &QAction::triggered, this, &MainWindow::on_deleteActTriggered);

    contextMenu->addAction(addAct);
    contextMenu->addAction(editAct);
    contextMenu->addAction(deleteAct);
}

void MainWindow::initToolBar()
{
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::on_saveActTriggered);
}

void MainWindow::on_deleteActTriggered()
{
    model->deleteSelectedTask();
}

void MainWindow::on_editActTriggered()
{
    TaskDialog Dlg(model->getSelectedTask());
    if (Dlg.exec())
    {
        model->editTask(Dlg.getTaskFromFields());
    }
}

void MainWindow::on_addActTriggered()
{
    TaskDialog Dlg;
    if (Dlg.exec())
    {
        model->addTask(Dlg.getTaskFromFields());
    }
}

void MainWindow::on_tasksTableView_clicked(const QModelIndex &index)
{
    model->changeState(index);
}

void MainWindow::on_saveActTriggered()
{
    model->saveTasksToFile();
}

