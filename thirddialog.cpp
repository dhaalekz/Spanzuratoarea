#include "thirddialog.h"
#include "ui_thirddialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QTSql>

QString user2,rasp,par;
QString ans;

ThirdDialog::ThirdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThirdDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    ui->buttonBox->setVisible(false);
    setWindowTitle("Spanzuratoarea - Recuperare parola");
    ui->label_4->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->label_2->setText("Introdu numele de utilizator:");
    ui->pushButton->setVisible(false);
    ui->label_3->setVisible(false);
    //QString user2=ui->lineEdit_2->text();
   // qDebug()<<user2;
    //QSqlQuery
}

ThirdDialog::~ThirdDialog()
{
    delete ui;
}

void ThirdDialog::on_pushButton_clicked()
{

    qDebug()<<user2;
    QSqlQuery querythird;
    ui->buttonBox->setVisible(true);
    ui->pushButton->setVisible(false);
    int i=0;
    querythird.exec("select nume from users where nume='"+user2+"'");
   // querythird.next();

    while(querythird.next()){
        i++;
        qDebug()<<querythird.value(0);
    }
    if(i==1){
    querythird.exec("SELECT quest FROM users WHERE nume = '"+user2+"'");
    querythird.next();
    ui->label_3->setText(querythird.value(0).toString());
    ui->lineEdit_2->setVisible(false);
    ui->label_3->setVisible(true);
    ui->label_2->setText("Intrebare: ");
    ui->label_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 14px");
    ui->lineEdit->setVisible(true);
    ui->label_4->setVisible(true);
    qDebug()<<querythird.value(0).toString();
    }
    else{
        ui->buttonBox->setVisible(false);
        ui->pushButton->setVisible(true);
        QMessageBox::critical(this,tr("Eroare!"),tr("Utilizatorul nu exista!"));

    }
    querythird.exec("SELECT answ FROM users WHERE nume = '"+user2+"'");
    querythird.next();
    ans=querythird.value(0).toString();
    qDebug()<<ans;
    querythird.exec("SELECT pass FROM users WHERE nume = '"+user2+"'");
    querythird.next();
    par=querythird.value(0).toString();
    qDebug()<<par;

}

void ThirdDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    user2=arg1;
    ui->pushButton->setVisible(true);
}

void ThirdDialog::on_buttonBox_accepted()
{
    qDebug()<<rasp;
    if(ans==rasp){
        par="Parola ta este: "+par;
        QMessageBox::information(this,tr("Parola ta este:"),par);
    }
    else{
        QMessageBox::critical(this,tr("Eroare!"),tr("Ai raspuns gresit la intrebare!"));
    }
}

void ThirdDialog::on_buttonBox_rejected()
{
    qDebug()<<"test";
}

void ThirdDialog::on_lineEdit_textChanged(const QString &arg1)
{
    rasp=arg1;
}
