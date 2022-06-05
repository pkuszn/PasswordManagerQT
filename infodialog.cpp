#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
    configure();
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::on_buttonBox_accepted()
{
    InfoDialog::close();
}

void InfoDialog::configure()
{
    QFont font;
    font.setPointSize(9);
    ui->label_6->setFont(font);
    ui->label_7->setFont(font);
    ui->label_8->setFont(font);
    ui->label_9->setFont(font);
    QFont font2;
    font2.setPointSize(15);
    ui->label->setFont(font2);
    QFont font3;
    font3.setPointSize(13);
    ui->label_2->setFont(font3);
    ui->label_3->setFont(font3);
    ui->label_5->setFont(font3);
    ui->label_10->setFont(font3);
}

