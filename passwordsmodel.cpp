#include "passwordsmodel.h"
#include <QDebug>

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
    return parent.isValid() ? 0 : 2;
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
    switch(index.column()){
        case PasswordEnums::SERVICE:
            return password.service;
        case PasswordEnums::LOGIN:
            return password.service;
        case PasswordEnums::PASSWORD:
            return password.service;
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
        case 1:
            return tr("Password");
        case 2:
            return tr("Login");
        }
    }
    return QVariant();
}

Qt::ItemFlags PasswordsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool PasswordsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
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

