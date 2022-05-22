#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include "passwordsmodel.h"

#include <QItemSelection>
#include <QMainWindow>

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

private:
    Ui::PasswordManager *ui;
    PasswordsModel model;
};
#endif // PASSWORDMANAGER_H
