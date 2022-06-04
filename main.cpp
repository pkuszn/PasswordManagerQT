#include "passwordmanager.h"
#include "ui_passwordmanager.h"
#include <QApplication>
#include "passwordsmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PasswordManager w;
    QString filePath = QApplication::applicationDirPath() + "/main.txt";
    w.ReadOnStartup(filePath);
    w.show();
    return a.exec();
}
