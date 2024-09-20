#include "datetimedialog.h"
#include "ui_datetimedialog.h"

DateTimeDialog::DateTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateTimeDialog)
{
    ui->setupUi(this);
    ui->okPushButton->setDefault(true);
}

DateTimeDialog::~DateTimeDialog()
{
    delete ui;
}

QList<QDateTime> DateTimeDialog::getCustomRange()
{
    QList<QDateTime> list = {ui->fromDateTimeEdit->dateTime(), ui->toDateTimeEdit->dateTime()};
    return list;
}

void DateTimeDialog::on_okPushButton_clicked()
{
    if (ui->fromDateTimeEdit->dateTime() > ui->toDateTimeEdit->dateTime())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning (ノ ゜Д゜)ノ ︵ ┻━┻");
        msgBox.setText("The first Date&Time should be earlier than the second one!!!");
        msgBox.exec();
        return;
    }
    accept();
}


void DateTimeDialog::on_cancelPushButton_clicked()
{
    reject();
}

