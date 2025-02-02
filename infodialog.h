#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = nullptr);
    ~InfoDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::InfoDialog *ui;
    void configure();
};

#endif // INFODIALOG_H
