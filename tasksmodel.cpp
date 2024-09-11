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
    if (role == Qt::DisplayRole)
    {
        return "beer";
    }

    if (role == Qt::TextAlignmentRole && index.column() != COLUMNS_NUMBER - 1) //all columns exept the last one
    {
        return Qt::AlignCenter;
    }
    return QVariant();
}

int TasksModel::rowCount(const QModelIndex &parent ) const
{
    return rows;
}
int TasksModel::columnCount(const QModelIndex &parent) const
{
    return COLUMNS_NUMBER;
}
