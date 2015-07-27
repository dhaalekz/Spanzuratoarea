#include "admindialog.h"
#include "ui_admindialog.h"
#include <QMessageBox>
#include <QtSql>
#include <QDebug>
#include <QComboBox>

int ok=0;
QString categ,cuvnou;

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    setWindowTitle("Spanzuratoarea - Panou administrator");
    this->setFixedSize(this->size());
    ui->pushButton_15->setVisible(false);
    ui->pushButton_16->setVisible(false);
    ui->label->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->pushButton_18->setVisible(false);
    ui->pushButton_17->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_5->setVisible(false);
    ui->pushButton_19->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
}

AdminDialog::~AdminDialog()
{
    delete ui;
}

void AdminDialog::on_pushButton_10_clicked()
{
    ui->pushButton_15->setVisible(true);
    ui->pushButton_16->setVisible(true);
    ui->pushButton_17->setVisible(true);
    ui->buttonBox->setVisible(false);
    ui->pushButton_10->setVisible(false);
    ui->pushButton_11->setVisible(false);
    ui->pushButton_12->setVisible(false);
    ui->pushButton_13->setVisible(false);
    ui->pushButton_14->setVisible(false);
    ui->label->setVisible(true);
    ui->label->setText("Sterge scorurile pentru: ");
}

void AdminDialog::on_pushButton_17_clicked()
{
    ui->pushButton_15->setVisible(false);
    ui->label->setVisible(false);
    ui->pushButton_16->setVisible(false);
    ui->pushButton_17->setVisible(false);
    ui->pushButton_10->setVisible(true);
    ui->pushButton_11->setVisible(true);
    ui->pushButton_12->setVisible(true);
    ui->pushButton_13->setVisible(true);
    ui->pushButton_14->setVisible(true);
    ui->pushButton_18->setVisible(false);
    ui->buttonBox->setVisible(true);
    ui->lineEdit->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->pushButton_19->setVisible(false);
}

void AdminDialog::on_pushButton_16_clicked()
{
    QMessageBox msgBox;
     msgBox.setText("Ai selectat sa stergi toate scorurile.");
     msgBox.setInformativeText("Esti sigur ca vrei sa faci acest lucru?");
     msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Cancel);
     int ret = msgBox.exec();
     switch(ret){
        case QMessageBox::Ok:{
         QSqlQuery qrydel;
         qrydel.exec("UPDATE users SET wins=0");
         qrydel.exec("UPDATE users SET losses=0");
         QMessageBox::information(this,tr("Succes!"),tr("Scorurile au fost sterse!"));
         break;}
        case QMessageBox::Cancel:
         //nimic
         break;
        default:
         //nimic
        break;
     }
}

void AdminDialog::on_pushButton_15_clicked()
{
    ui->lineEdit->setVisible(true);
    ui->label->setText("Introdu numele utilizatorului: ");
    ui->pushButton_17->setVisible(true);
    ui->buttonBox->setVisible(false);
    ui->pushButton_16->setVisible(false);
    ui->pushButton_18->setVisible(true);
    ui->pushButton_15->setVisible(false);
    ok=0;
}

