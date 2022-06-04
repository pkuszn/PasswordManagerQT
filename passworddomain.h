#ifndef PASSWORDDOMAIN_H
#define PASSWORDDOMAIN_H

#include <QString>



class PasswordDomain
{
public:
    PasswordDomain();
    PasswordDomain(int length);
    ~PasswordDomain();
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);

private:
    QString generatePassword(int length);
    QString password;
    int length;
};

#endif // PASSWORDDOMAIN_H
