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

    Task& operator=(const Task& other)
    {
        this->name = other.name;
        this->description = other.description;
        this->deadline = other.deadline;
        this->isCompleted = other.isCompleted;
        return *this;
    }

};

#endif // TASK_H
