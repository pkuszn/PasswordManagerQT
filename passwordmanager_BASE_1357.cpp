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
#include <QFileDialog>
#include <qmessagebox.h>



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
    QString password = ui->radioButton->isChecked() ? model.maskPassword() : index.data(2).toString();
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


void PasswordManager::SaveToFile(QList<Password> passwordList)
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Password Instance"), "",
                                                    tr("Password Instance (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::Append | QFile::Text) ) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QTextStream out(&file);
        foreach(Password password, passwordList){
            out << password.service + "," + password.login + "," + password.password + "," + password.frequency + "\n";
        }
    }
}

QList<Password> PasswordManager::ReadFromFile(){
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Password File"), "",
                                                    tr("Password Instance (*.txt);;All Files (*)"));

    QList<Password> passwordList;
    if(filename.isEmpty()){
        return passwordList;
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::information(this, tr("Unable to open file"),
                                 file.errorString());
        return passwordList;
    }

    QTextStream in(&file);
    QStringList itemList;
    while(true){
        QString line = in.readLine();
        if(line.isNull()){
            break;
        }
        itemList.append(line);
    }
    for(int i = 0; i<itemList.count(); i++){
        QString str = itemList.at(i);
        QStringList elements = str.split(",");
        passwordList.append(*new Password(elements.at(0), elements.at(1), elements.at(2), elements.at(3)));
    }
    return passwordList;
}


const QString &PasswordManager::getFilename() const
{
    return filename;
}

void PasswordManager::setFilename(const QString &newFilename)
{
    filename = newFilename;
}

void PasswordManager::on_actionSave_triggered()
{
    SaveToFile(model.getPasswords());
}

void PasswordManager::on_actionOpenm_triggered()
{
    QList<Password> passwordList = ReadFromFile();
    foreach(Password password, passwordList){
        model.addEntity(password);
    }
}