void AdminDialog::on_pushButton_18_clicked()
{
    qDebug()<<ok;
    if(ok==0){
    QString userdel=ui->lineEdit->text();
    int cnt=0;
    QSqlQuery qrydel;
    qrydel.exec("SELECT nume FROM users WHERE nume='"+userdel+"'");
    while(qrydel.next()){
        cnt++;
    }
    if(cnt!=1){
        QMessageBox::critical(this,tr("Eroare!"),tr("Utilizatorul nu exista!"));
    }
    else{
        QMessageBox msgBox;
         msgBox.setText("Ai selectat sa stergi scorurile pentru utilizatorul "+userdel+".");
         msgBox.setInformativeText("Esti sigur ca vrei sa faci acest lucru?");
         msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
         msgBox.setDefaultButton(QMessageBox::Cancel);
         int ret = msgBox.exec();
         switch(ret){
            case QMessageBox::Ok:{
            // QSqlQuery qrydel;
             qrydel.exec("UPDATE users SET wins=0 WHERE nume='"+userdel+"'");
             qrydel.exec("UPDATE users SET losses=0 WHERE nume='"+userdel+"'");
             QMessageBox::information(this,tr("Succes!"),tr("Scorurile au fost sterse!"));
             break;}

            case QMessageBox::Cancel:
             //
             break;
            default:
             //
             break;
          }

         }
    }
    else if(ok==1){
        QSqlQuery qrydel;
        QString userdel=ui->lineEdit->text();
        int cnt=0;
        qrydel.exec("SELECT nume FROM users WHERE nume='"+userdel+"'");
        while(qrydel.next()){
            cnt++;
        }
        if(cnt!=1){
            QMessageBox::critical(this,tr("Eroare!"),tr("Utilizatorul nu exista!"));
        }
        else{
            QMessageBox msgBox;
             msgBox.setText("Ai selectat sa stergi utilizatorul "+userdel+".");
             msgBox.setInformativeText("Esti sigur ca vrei sa faci acest lucru?");
             msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
             msgBox.setDefaultButton(QMessageBox::Cancel);
             int ret = msgBox.exec();
             switch(ret){
                case QMessageBox::Ok:
                {
                     qrydel.exec("DELETE FROM users WHERE nume='"+userdel+"'");
                     QMessageBox::information(this,tr("Succes!"),tr("Utilizatorul a fost sters!"));
                     break;
                }
                case QMessageBox::Cancel:
                 //
                 break;
                default:
                //
                break;
             }
        }
    }
    else if(ok==2){
        QSqlQuery qrydel;
        QString useradm=ui->lineEdit->text();
        int cnt=0;
        qrydel.exec("SELECT nume FROM users WHERE nume='"+useradm+"'");
        while(qrydel.next()){
            cnt++;
        }
        if(cnt!=1){
            QMessageBox::critical(this,tr("Eroare!"),tr("Utilizatorul nu exista!"));
        }
        else{
            QMessageBox msgBox;
             msgBox.setText("Ai selectat sa acorzi drept de administrator utilizatorului "+useradm+".");
             msgBox.setInformativeText("Esti sigur ca vrei sa faci acest lucru?");
             msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
             msgBox.setDefaultButton(QMessageBox::Cancel);
             int ret = msgBox.exec();
             switch(ret){
                case QMessageBox::Ok:{
                    qrydel.exec("UPDATE users SET admin=1 WHERE nume='"+useradm+"'");
                    QMessageBox::information(this,tr("Succes!"),tr("Utilizatorul a primit drepturi de administrator!"));
                    break;
                }
                 case QMessageBox::Cancel:
                    //
                    break;
                 default:
                    //
                 break;
             }
        }
    }
    else if(ok==3){
        QSqlQuery qrydel;
        QString cuvdel=ui->lineEdit->text().toUpper();
        qDebug()<<cuvdel;
        int cnt=0;
        qrydel.exec("SELECT * FROM desc WHERE cuvant='"+cuvdel+"'");
        while(qrydel.next()){
            cnt++;
        }
        if(cnt!=1){
            QMessageBox::critical(this,tr("Eroare!"),tr("Cuvantul nu exista!"));
        }
        else{
            QMessageBox msgBox;
             msgBox.setText("Ai selectat sa stergi cuvantul "+cuvdel+".");
             msgBox.setInformativeText("Esti sigur ca vrei sa faci acest lucru?");
             msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
             msgBox.setDefaultButton(QMessageBox::Cancel);
             int ret = msgBox.exec();
             switch(ret){
             case QMessageBox::Ok:{
                 qrydel.exec("DELETE FROM desc WHERE cuvant = '"+cuvdel+"'");
                 qrydel.exec("UPDATE cuvinte SET animale = null WHERE animale = '"+cuvdel+"'");
                 qrydel.exec("UPDATE cuvinte SET pictori = null WHERE pictori = '"+cuvdel+"'");
                 qrydel.exec("UPDATE cuvinte SET autori = null WHERE autori = '"+cuvdel+"'");
                 qrydel.exec("UPDATE cuvinte SET judete = null WHERE judete = '"+cuvdel+"'");
                 qrydel.exec("UPDATE cuvinte SET plante = null WHERE plante = '"+cuvdel+"'");
                 qrydel.exec("UPDATE cuvinte SET fructe = null WHERE fructe = '"+cuvdel+"'");
                 qrydel.exec("UPDATE cuvinte SET tari = null WHERE tari = '"+cuvdel+"'");
                 QMessageBox::information(this,tr("Succes!"),tr("Cuvantul a fost sters!"));
                 break;
             }
             case QMessageBox::Cancel:
                 //
                 break;
             default:
                 //
                 break;
             }
        }
    }
    else if (ok==4){
        qDebug()<<ui->comboBox->currentText();
        if(ui->comboBox->currentText()=="Alege categoria.."){
            QMessageBox::critical(this,tr("Eroare!"),tr("Alege o categorie!"));
        }
        else{
            categ=ui->comboBox->currentText();
            ui->lineEdit->setVisible(true);
            ui->comboBox->setVisible(false);
            ui->comboBox->setCurrentText("Alege categoria..");
            ui->label->setText("Introdu cuvantul: ");
            ok=5;
        }
    }
    else{
        ui->pushButton_19->setVisible(true);
        ui->lineEdit->setVisible(false);
        ui->label->setText("Introdu descrierea cuvantului "+cuvnou+":");
        ui->pushButton_18->setVisible(false);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);
        ui->lineEdit_2->setVisible(true);
        ui->lineEdit_3->setVisible(true);
        ui->lineEdit_4->setVisible(true);
        ui->lineEdit_5->setVisible(true);
        ui->pushButton_17->setVisible(false);
        cuvnou=ui->lineEdit->text().toUpper();
    }
}

