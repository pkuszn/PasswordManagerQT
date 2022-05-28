#include "passwordmanager.h"
#include "ui_passwordmanager.h"
#include <QItemSelectionModel>
#include <QDebug>
#include <QColor>
#include <ui_newinstancedialog.h>
#include <QItemSelection>
#include "infodialog.h"
#include "passwordsmodel.h"
#include <editwidget.h>
#include <QtAlgorithms>
#include <editwidget.h>



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

void PasswordManager::configure(){
    setWindowTitle("PasswordManager");
    setLabel(*ui->label, 25, true, Qt::blue);
    ui->tableView->setModel(&model);
    setColumnWidth(ui->tableView->width()-5);
    setLabel(*ui->label_6, 20, true, nullptr);
    setLabel(*ui->label_7, 20, true, nullptr);
}

void PasswordManager::onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{

    Q_UNUSED(deselected)
    if(selected.indexes().isEmpty()){
        return;
    }
    QModelIndexList list = selected.indexes();
    const QModelIndex& index = list.first();

    QString login = index.data(1).toString();
    ui->label_4->setText(login);
    QString password;
    if(ui->radioButton->isChecked()){
        password = model.maskPassword();
    }
    else{
        password = index.data(2).toString();
    }
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


void PasswordManager::on_pushButton_clicked()
{
    NewInstanceDialog *dialog = new NewInstanceDialog();
    connect(dialog, &NewInstanceDialog::sendInstance, this, &PasswordManager::on_textEdited);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void PasswordManager::on_textEdited(QString service, QString login, QString password)
{
    if(service.length () == 0 || login.length() == 0 || password.length() == 0){
        return;
    }
    const auto& passwordEntity = new Password(service, login, password, "0");
    model.addEntity(*passwordEntity);
}

void PasswordManager::on_receivedEditedInstance(QString service, QString login, QString password)
{
    if(service.length () == 0 || login.length() == 0 || password.length() == 0){
        return;
    }
    if(ui->tableView){
    //TODO: implement edit function
        QModelIndex currentIndex = ui->tableView->selectionModel()->currentIndex();
        model.setData(currentIndex.column, service);

    }
}


void PasswordManager::on_pushButton_3_clicked()
{
    if(ui->tableView){
        QModelIndex currentIndex = ui->tableView->selectionModel()->currentIndex();
        model.removePassword(currentIndex.row());
    }
}


void PasswordManager::on_actionClear_all_triggered()
{
    if(ui->tableView){
        model.removeAllData();
    }
}


void PasswordManager::on_actionAbout_author_triggered()
{
    InfoDialog *dlg = new InfoDialog();
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}


void PasswordManager::on_pushButton_2_clicked()
{
    EditWidget *editWidget = new EditWidget();
    if(ui->tableView){
        QModelIndex currentIndex = ui->tableView->selectionModel()->currentIndex();
        connect(this, &PasswordManager::sendInstanceToEdit, editWidget, &EditWidget::on_receivedText);
        emit sendInstanceToEdit(currentIndex.data(0).toString(), currentIndex.data(1).toString(), currentIndex.data(2).toString());
        editWidget->setAttribute(Qt::WA_DeleteOnClose);
        editWidget->show();
    }
    bool succeeded = connect(editWidget, &EditWidget::sendEditedInstance, this, &PasswordManager::on_receivedEditedInstance);
    qDebug() << succeeded;
}


