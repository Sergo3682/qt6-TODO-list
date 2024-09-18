#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "tasksmodel.h"
#include "taskdialog.h"
#include "datetimedialog.h"

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
    QMenu *contextMenu;
    QAction *addAct, *editAct, *deleteAct;

    void initContextMenu();
    void initToolBar();
    void loadFilterBox();

private slots:
    void openContextMenu(const QPoint&);
    void on_dateFilterBoxActivated(int index);
    void on_stateFilterBoxActivated(int index);
    void on_nameFilterBoxActivated(int index);
    void on_deleteActTriggered();
    void on_editActTriggered();
    void on_addActTriggered();
    void on_saveActTriggered();

    void on_tasksTableView_clicked(const QModelIndex &index);
};
#endif // MAINWINDOW_H
