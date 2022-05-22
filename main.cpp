#include "passwordmanager.h"
#include "ui_passwordmanager.h"
#include <QApplication>
#include "passwordsmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PasswordManager w;
    w.show();
    return a.exec();
}
