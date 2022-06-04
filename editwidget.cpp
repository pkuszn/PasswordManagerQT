#include "editwidget.h"
#include "ui_editwidget.h"

#include <qstring.h>

EditWidget::EditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditWidget)
{
    ui->setupUi(this);
}

EditWidget::~EditWidget()
{
    delete ui;
}

void EditWidget::on_receivedText(QString service, QString login, QString password)
{
    ui->lineEdit->setText(service);
    ui->lineEdit_2->setText(login);
    ui->textEdit->setText(password);
}

void EditWidget::on_pushButton_clicked()
{
    emit sendEditedInstance(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->textEdit->toPlainText());
    EditWidget::close();
}

