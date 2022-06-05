#ifndef PASSWORDSMODEL_H
#define PASSWORDSMODEL_H

#include <QLabel>
#include <QVector>
#include <QAbstractTableModel>
#include <passwordinterface.h>
#include <qplugin.h>
#include <qstandarditemmodel.h>

struct Password
{
    QString service;
    QString login;
    QString password;
    QString numberOfClicks;
    Password(const QString service, const QString login, const QString password, const QString numberOfClicks):
        service(service),
        login(login),
        password(password),
        numberOfClicks(numberOfClicks)
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

inline bool frequencyGreaterThan(Password &pass1, Password &pass2)
{
    return pass1.numberOfClicks > pass2.numberOfClicks;
}

class PasswordsModel : public QAbstractTableModel {
    Q_OBJECT
public:
    enum ManagerEnum {
         SERVICE=0, LOGIN, PASSWORD, CLICKS
     };
    PasswordsModel(QObject *parent = 0);
    PasswordsModel(const QVector<Password> &passwords, QObject *parent = 0);
    inline static int iterator = 0;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool setDataCustom(const QModelIndex &index, const QVariant &value, int column);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    const QVector<Password> &getPasswords() const;
    void addEntity(Password password);
    bool removeAllData();
    void removePassword(int index);
    bool EditEntity(int index);
    QString maskPassword(int length);
    bool sortEnabled;
    bool moveItem(const QModelIndex &fromParent, int fromRow,
            const QModelIndex &toParent, int toRow,	 bool up);

private:
    QVector<Password> passwordList;
private slots:

};

#endif // PASSWORDSMODEL_H
