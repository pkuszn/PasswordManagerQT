#ifndef PASSWORDSMODEL_H
#define PASSWORDSMODEL_H

#include <QLabel>
#include <QVector>
#include <QAbstractTableModel>
#include <passwordinterface.h>
#include <qplugin.h>
struct Password
{
    QString service;
    QString login;
    QString password;
    Password(const QString service, const QString login, const QString password):
        service(service),
        login(login),
        password(password)
    {

    }
};

inline QDataStream &operator<<(QDataStream &stream, const Password &password)
{
    return stream << password.service << password.login << password.password;
}

inline QDataStream &operator>>(QDataStream &stream, Password &password)
{
    return stream >> password.service >> password.login >> password.password;
}

class PasswordsModel : public QAbstractTableModel {
    Q_OBJECT
public:
    enum ManagerEnum {
         SERVICE=0, LOGIN, PASSWORD
     };
    PasswordsModel(QObject *parent = 0);
    PasswordsModel(const QVector<Password> &contacts, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    const QVector<Password> &getPasswords() const;

private:
    QVector<Password> passwordList;
private slots:

};

#endif // PASSWORDSMODEL_H
