#include "passworddomain.h"
#include <stdlib.h>

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

QString PasswordDomain::generatePassword()
{
    srand(time(NULL));

    int targetLengthPassword = rand() & 50 + 8;
    char generatedPasswordCharArray[targetLengthPassword];
    for(int i = 0; i<=targetLengthPassword; i++){
        generatedPasswordCharArray[i] = convertAsciiToChar(rand() & 33 + 93);
    }
    QString generatedPassword(generatedPasswordCharArray);
    return generatedPassword;
}

char PasswordDomain::convertAsciiToChar(int number)
{
    char value = char(number);
    return value;
}
