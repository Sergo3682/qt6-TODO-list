#ifndef TASKSFILTERPROXY_H
#define TASKSFILTERPROXY_H

#include <QSortFilterProxyModel>
#include "tasksmodel.h"

#include <QAbstractTableModel>

class TasksFilterProxy : public QSortFilterProxyModel
{
public:
    TasksFilterProxy();
    TasksFilterProxy(TasksModel *model);
    void filterState(int &index);
    void sortName(int &index);
    void filterDate(std::tuple<QDateTime, QDateTime> CustomRange);
    void setCurrentIndex(QModelIndex here);
    QModelIndex getCurrenSourceIndex();

    void addTask(Task tmpTask);
    void deleteTask();

private:
    std::tuple<QDateTime, QDateTime> CustomRange;
    enum StateToShow {All = 0, Done = 1, InProgress = 2};
    enum NamesToSort {Asc = 0, Desc = 1};
    bool is_filterDate = false;
    QModelIndex currentIndex;
};

#endif // TASKSFILTERPROXY_H
