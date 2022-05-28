#include "newinstancedialog.h"
#include "ui_newinstancedialog.h"
#include <PasswordDomain.h>
#include <QDialog>

NewInstanceDialog::NewInstanceDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewInstanceDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(close()));

}

NewInstanceDialog::~NewInstanceDialog()
{
    delete ui;
}


void NewInstanceDialog::on_pushButton_clicked()
{
    emit sendInstance(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text());

}


void NewInstanceDialog::on_pushButton_3_clicked()
{
    ui->lineEdit_3->clear();
    PasswordDomain *domain = new PasswordDomain();
    ui->lineEdit_3->setText(domain->getPassword());
}

