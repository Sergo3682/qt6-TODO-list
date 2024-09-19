#include "taskdialog.h"
#include "ui_taskdialog.h"

TaskDialog::TaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskDialog)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime().addDays(1));
}

TaskDialog::TaskDialog(Task selectedTask) :
    ui(new Ui::TaskDialog)
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(selectedTask.name);
    ui->descriptionTextEdit->setPlainText(selectedTask.description);
    ui->dateTimeEdit->setDateTime(selectedTask.deadline);
    currentState = selectedTask.isCompleted;
}

TaskDialog::~TaskDialog()
{
    delete ui;
}

Task TaskDialog::getTaskFromFields()
{
    Task tmpTask;
    tmpTask.name = ui->nameLineEdit->text();
    tmpTask.description = ui->descriptionTextEdit->toPlainText();
    tmpTask.deadline = ui->dateTimeEdit->dateTime();
    tmpTask.isCompleted = currentState;
    return tmpTask;
}

void TaskDialog::on_buttonBox_accepted()
{
    if (ui->nameLineEdit->text().size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning (ノ ゜Д゜)ノ ︵ ┻━┻");
        msgBox.setText("Name field cannot be empty!!!");
        msgBox.exec();
        return;
    }
    accept();
}

void TaskDialog::on_buttonBox_rejected()
{
    reject();
}

