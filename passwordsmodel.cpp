#include "passwordsmodel.h"
#include <QDebug>
#include <stdlib.h>
#include <algorithm>

PasswordsModel::PasswordsModel(QObject *parent)
    :QAbstractTableModel(parent)
{
    passwordList
            << *new Password("mBank", "patryk98", ":12345")
            << *new Password("Facebook", "mokoloko", "435425")
            << *new Password("PayPal", "mitoman111", "flags123")
            << *new Password("pobieraczek.com", "Washington, D.CxD", "asdsadasd");
}

PasswordsModel::PasswordsModel(const QVector<Password> &passwords, QObject *parent)
    : QAbstractTableModel(parent),
      passwordList(passwords)
{

}

int PasswordsModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : passwordList.size();
}

int PasswordsModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 1;
}

QVariant PasswordsModel::data(const QModelIndex& index, int role) const
{
    const auto & password = passwordList.at(index.row());
    if(!index.isValid()){
        return QVariant();
    }
    if(index.row() >= passwordList.size() || index.row() < 0) {
        return QVariant();
    }
    switch(role){
    case ManagerEnum::SERVICE:
        return password.service;
    case ManagerEnum::LOGIN:
        return password.login;
    case ManagerEnum::PASSWORD:
        return password.password;
    default:
        break;
    }
    return QVariant();
}

QVariant PasswordsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return tr("Service");
        }
    }
    return QVariant();
}

Qt::ItemFlags PasswordsModel::flags(const QModelIndex &index) const
{
    return !index.isValid() ? Qt::ItemIsEnabled : (QAbstractTableModel::flags(index) | Qt::ItemIsEditable);
}

bool PasswordsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

void PasswordsModel::addEntity(Password password)
{
    if(passwordList.count() == 0 || password.service == nullptr){
        return;
    }
    beginInsertRows(QModelIndex(),passwordList.size(),passwordList.size() + 9);
    passwordList.append(password);
    endInsertRows();
}

bool PasswordsModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        passwordList.insert(position, { QString(), QString(), QString() });
    endInsertRows();
    return true;
}

bool PasswordsModel::removeRows(int position, int rows, const QModelIndex &index)
{
    return false;
}

const QVector<Password> &PasswordsModel::getPasswords() const
{
    return passwordList;
}

