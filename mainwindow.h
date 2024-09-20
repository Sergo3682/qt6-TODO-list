#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "tasksmodel.h"
#include "taskdialog.h"
#include "datetimedialog.h"
#include "tasksfilterproxy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TasksModel *model;
    TasksFilterProxy *proxy;
    QMenu *contextMenu;
    QAction *addAct, *editAct, *deleteAct;

    void initContextMenu();
    void initToolBar();
    void loadSortFilterBox();

private slots:
    void openContextMenu(const QPoint&);
    void on_dateFilterBoxActivated(int index);
    void on_stateFilterBoxActivated(int index);
    void on_nameSortBoxActivated(int index);
    void on_deleteActTriggered();
    void on_editActTriggered();
    void on_addActTriggered();
    void on_saveActTriggered();

    void on_tasksTableView_clicked(const QModelIndex &index);
    void on_searchButton_clicked();
    void on_clearButton_clicked();
};
#endif // MAINWINDOW_H
