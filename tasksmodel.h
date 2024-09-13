#ifndef TASKSMODEL_H
#define TASKSMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "task.h"
#define COLUMNS_NUMBER 4

class TasksModel : public QAbstractTableModel
{
public:
    TasksModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    const QList<QString> columnHeaders = { "State", "Name", "Date", "Description" };
    QList<Task> tasks;
};

enum colNames {State, Name, Date, Description};

#endif // TASKSMODEL_H
