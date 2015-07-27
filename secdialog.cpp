#include "secdialog.h"
#include "ui_secdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QTSql>

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    setWindowTitle("Spanzuratoarea - Inregistrare");
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_buttonBox_accepted()
{
    QSqlQuery qrysec;
    QString usern,passw,intreb,rasp;
    usern=ui->lineEdit->text();
    passw=ui->lineEdit_2->text();
    intreb=ui->lineEdit_3->text();
    rasp=ui->lineEdit_4->text();
    qrysec.exec("INSERT INTO users VALUES('"+usern+"',0,0,'"+passw+"','"+intreb+"','"+rasp+"',0)");
    QMessageBox::information(this,tr("Succes"),tr("Utilizatorul a fost inregistrat cu succes, va puteti conecta!"));
    qDebug()<<"Merge";
}
