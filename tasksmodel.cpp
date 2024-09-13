#include "tasksmodel.h"

TasksModel::TasksModel(QObject* parent): QAbstractTableModel(parent)
{
    Task task1;
    task1.name = QString("Add name");
    task1.description = QString("Add desc");
    task1.deadline = QDateTime(QDate(2024, 9, 13), QTime(12, 45, 0));
    tasks.append(task1);
}

QVariant TasksModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return columnHeaders[section];
    }
    return QVariant();
}

QVariant TasksModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
            case Name:
                return tasks[index.row()].name;
            case State:
                return tasks[index.row()].isCompleted;
            case Date:
                return tasks[index.row()].deadline;
            case Description:
                return tasks[index.row()].description;
            default:
                return "beer";
        }
    }

    if (role == Qt::TextAlignmentRole && index.column() != COLUMNS_NUMBER - 1) //all columns exept the last one
    {
        return Qt::AlignCenter;
    }
    return QVariant();
}

int TasksModel::rowCount(const QModelIndex &parent ) const
{
    return tasks.size();
}
int TasksModel::columnCount(const QModelIndex &parent) const
{
    return COLUMNS_NUMBER;
}
