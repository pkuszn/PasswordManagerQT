#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include "passwordsmodel.h"

#include <newinstancedialog.h>
#include <QItemSelection>
#include <QMainWindow>
#include <QTableView>
#include <qpushbutton.h>
#include <qstandarditemmodel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class PasswordManager; }
QT_END_NAMESPACE

class PasswordManager : public QMainWindow
{
    Q_OBJECT

public:
    PasswordManager(QWidget *parent = 0);
    ~PasswordManager();
    void ReadOnStartup(QString filePath);
    void AddFileToArchive(const QString fileName, const QString password);

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
    void on_actionSave_triggered();
    void on_actionOpenm_triggered();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_actionExit_triggered();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();

    void on_checkBox_stateChanged(int arg1);

signals:
    void sendInstanceToEdit(QString service, QString login, QString password);

private:
    QString filename;
    Ui::PasswordManager *ui;
    PasswordsModel model;
    NewInstanceDialog *dialog;
    void SaveToFile(QList<Password> passwordList);
    void SaveToFile(QString filePath, QList<Password> passwordList);
    QList<Password> ReadFromFile();
    const QString &getFilename() const;
    void setFilename(const QString &newFilename);
    void addIconToButton(QPushButton *button, QString filePath);
    void setButtonSize(QPushButton *button, int width, int height);
    void MoveRow(bool moveUp);

};
#endif // PASSWORDMANAGER_H
