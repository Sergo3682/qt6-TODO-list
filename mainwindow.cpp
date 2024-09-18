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
    loadFilterBox();
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

void MainWindow::loadFilterBox()
{
    ui->stateFilterBox->addItem("State");
    ui->stateFilterBox->addItem("Done");
    ui->stateFilterBox->addItem("In progress");
    ui->stateFilterBox->setCurrentIndex(ui->stateFilterBox->findText("State"));
    connect(ui->stateFilterBox, qOverload<int>(&QComboBox::activated), this, &MainWindow::on_stateFilterBoxActivated);

    ui->dateFilterBox->addItem("Date");
    ui->dateFilterBox->addItem("Custom range...");
    ui->dateFilterBox->setCurrentIndex(ui->dateFilterBox->findText("Date"));
    connect(ui->dateFilterBox, qOverload<int>(&QComboBox::activated), this, &MainWindow::on_dateFilterBoxActivated);

    ui->nameFilterBox->addItem("Name");
    ui->nameFilterBox->addItem("A-z");
    ui->nameFilterBox->addItem("Z-a");
    ui->nameFilterBox->setCurrentIndex(ui->nameFilterBox->findText("Name"));
    connect(ui->nameFilterBox, qOverload<int>(&QComboBox::activated), this, &MainWindow::on_nameFilterBoxActivated);
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

void MainWindow::on_dateFilterBoxActivated(int index)
{
    if (index == 0)
    {
        //clear filter
    }

    else if (index == 1)
    {
        DateTimeDialog Dlg;
        if (Dlg.exec())
        {
            //filter
        }
        else
        {
            ui->dateFilterBox->setCurrentIndex(0);
            //clear filter
        }
    }
}

void MainWindow::on_stateFilterBoxActivated(int index)
{
    switch (index)
    {
        case 0:
        {
            //reset filter
            break;
        }
        case 1:
        {
            //set done filter
            break;
        }
        case 2:
        {
            //set in progress filter
            break;
        }
        default:
            break;
    }
}

void MainWindow::on_nameFilterBoxActivated(int index)
{
    switch (index)
    {
        case 0:
        {
            //reset filter
            break;
        }
        case 1:
        {
            //set A-z filter
            break;
        }
        case 2:
        {
            //set Z-a filter
            break;
        }
        default:
            break;
    }
}

