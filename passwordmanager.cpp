#include "passwordmanager.h"
#include "ui_passwordmanager.h"
#include <QItemSelectionModel>
#include <QDebug>
#include <QColor>
#include <ui_newinstancedialog.h>
#include <QItemSelection>
#include "infodialog.h"
#include "passwordsmodel.h"
#include "passwordsmodel.h"
#include <QtAlgorithms>
#include <QFileDialog>
#include <qmessagebox.h>
#include <QSortFilterProxyModel>
#include <editwidget.h>
#include <QClipboard>
#include <qapplication.h>
#include <QStandardItemModel>



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
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setDragEnabled(true);
    ui->tableView->setAcceptDrops(true);
    ui->tableView->setDragDropMode(QAbstractItemView::DragDrop);
    ui->tableView->setDefaultDropAction(Qt::MoveAction);
    ui->tableView->setDragDropOverwriteMode(false);
    ui->tableView->setDropIndicatorShown(true);
}

PasswordManager::~PasswordManager()
{
    delete ui;
}

void PasswordManager::configure(){
    setWindowTitle("PasswordManager");
    setLabel(*ui->label, 20, true, Qt::black);
    ui->tableView->setModel(&model);
    setColumnWidth(ui->tableView->width()-10);
    setLabel(*ui->label_6, 15, true, nullptr);
    setLabel(*ui->label_7, 15, true, nullptr);
    addIconToButton(ui->pushButton_6, ":/icons/icons/down-arrow.png");
    addIconToButton(ui->pushButton_7, ":/icons/icons/up-arrow.png");
    setButtonSize(ui->pushButton_6, 30, 25);
    setButtonSize(ui->pushButton_7, 30, 25);

}

void PasswordManager::addIconToButton(QPushButton *button, QString filePath){
    if(filePath.length() == 0){
        return;
    }
    QPixmap pixmap(filePath);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
}

void PasswordManager::setButtonSize(QPushButton *button, int width, int height){
    if(width == 0 || height == 0){
        return;
    }
    const QSize btnSize = QSize(width, height);
    button->setFixedSize(btnSize);
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
    QString password = ui->checkBox_2->isChecked() ? model.maskPassword(index.data(2).toString().length()) : index.data(2).toString();
    ui->label_5->setText(password);
}

void PasswordManager::setColumnWidth(int size)
{
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
        QModelIndex currentIndex = ui->tableView->selectionModel()->currentIndex();
        model.setDataCustom(currentIndex, service, 0);
        model.setDataCustom(currentIndex, login, 1);
        model.setDataCustom(currentIndex, password, 2);
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
            out << password.service + "," + password.login + "," + password.password + "," + password.numberOfClicks + "\n";
        }
    }
}

void PasswordManager::SaveToFile(QString filePath, QList<Password> passwordList)
{
    if (filePath.isEmpty())
        return;
    else {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QFile::Text) ) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QTextStream out(&file);
        foreach(Password password, passwordList){
            out << password.service + "," + password.login + "," + password.password + "," + password.numberOfClicks + "\n";
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

void PasswordManager::ReadOnStartup(QString filePath)
{
    QList<Password> passwordList;
    if(filePath.isEmpty()){
        return;
    }
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::information(this, tr("Unable to open file"),
                                 file.errorString());
        return;
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
    foreach(Password password, passwordList){
        model.addEntity(password);
    }
}

void PasswordManager::AddFileToArchive(const QString fileName, const QString password)
{
    return;
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

void PasswordManager::on_pushButton_5_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString originalText = clipboard->text();
    QModelIndex currentIndex = ui->tableView->selectionModel()->currentIndex();
    int numberOfClicks = currentIndex.data(3).toInt() + 1;
    model.setDataCustom(currentIndex, numberOfClicks, 3);
    clipboard->setText(currentIndex.data(2).toString());
}


void PasswordManager::on_pushButton_4_clicked()
{
    QString filePath = QApplication::applicationDirPath() + "/main.txt";
    SaveToFile(filePath, model.getPasswords());
    QApplication::quit();
}


void PasswordManager::on_actionExit_triggered()
{
    QApplication::quit();
}


void PasswordManager::on_pushButton_6_clicked()
{
    QObject::connect(ui->tableView->verticalHeader(),&QHeaderView::sectionMoved,[=](int logicalIndex, int oldVisualIndex, int newVisualIndex)->void{
        Q_ASSERT(logicalIndex==oldVisualIndex);
        const QModelIndex numberIndex =model.index(1,logicalIndex); /*I use 1 here because of model->setHeaderData(1, Qt::Horizontal, tr("Number")); it looks strange, however, you have nothing at index 0*/
        Q_ASSERT(logicalIndex==numberIndex.data().toInt());
        model.setData(numberIndex,newVisualIndex);
    });
}


void PasswordManager::on_pushButton_7_clicked()
{
    int selectedRow = ui->tableView->currentIndex().row();
    QModelIndex currentIndex = ui->tableView->selectionModel()->currentIndex();
    ui->tableView->model()->moveRow(this->model.index(selectedRow, currentIndex.column()),
                                    selectedRow,
                                    this->model.index(selectedRow+1, currentIndex.column()),
                                    selectedRow+1);
}

void PasswordManager::MoveRow(bool moveUp)
{
return;
}

void PasswordManager::on_checkBox_stateChanged(int arg1)
{
    model.sortEnabled = ui->checkBox->isChecked();
    if(model.sortEnabled){
        ui->pushButton_6->setDisabled(true);
        ui->pushButton_7->setDisabled(true);
    }
    if(!model.sortEnabled){
        ui->pushButton_6->setDisabled(false);
        ui->pushButton_7->setDisabled(false);
    }
}

