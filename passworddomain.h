#ifndef PASSWORDDOMAIN_H
#define PASSWORDDOMAIN_H

#include <QString>



class PasswordDomain
{
public:
    PasswordDomain();
    PasswordDomain(int length);
    ~PasswordDomain();
    QString password;
    int length;

    const QString &getPassword() const;
    void setPassword(const QString &newPassword);

private:
    QString generatePassword(int length);

};

#endif // PASSWORDDOMAIN_H
