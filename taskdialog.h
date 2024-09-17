#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include "task.h"
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class TaskDialog;
}

class TaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskDialog(QWidget *parent = nullptr);
    explicit TaskDialog(Task selectedTask);
    ~TaskDialog();
    Task getTaskFromFields();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::TaskDialog *ui;
};

#endif // TASKDIALOG_H
