#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QWidget>

namespace Ui {
class EditWidget;
}

class EditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditWidget(QWidget *parent = nullptr);
    ~EditWidget();

signals:
    void sendEditedInstance(QString service, QString login, QString password);

public slots:
    void on_receivedText(QString service, QString login, QString password);
    void on_pushButton_clicked();

private:
    Ui::EditWidget *ui;
};

#endif // EDITWIDGET_H
