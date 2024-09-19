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
    this->setFilterKeyColumn(TasksModel::State);
    switch (index)
    {
        case All:
        {
            this->setFilterRegularExpression(QRegularExpression("true|false", QRegularExpression::CaseInsensitiveOption));
            break;
        }
        case Done:
        {
            this->setFilterRegularExpression(QRegularExpression("true", QRegularExpression::CaseInsensitiveOption));
            break;
        }
        case InProgress:
        {
            this->setFilterRegularExpression(QRegularExpression("false", QRegularExpression::CaseInsensitiveOption));
            break;
        }
        default:
            break;
    }
    emit layoutChanged();
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

void TasksFilterProxy::filterDate(std::tuple<QDateTime, QDateTime> CustomRange)
{
    is_filterDate = true;
    this->CustomRange = CustomRange;

}
