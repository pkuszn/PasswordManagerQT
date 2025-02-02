#include "passwordsmodel.h"
#include <QDebug>
#include <QItemSelection>
#include <QString>
#include <cstdlib>
#include <qfile.h>
#include <qmessagebox.h>
#include <QFileDialog>
#include <qmessagebox.h>
#include <stdlib.h>

PasswordsModel::PasswordsModel(QObject *parent)
    :QAbstractTableModel(parent)
{
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
    case ManagerEnum::CLICKS:
        return password.numberOfClicks;
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
            break;
        case 1:
            passwordList[row].login = value.toString();
            break;
        case 2:
            passwordList[row].password = value.toString();
            break;
        case 3:
            passwordList[row].numberOfClicks = value.toString();
            break;
        default:
            return false;
        }
        if(sortEnabled){
            std::sort(passwordList.begin(),passwordList.end(), frequencyGreaterThan);
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool PasswordsModel::setDataCustom(const QModelIndex &index, const QVariant &value, int column)
{
    if (index.isValid() && !(index.row() >= passwordList.size() || index.row() < 0))
    {
        int row = index.row();

        switch(column)
        {
        case 0:
            passwordList[row].service = value.toString();
            break;
        case 1:
            passwordList[row].login = value.toString();
            break;
        case 2:
            passwordList[row].password = value.toString();
            break;
        case 3:
            passwordList[row].numberOfClicks = value.toString();
            break;
        default:
            return false;
        }
        if(sortEnabled){
            std::sort(passwordList.begin(),passwordList.end(), frequencyGreaterThan);
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void PasswordsModel::addEntity(Password password)
{
    beginInsertRows(QModelIndex(),passwordList.size(),passwordList.size());
    passwordList.append(password);
    if(sortEnabled){
        std::sort(passwordList.begin(),passwordList.end(), frequencyGreaterThan);
    }
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
    if(sortEnabled){
        std::sort(passwordList.begin(),passwordList.end(), frequencyGreaterThan);
    }
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

QString PasswordsModel::maskPassword(int length){
    QString characters;
    for(int i = 0; i<length; i++){
        characters.append("*");
    }
    return characters;
}

bool PasswordsModel::moveItem(const QModelIndex &fromParent, int fromRow,
                              const QModelIndex &toParent, int toRow,	 bool up)
{
    QModelIndex to = index(toRow, 0, toParent);
    QModelIndex from = index(fromRow, 0, fromParent);
    QPersistentModelIndex pCurrent = from;
    changePersistentIndex(pCurrent, index(toRow, 0, toParent));
    if (up)
    {
        removeRows(fromRow + 1, 1, fromParent);
    }
    else
    {
        removeRows(fromRow + 1, 1, fromParent);
    }
}
