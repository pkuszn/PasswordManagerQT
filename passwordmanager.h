#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include "passwordsmodel.h"

#include <editwidget.h>
#include <newinstancedialog.h>
#include <QItemSelection>
#include <QMainWindow>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui { class PasswordManager; }
QT_END_NAMESPACE

class PasswordManager : public QMainWindow
{
    Q_OBJECT

public:
    PasswordManager(QWidget *parent = 0);
    ~PasswordManager();

private slots:
    void onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void configure();
    void setColumnWidth(int size);
    void setLabel(QLabel& label, int size, bool bold = false, QColor color = false);
    void on_pushButton_clicked();
    void on_textEdited(QString service, QString login, QString password);
    void on_receivedEditedInstance(QString service, QString login, QString password);

    void on_pushButton_3_clicked();

    void on_actionClear_all_triggered();

    void on_actionAbout_author_triggered();

    void on_pushButton_2_clicked();

signals:
    void sendInstanceToEdit(QString service, QString login, QString password);

private:
    Ui::PasswordManager *ui;
    PasswordsModel model;
    NewInstanceDialog *dialog;
    EditWidget *editWidget = nullptr;
};
#endif // PASSWORDMANAGER_H
