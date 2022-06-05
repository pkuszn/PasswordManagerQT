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
    void configure();

signals:
    void updateTicksLabel(int ticks);

signals:
    void sendInstance(QString service, QString login, QString password);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_receivedTicks(int value);
};

#endif // NEWINSTANCEDIALOG_H
