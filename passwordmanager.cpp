#include "passwordmanager.h"
#include "ui_passwordmanager.h"
#include <QItemSelectionModel>
#include <QDebug>
#include <QColor>
#include <ui_newinstancedialog.h>
#include "passwordsmodel.h"


PasswordManager::PasswordManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PasswordManager),
    model()
{

    ui->setupUi(this);

    configure();
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
    ui->label_4->setText(login);
    QString password = index.data(2).toString();
    ui->label_5->setText(password);
}

void PasswordManager::setColumnWidth(int size)
{
    for (int col=0; col<20; col++)
    {
       ui->tableView->setColumnWidth(col,size);
    }
}

void PasswordManager::setLabel(QLabel &label, int size, bool bold, QColor color)
{
    QFont font = label.font();
    font.setPointSize(size);
    font.setBold(bold);
    label.setFont(font);
    if(color == nullptr){
        return;
    }
    QPalette palette = ui->label->palette();
    palette.setColor(ui->label->foregroundRole(), color);
    ui->label->setPalette(palette);
}

void PasswordManager::configure(){
    setWindowTitle("PasswordManager");
    setLabel(*ui->label, 25, true, Qt::blue);
    ui->tableView->setModel(&model);
    setColumnWidth(ui->tableView->width()-5);
    setLabel(*ui->label_6, 20, true, nullptr);
    setLabel(*ui->label_7, 20, true, nullptr);
}

void PasswordManager::on_pushButton_clicked()
{
    NewInstanceDialog *dialog = new NewInstanceDialog();
    connect(dialog, &NewInstanceDialog::sendInstance, this, &PasswordManager::on_textEdited);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void PasswordManager::on_textEdited(QString service, QString login, QString password)
{
    ui->label_8->setText(service);
    ui->label_8->setText(login);
    ui->label_8->setText(password);

}