void AdminDialog::on_pushButton_11_clicked()
{
    ui->label->setVisible(true);
    ui->lineEdit->setVisible(true);
    ui->label->setText("Introdu numele utilizatorului: ");
    ui->pushButton_17->setVisible(true);
    ui->buttonBox->setVisible(false);
    ui->pushButton_10->setVisible(false);
    ui->pushButton_11->setVisible(false);
    ui->pushButton_12->setVisible(false);
    ui->pushButton_13->setVisible(false);
    ui->pushButton_14->setVisible(false);
    ui->label->setVisible(true);
    ui->pushButton_18->setVisible(true);
    ok=1;
}

void AdminDialog::on_pushButton_14_clicked()
{
    ui->label->setVisible(true);
    ui->lineEdit->setVisible(true);
    ui->label->setText("Introdu numele utilizatorului: ");
    ui->pushButton_17->setVisible(true);
    ui->buttonBox->setVisible(false);
    ui->pushButton_10->setVisible(false);
    ui->pushButton_11->setVisible(false);
    ui->pushButton_12->setVisible(false);
    ui->pushButton_13->setVisible(false);
    ui->pushButton_14->setVisible(false);
    ui->label->setVisible(true);
    ui->pushButton_18->setVisible(true);
    ok=2;
}

void AdminDialog::on_pushButton_13_clicked()
{
    ui->label->setVisible(true);
    ui->lineEdit->setVisible(true);
    ui->label->setText("Introdu cuvantul pe care doresti sa il stergi: ");
    ui->pushButton_17->setVisible(true);
    ui->buttonBox->setVisible(false);
    ui->pushButton_10->setVisible(false);
    ui->pushButton_11->setVisible(false);
    ui->pushButton_12->setVisible(false);
    ui->pushButton_13->setVisible(false);
    ui->pushButton_14->setVisible(false);
    ui->label->setVisible(true);
    ui->pushButton_18->setVisible(true);
    ok=3;
}

void AdminDialog::on_pushButton_12_clicked()
{
    ui->label->setVisible(true);
   // ui->lineEdit->setVisible(true);
    ui->label->setText("Alege categoria in care doresti sa introduci cuvantul: ");
    ui->comboBox->setVisible(true);
    ui->pushButton_17->setVisible(true);
    ui->buttonBox->setVisible(false);
    ui->pushButton_10->setVisible(false);
    ui->pushButton_11->setVisible(false);
    ui->pushButton_12->setVisible(false);
    ui->pushButton_13->setVisible(false);
    ui->pushButton_14->setVisible(false);
    ui->label->setVisible(true);
    ui->pushButton_18->setVisible(true);
    ok=4;
}

void AdminDialog::on_pushButton_19_clicked()
{
    QString descri=ui->lineEdit_5->text()+"\\n"+ui->lineEdit_4->text()+"\\n"+ui->lineEdit_2->text()+"\\n"+ui->lineEdit_3->text();
    QSqlQuery qryinr,qrydesc;
    qDebug()<<descri;
    qDebug()<<categ;
    qDebug()<<cuvnou;
    qryinr.exec("INSERT INTO cuvinte("+categ+") VALUES ('"+cuvnou+"')");
    qryinr.next();
    qrydesc.exec("INSERT INTO desc VALUES('"+cuvnou+"','"+descri+"')");
    qrydesc.next();
    QMessageBox::information(this,"Succes!","Cuvantul a fost adaugat cu succes!");
    ui->pushButton_15->setVisible(false);
    ui->label->setVisible(false);
    ui->pushButton_16->setVisible(false);
    ui->pushButton_17->setVisible(false);
    ui->pushButton_10->setVisible(true);
    ui->pushButton_11->setVisible(true);
    ui->pushButton_12->setVisible(true);
    ui->pushButton_13->setVisible(true);
    ui->pushButton_14->setVisible(true);
    ui->pushButton_18->setVisible(false);
    ui->buttonBox->setVisible(true);
    ui->lineEdit->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->pushButton_19->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_5->setVisible(false);
}
