#ifndef SAVELOADMANAGER_H
#define SAVELOADMANAGER_H

#define DATE_FORMAT "dd.MM.yyyy hh:mm"

#include "task.h"
#include <QFile>
#include <QTextStream>
#include <QtXml/QDomDocument>

class SaveLoadManager
{
public:
    SaveLoadManager();
    void SaveToFile(QString filepath, QList<Task>& tasks);
    void LoadFromFile(QList<Task>& tasks);
    void CreateXMLfromTask(QDomElement& child, Task task);
    Task CreateTaskFromXML();

private:
    QString xmlbuffer;
};

#endif // SAVELOADMANAGER_H
