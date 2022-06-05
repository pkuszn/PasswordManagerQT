#include "editwidget.h"
#include "ui_editwidget.h"

#include <qstring.h>

EditWidget::EditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditWidget)
{
    ui->setupUi(this);
    configure();
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


void EditWidget::on_pushButton_2_clicked()
{
    EditWidget::close();
}

void EditWidget::configure()
{
    QFont font;
    font.setPointSize(15);
    ui->label_5->setFont(font);
}

