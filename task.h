#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDateTime>

class Task
{
public:
    QString name;
    QString description;
    QDateTime deadline;
    bool isCompleted = false;
};

#endif // TASK_H
