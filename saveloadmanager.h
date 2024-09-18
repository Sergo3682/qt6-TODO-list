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
    void LoadFromFile(QString filepath, QList<Task>& tasks); 

private:
    Task CreateTaskFromXML(QDomElement& child);
    void CreateXMLfromTask(QDomElement& child, Task task);
};

#endif // SAVELOADMANAGER_H
