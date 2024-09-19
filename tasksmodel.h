#ifndef TASKSMODEL_H
#define TASKSMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "task.h"
#include "saveloadmanager.h"

#define COLUMNS_NUMBER 4

class TasksModel : public QAbstractTableModel
{
public:
    enum colNames {State, Name, Date, Description};

    TasksModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void deleteTask(QModelIndex index);
    void addTask(Task tmpTask);
    void editTask(QModelIndex index, Task tmpTask);
    Task getTask(QModelIndex index);
    void changeState(QModelIndex index);
    void saveTasksToFile();
    void loadTasksFromFile();


private:
    const QList<QString> columnHeaders = { "State", "Name", "Date", "Description" };
    QList<Task> tasks;
};



#endif // TASKSMODEL_H
