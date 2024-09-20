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
    void filterDate(QList<QDateTime> CustomRange);
    void filterDescription(QString searchEntry);
    void clearFilters(int state, bool date, bool desc);
    void setCurrentIndex(QModelIndex here);
    QModelIndex getCurrenSourceIndex();

    void addTask(Task tmpTask);
    void deleteTask();

private:
    QList<QDateTime> CustomRange;
    enum StateToShow {All = 0, Done = 1, InProgress = 2};
    enum NamesToSort {Asc = 0, Desc = 1};
    bool is_filterDate = false;
    bool is_filterDesc = false;
    int is_filterState = All;
    QString searchEntry = "";
    QModelIndex currentIndex;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // TASKSFILTERPROXY_H
