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
    const char numbers[] = "0123456789";
    const char symbols[] = "!@#$%^&*";
    const char letter[] = "abcdefghijklmnopqrstuvwxyz";
    const char LETTER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    srand((unsigned int)(time(NULL)));
    int length = rand() % 30 * 8;
    char password[length];
    int i = 0;
    int randomizer = 0;
    for (i = 0; i < length; i++) {

           if (randomizer == 1) {
               password[i] = numbers[rand() % 10];
               randomizer = rand() % 4;
           }
           else if (randomizer == 2) {
               password[i] = symbols[rand() % 8];
               randomizer = rand() % 4;
           }
           else if (randomizer == 3) {
               password[i] = LETTER[rand() % 26];
               randomizer = rand() % 4;
           }
           else {
               password[i] = letter[rand() % 26];
               randomizer = rand() % 4;
           }
       }
    QString generatedPassword = QString::fromLatin1(password);
    return generatedPassword;
}





