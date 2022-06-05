#include "newinstancedialog.h"
#include "ui_newinstancedialog.h"
#include <passworddomain.h>
#include <QDialog>

NewInstanceDialog::NewInstanceDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewInstanceDialog)
{
    ui->setupUi(this);
    configure();
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(close()));
    ui->textEdit->setToolTip("You can simply generate a new password using 'Generate' Button. Set the password length using horizontal slider.");
}

NewInstanceDialog::~NewInstanceDialog()
{
    delete ui;
}

void NewInstanceDialog::configure()
{
    QFont font = ui->label_5->font();
    font.setBold(true);
    font.setPointSize(15);
    ui->label_5->setFont(font);
    font.setPointSize(12);
    ui->label_6->setFont(font);

}


void NewInstanceDialog::on_pushButton_clicked()
{
    emit sendInstance(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->textEdit->toPlainText());
    NewInstanceDialog::close();
}


void NewInstanceDialog::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
    PasswordDomain *domain = new PasswordDomain(ui->horizontalSlider->value());
    ui->textEdit->setText(domain->getPassword());
}


void NewInstanceDialog::on_horizontalSlider_valueChanged(int value)
{
    connect(this, &NewInstanceDialog::updateTicksLabel, this, &NewInstanceDialog::on_receivedTicks);
    emit updateTicksLabel(value);
}

void NewInstanceDialog::on_receivedTicks(int value)
{
    QString ticks = QString::number(value);
    ui->label_6->setText(ticks);
}

