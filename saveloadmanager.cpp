#include "saveloadmanager.h"

SaveLoadManager::SaveLoadManager()
{

}

void SaveLoadManager::SaveToFile(QString filepath, QList<Task>& tasks)
{
    QFile fd(filepath);
    fd.open(QFile::WriteOnly);

    QTextStream xmlContent(&fd);
    QDomDocument document;

    QDomElement root = document.createElement("tasks");
    document.appendChild(root);
    QDomElement child;

    foreach (Task task, tasks) {
        child = document.createElement("task");
        CreateXMLfromTask(child, task);
        root.appendChild(child);
    }
    xmlContent << document.toString();
    fd.close();
}

void SaveLoadManager::LoadFromFile(QString filepath, QList<Task> &tasks)
{
    QFile fd(filepath);

    if (!QFile::exists(filepath))
    {
        fd.open(QFile::WriteOnly);
        fd.close();
        return;
    }

    fd.open(QFile::ReadOnly);

    QDomDocument document;
    document.setContent(&fd);
    QDomElement root = document.firstChildElement();
    QDomNodeList nodelist = root.childNodes();

    for (int i = 0; i < nodelist.length(); i++)
    {
        QDomElement nextelem = nodelist.at(i).toElement();
        tasks.append(CreateTaskFromXML(nextelem));
    }
    fd.close();
}

void SaveLoadManager::CreateXMLfromTask(QDomElement& child, Task task)
{
    child.setAttribute("name", task.name);
    child.setAttribute("state", task.isCompleted);
    child.setAttribute("deadline", task.deadline.toString(DATE_FORMAT));
    child.setAttribute("description", task.description);
}

Task SaveLoadManager::CreateTaskFromXML(QDomElement& child)
{
    Task tmpTask;
    tmpTask.name = child.attribute("name");
    tmpTask.deadline = QDateTime::fromString(child.attribute("deadline"), DATE_FORMAT);
    tmpTask.isCompleted = child.attribute("state").toInt();
    tmpTask.description = child.attribute("description");
    return tmpTask;
}

