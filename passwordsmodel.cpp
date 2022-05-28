#include "passwordsmodel.h"
#include <QDebug>
#include <QItemSelection>
#include <QString>
#include <cstdlib>

PasswordsModel::PasswordsModel(QObject *parent)
    :QAbstractTableModel(parent)
{
    passwordList
            << *new Password("mBank", "patryk98", ":12345", "0")
            << *new Password("Facebook", "mokoloko", "435425", "0")
            << *new Password("PayPal", "mitoman111", "flags123", "0")
            << *new Password("pobieraczek.com", "Washington, D.CxD", "asdsadasd", "0");
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
    case ManagerEnum::FREQUENCY:
        return password.frequency;
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
    if (index.isValid() && role == Qt::EditRole && !(index.row() >= passwordList.size() || index.row() < 0))
        {
            int row = index.row();

            switch(index.column())
            {
            case 0:
                passwordList[row].service = value.toString();
                passwordList[row].login = value.toString();
                passwordList[row].password = value.toString();
                break;
            case 1:
                passwordList[row].login = value.toString();
                break;
            case 2:
                passwordList[row].password = value.toString();
                break;
            case 3:
                passwordList[row].frequency = value.toString();
                break;
            default:
                return false;
            }
            emit dataChanged(index, index);
            return true;
        }
        return false;
}



bool PasswordsModel::EditEntity(int index){


}

void PasswordsModel::addEntity(Password password)
{
    beginInsertRows(QModelIndex(),passwordList.size(),passwordList.size() + 1);
    passwordList.append(password);
    endInsertRows();
}

bool PasswordsModel::removeAllData()
{
    if(passwordList.count() < 0){
        return false;
    }
    int beginRow = 0;
    int endRow = beginRow + passwordList.size()-1;
    beginRemoveRows(QModelIndex(), beginRow, endRow);
    passwordList.clear();
    endRemoveRows();
    return true;
}

void PasswordsModel::removePassword(int index)
{
    if(index < 0){
        return;
    }
    beginRemoveRows(QModelIndex(), index, index);
    passwordList.removeAt(index);
    endRemoveRows();
}



bool PasswordsModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        passwordList.insert(position, { QString(), QString(), QString(), QString() });
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

//TODO: mask password return masked password with the same length like original
QString PasswordsModel::maskPassword(){
    QString password = "*************";
    return password;
}

