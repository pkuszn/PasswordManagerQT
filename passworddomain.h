#ifndef PASSWORDDOMAIN_H
#define PASSWORDDOMAIN_H

#include <QString>



class PasswordDomain
{
public:
    PasswordDomain();
    ~PasswordDomain();
    QString password;

    const QString &getPassword() const;
    void setPassword(const QString &newPassword);

private:
    QString generatePassword();
    char convertAsciiToChar(int number);
};

#endif // PASSWORDDOMAIN_H
