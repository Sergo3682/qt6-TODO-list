#ifndef DATETIMEDIALOG_H
#define DATETIMEDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class DateTimeDialog;
}

class DateTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DateTimeDialog(QWidget *parent = nullptr);
    // QDateTime getFromDateTime();
    // QDateTime getToDateTime();
    QList<QDateTime> getCustomRange();
    ~DateTimeDialog();

private slots:
    void on_okPushButton_clicked();
    void on_cancelPushButton_clicked();

private:
    Ui::DateTimeDialog *ui;
};

#endif // DATETIMEDIALOG_H
