#include "passwordmanager.h"
#include "ui_passwordmanager.h"
#include <QItemSelectionModel>
#include <QDebug>
#include "passwordsmodel.h"


PasswordManager::PasswordManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PasswordManager),
    model()
{

    ui->setupUi(this);
    setWindowTitle("PasswordManager");
    ui->tableView->setModel(&model);
    setColumnWidth(ui->tableView->width()-5);
    QItemSelectionModel* selectionModel = ui->tableView->selectionModel();
     connect(selectionModel, &QItemSelectionModel::selectionChanged,
             this, &PasswordManager::onSelectionChanged);

}

PasswordManager::~PasswordManager()
{
    delete ui;
}

void PasswordManager::onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{

    Q_UNUSED(deselected)
    if(selected.indexes().isEmpty()){
        // do nothing
        return;
    }
    QModelIndexList list = selected.indexes();
    const QModelIndex& index = list.first();

    QString login = index.data(1).toString();
    ui->label_5->setText(login);
    QString password = index.data(2).toString();
    ui->label_4->setText(password);
}

void PasswordManager::setColumnWidth(int size)
{
    for (int col=0; col<20; col++)
    {
       ui->tableView->setColumnWidth(col,size);
    }
}

