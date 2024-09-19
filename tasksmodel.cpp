#include "tasksmodel.h"

TasksModel::TasksModel(QObject* parent): QAbstractTableModel(parent)
{
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
    if (role == Qt::CheckStateRole && index.column() == State)
    {
        return tasks[index.row()].isCompleted;
    }

    if (role == Qt::UserRole)
    {
        switch (index.column())
        {
            case Name:
                return tasks[index.row()].name;
            case State:
                return tasks[index.row()].isCompleted ? "true" : "false";
            case Date:
                return tasks[index.row()].deadline;
            case Description:
                return tasks[index.row()].description;
            default:
                 return "Empty";
        }
    }
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
            case Name:
                return tasks[index.row()].name;
            case Date:
                return tasks[index.row()].deadline.toString(DATE_FORMAT);
            case Description:
                return tasks[index.row()].description;
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

void TasksModel::deleteTask(QModelIndex index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    tasks.removeAt(index.row());
    removeRow(index.row());
    endRemoveRows();
}

void TasksModel::addTask(Task tmpTask)
{
    beginInsertRows(QModelIndex(), tasks.size()-1, tasks.size()-1);
    tasks.append(tmpTask);
    endInsertRows();
}

void TasksModel::editTask(QModelIndex index, Task tmpTask)
{
    tasks[index.row()] = tmpTask;
}

Task TasksModel::getTask(QModelIndex index)
{
    return tasks[index.row()];
}

void TasksModel::changeState(QModelIndex index)
{
    if (index.column() == State)
    {
        tasks[index.row()].isCompleted = !tasks[index.row()].isCompleted;
    }
}

void TasksModel::saveTasksToFile()
{
    SaveLoadManager Manager;
    Manager.SaveToFile("./MyTasks.xml", tasks);
}

void TasksModel::loadTasksFromFile()
{
    SaveLoadManager Manager;
    Manager.LoadFromFile("./MyTasks.xml", tasks);
}
