#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tasksmodel.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new TasksModel)
    , proxy(new TasksFilterProxy(model))
    , contextMenu(new QMenu)
{
    ui->setupUi(this);
    initContextMenu();
    initToolBar();
    loadSortFilterBox();
    connect(ui->tasksTableView, &QWidget::customContextMenuRequested,
        this, &MainWindow::openContextMenu);
    model->loadTasksFromFile();
    ui->tasksTableView->setModel(proxy);
    ui->tasksTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tasksTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tasksTableView->verticalHeader()->hide();
    ui->tasksTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tasksTableView->horizontalHeader()->setSectionResizeMode(TasksModel::State, QHeaderView::ResizeToContents);
    emit ui->nameSortBox->activated(0);
}

MainWindow::~MainWindow()
{
    delete proxy;
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
        ui->tasksTableView->clearSelection();
        deleteAct->setEnabled(false);
        editAct->setEnabled(false);
    }
    else if (!deleteAct->isEnabled())
    {
        deleteAct->setEnabled(true);
        editAct->setEnabled(true);
    }
    contextMenu->popup(ui->tasksTableView->mapToGlobal(position));
    proxy->setCurrentIndex(ui->tasksTableView->indexAt(position));
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
    model->deleteTask(proxy->getCurrenSourceIndex());
    emit proxy->layoutChanged();
}

void MainWindow::loadSortFilterBox()
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

    ui->nameSortBox->addItem("A-z");
    ui->nameSortBox->addItem("Z-a");
    ui->nameSortBox->setCurrentIndex(ui->nameSortBox->findText("A-z"));
    connect(ui->nameSortBox, qOverload<int>(&QComboBox::activated), this, &MainWindow::on_nameSortBoxActivated);
}

void MainWindow::on_editActTriggered()
{
    TaskDialog Dlg(model->getTask(proxy->getCurrenSourceIndex()));
    if (Dlg.exec())
    {
        model->editTask(proxy->getCurrenSourceIndex(), Dlg.getTaskFromFields());
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
    proxy->setCurrentIndex(index);
    model->changeState(proxy->getCurrenSourceIndex());
    emit proxy->layoutChanged();
    emit ui->stateFilterBox->setCurrentIndex(ui->stateFilterBox->currentIndex());
}

void MainWindow::on_saveActTriggered()
{
    model->saveTasksToFile();
}

void MainWindow::on_dateFilterBoxActivated(int index)
{
    if (index == 0)
    {
        proxy->clearFilters(ui->stateFilterBox->currentIndex(),0,ui->searchBar->text().size());
    }
    else if (index == 1)
    {
        DateTimeDialog Dlg;
        if (Dlg.exec())
        {
            proxy->filterDate(Dlg.getCustomRange());
        }
        else
        {
            ui->dateFilterBox->setCurrentIndex(0);
        }
    }
}

void MainWindow::on_stateFilterBoxActivated(int index)
{
    proxy->filterState(index);
}

void MainWindow::on_nameSortBoxActivated(int index)
{
    proxy->sortName(index);
}

void MainWindow::on_searchButton_clicked()
{
    proxy->filterDescription(ui->searchBar->text());
}

void MainWindow::on_clearButton_clicked()
{
    proxy->clearFilters(0,0,0);
    ui->stateFilterBox->setCurrentIndex(0);
    ui->dateFilterBox->setCurrentIndex(0);
    ui->nameSortBox->setCurrentIndex(0);
    ui->searchBar->clear();
}

