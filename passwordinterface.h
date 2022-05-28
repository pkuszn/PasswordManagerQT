#ifndef PASSWORDINTERFACE_H
#define PASSWORDINTERFACE_H
#include <qplugin.h>

class PasswordInterface
{
public:
    QString service;
    QString login;
    QString password;
    virtual bool addNewPassword() = 0;
};
Q_DECLARE_INTERFACE(PasswordInterface, "PasswordInterface");

#endif // PASSWORDINTERFACE_H
