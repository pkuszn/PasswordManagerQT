#ifndef NEWINSTANCEDIALOG_H
#define NEWINSTANCEDIALOG_H

#include <QString>
#include <QWidget>

namespace Ui {
class NewInstanceDialog;
}

class NewInstanceDialog : public QWidget
{
    Q_OBJECT

public:
    explicit NewInstanceDialog(QWidget *parent = nullptr);
    ~NewInstanceDialog();

private:
    Ui::NewInstanceDialog *ui;

signals:
    void sendInstance(QString service, QString login, QString password);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
};

#endif // NEWINSTANCEDIALOG_H
