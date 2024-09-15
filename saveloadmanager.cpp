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

void SaveLoadManager::CreateXMLfromTask(QDomElement& child, Task task)
{
    child.setAttribute("name", task.name);
    child.setAttribute("status", task.isCompleted);
    child.setAttribute("deadline", task.deadline.toString(DATE_FORMAT));
    child.setAttribute("description", task.description);
}

