#include "passworddomain.h"
#include <stdlib.h>
#include <qdebug.h>
#include <qstring.h>

PasswordDomain::PasswordDomain()
{
    setPassword(generatePassword());
}

PasswordDomain::~PasswordDomain()
{
}

const QString &PasswordDomain::getPassword() const
{
    return password;
}

void PasswordDomain::setPassword(const QString &newPassword)
{
    password = newPassword;
}

//TODO: Improve generating passwords
QString PasswordDomain::generatePassword()
{
    const char alphanum[] = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    srand(time(0));
    int targetLengthPassword = 15;
    int charArrayLength = sizeof(alphanum)-1;
    char generatedPasswordCharArray[targetLengthPassword];
    for(int i = 0; i<targetLengthPassword; i++){
        generatedPasswordCharArray[i] = alphanum[rand() & charArrayLength];
    }
    qDebug() << generatedPasswordCharArray;
    QString generatedPassword = QString::fromLatin1(generatedPasswordCharArray);
    qDebug() << QString::fromLatin1(generatedPasswordCharArray);
    return generatedPassword;
}





