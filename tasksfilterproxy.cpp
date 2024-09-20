#include "tasksfilterproxy.h"

TasksFilterProxy::TasksFilterProxy()
{
}

TasksFilterProxy::TasksFilterProxy(TasksModel *model)
{
    this->setFilterRole(Qt::UserRole);
    this->setSortRole(Qt::UserRole);
    this->setSourceModel(model);
}

void TasksFilterProxy::filterState(int &index)
{
    is_filterState = index;
    invalidateFilter();
}

void TasksFilterProxy::filterDescription(QString searchEntry)
{
    is_filterDesc = true;
    this->searchEntry = searchEntry;
    invalidateFilter();
}

void TasksFilterProxy::sortName(int &index)
{
    switch (index)
    {
        case Asc:
        {
            sort(TasksModel::Name, Qt::AscendingOrder);
            break;
        }
        case Desc:
        {
            sort(TasksModel::Name, Qt::DescendingOrder);
            break;
        }
        default:
            break;
    }
}


void TasksFilterProxy::setCurrentIndex(QModelIndex here)
{
    currentIndex = here;
}

QModelIndex TasksFilterProxy::getCurrenSourceIndex()
{
    return mapToSource(currentIndex);
}

void TasksFilterProxy::filterDate(QList<QDateTime> CustomRange)
{
    is_filterDate = true;
    this->CustomRange = CustomRange;
    this->invalidateFilter();
}

void TasksFilterProxy::clearFilters(int state, bool date, bool desc)
{
    is_filterState = state;
    is_filterDate = date;
    is_filterDesc = desc;
    invalidateFilter();
}

bool TasksFilterProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    bool result = true;
    if(is_filterState)
    {
        QModelIndex index = sourceModel()->index(sourceRow, TasksModel::State, sourceParent);
        if (is_filterState == Done)
        {
            result = index.data(Qt::UserRole).value<bool>();
        }
        else
        {
            result = !(index.data(Qt::UserRole).value<bool>());
        }
        if (!result)
            return result;
    }
    if (is_filterDate)
    {
        QModelIndex index = sourceModel()->index(sourceRow, TasksModel::Date, sourceParent);
        result = index.data(Qt::UserRole).value<QDateTime>() >= CustomRange[0] && index.data(Qt::UserRole).value<QDateTime>() <= CustomRange[1];
        if (!result)
            return result;
    }
    if (is_filterDesc)
    {
        QModelIndex index = sourceModel()->index(sourceRow, TasksModel::Description, sourceParent);
        QString description = index.data(Qt::UserRole).value<QString>();
        result = description.contains(searchEntry);
        if (!result)
            return result;
    }
    return result;
}
