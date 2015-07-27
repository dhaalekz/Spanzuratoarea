#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secdialog.h"
#include "thirddialog.h"
#include "admindialog.h"
#include <QString>
#include <QMessageBox>
#include <QObject>


//Declaratii

//Variabile

QString user,pass;
QString cuvo,cuvm,cuvl;
QString utilizate;
QString categorii[7]={"animale","autori","pictori","judete","plante","fructe","tari"};
int i=0;
//Proceduri/functii
//void
void victorie(QString user);
void infrangere(QString user);
void citirentop3(QString &nume1, QString &nume2, QString &nume3);
void citirewtop3(int &win1, int &win2, int &win3);
void citireci(QString user, int &wins, int &loss);
void cleandb();

//int
int nrrandom();
//QString
QString citcuv(QString categorie);
QString transfcuv(QString cuvant);
QString modif(QString cuvant);
QString modifica(QString lit, QString cuvm, QString cuvo);
QString citdesc(QString cuvl);
//bool
bool gata(QString cuvm,QString cuvo);
bool serepeta(QString lit, QString utilizate);
bool introd(QString cuvant, QString &cuvant2, QString cuvant3);
bool exist(QString user);
bool isAdmin(QString user);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(this->size());
    //setWindowFlags(windowFlags() ^ Qt::WindowMaximizeButtonHint);
    ui->setupUi(this); //initializam interfata
    //Pregatim imaginile
    //<<<
    //cap
    QPixmap head("C:/img/head.png");
    ui->img1->setPixmap(head);
    //corp
    QPixmap body("C:/img/body.png");
    ui->img1_2->setPixmap(body);
    //mana
    QPixmap lhand("C:/img/lhand.png");
    ui->img1_3->setPixmap(lhand);
    //mana2
    QPixmap rhand("C:/img/rhand.png");
    ui->img1_4->setPixmap(rhand);
    //picior
    QPixmap rfeet("C:/img/rfeet.png");
    ui->img1_5->setPixmap(rfeet);
    //complet
    QPixmap FULL("C:/img/FULL.png");
    ui->img1_6->setPixmap(FULL);
    //>>>
    //Main
    qDebug()<<categorii[0];
    setWindowTitle("Spanzuratoarea"); //setam titlul
    //Setari interfata
    ui->lineEdit->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->label_2->setVisible(false);
    ui->pushButton_4->setVisible(false);
    ui->butstatistici->setVisible(false);
    ui->buttop3->setVisible(false);
    ui->pushButton_8->setVisible(false);
    ui->stat1->setVisible(false);
    ui->stat1_2->setVisible(false);
    ui->statnume->setVisible(false);
    ui->statnume_2->setVisible(false);
    ui->statnume_3->setVisible(false);
    ui->statwins->setVisible(false);
    ui->statwins_2->setVisible(false);
    ui->statwins_3->setVisible(false);
    ui->butback->setVisible(false);
    ui->line_2->setVisible(false);
    ui->catanim->setVisible(false);
    ui->cataut->setVisible(false);
    ui->catfruct->setVisible(false);
    ui->catjud->setVisible(false);
    ui->catpict->setVisible(false);
    ui->catplant->setVisible(false);
    ui->cattari->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->img1->setVisible(false);
    ui->img1_2->setVisible(false);
    ui->img1_3->setVisible(false);
    ui->img1_4->setVisible(false);
    ui->img1_5->setVisible(false);
    ui->img1_6->setVisible(false);
    ui->groupBox->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->pushButton_9->setVisible(false);
    ui->pushButton_10->setVisible(false);
    ui->cataleat->setVisible(false);
    ui->butadmin->setVisible(false);
    //Conexiunea la baza de date
    utilizatori=QSqlDatabase::addDatabase("QSQLITE");
    utilizatori.setDatabaseName("C:/sqlite/data.db");

    if(utilizatori.open())
        qDebug()<<"Baza de date e deschisa!";
    else
        qDebug()<<"Baza de date nu e deschisa!";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
        qApp->exit(); //iesire
}

void MainWindow::on_pushButton_clicked()
{
    //tranzitia spre login
    cleandb();
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->lineEdit->setVisible(true);
    ui->pushButton_3->setVisible(true);
    ui->label_2->setVisible(true);
    ui->lineEdit_2->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
    ui->pushButton_9->setVisible(true);
   }


void MainWindow::on_pushButton_3_clicked()
{
    if(!utilizatori.isOpen()){ //verificam daca baza de date e deschisa
        //qDebug()<<"Esuare la conectarea la baza de date..";
        return;
    }
    user=ui->lineEdit->text(); //salvam in variabila user numele utilizatorului
    pass=ui->lineEdit_2->text();//salvam in variabila pass parola utilizatorului
    QSqlQuery qry;
    //login
    if(qry.exec("select * from users where nume='"+user+"' and pass='"+pass+"'")){
        int count=0;
        while(qry.next()){
            count++;
        }
        if(count==1){//verificam daca exista user-ul si continuam spre urmatorul meniu
            ui->lineEdit->setVisible(false);
            ui->pushButton_3->setVisible(false);
            ui->pushButton_4->setVisible(true);
            ui->butstatistici->setVisible(true);
            ui->buttop3->setVisible(true);
            ui->pushButton_8->setVisible(true);
            ui->lineEdit_2->setVisible(false);
            ui->label_7->setVisible(false);
            ui->label_6->setVisible(false);
            ui->label_2->setText("Salut, "+user+"!");
            ui->label_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
            ui->pushButton_9->setVisible(false);
            ui->pushButton_10->setVisible(false);
            if(isAdmin(user)){
                ui->butadmin->setVisible(true);
            }
        }
        if(count<1) //in cazul in care userul nu exista, cream unul nou
        {

            if(!exist(user))
            {
                 QMessageBox::critical(this,tr("Eroare!"),tr("Userul nu exista!"));

                 ui->pushButton_8->setVisible(true);
            }
            else{
                QMessageBox::critical(this,tr("Eroare!"),tr("Parola e gresita"));
                ui->pushButton_10->setVisible(true);
                ui->pushButton_8->setVisible(true);

            }
        }           
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    user=arg1; //trimitem in variabila user numele utilizatorului
}

void MainWindow::on_pushButton_8_clicked()
{
    qApp->exit(); //a doua iesire
}

void MainWindow::on_buttop3_clicked()
{
    //citire castiguri
    int win1,win2,win3;
    citirewtop3(win1,win2,win3);
    QString nume1,nume2,nume3;
    citirentop3(nume1,nume2,nume3);
    //UI
    ui->pushButton_4->setVisible(false);
    ui->butstatistici->setVisible(false);
    ui->buttop3->setVisible(false);
    ui->pushButton_8->setVisible(false);
    ui->butback->setVisible(true);
    ui->stat1->setVisible(true);
    ui->stat1_2->setVisible(true);
    ui->statnume->setVisible(true);
    ui->statnume_2->setVisible(true);
    ui->statnume_3->setVisible(true);
    ui->statwins->setVisible(true);
    ui->statwins_2->setVisible(true);
    ui->statwins_3->setVisible(true);
    ui->line_2->setVisible(true);
    ui->butadmin->setVisible(false);
    ui->statnume->setText(nume1);
    ui->statnume_2->setText(nume2);
    ui->statnume_3->setText(nume3);
    ui->statwins->setText(QString::number(win1));
    ui->statwins_2->setText(QString::number(win2));
    ui->statwins_3->setText(QString::number(win3));
    ui->statnume->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->statnume_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->statnume_3->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->statwins->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->statwins_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->statwins_3->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
   }

void MainWindow::on_butback_clicked()
{
    //Butonul de inapoi
    ui->pushButton_4->setVisible(true);
    ui->butstatistici->setVisible(true);
    ui->buttop3->setVisible(true);
    ui->pushButton_8->setVisible(true);
    ui->stat1->setVisible(false);
    ui->stat1_2->setVisible(false);
    ui->statnume->setVisible(false);
    ui->statnume_2->setVisible(false);
    ui->statnume_3->setVisible(false);
    ui->statwins->setVisible(false);
    ui->statwins_2->setVisible(false);
    ui->statwins_3->setVisible(false);
    ui->butback->setVisible(false);
    ui->line_2->setVisible(false);
    ui->catanim->setVisible(false);
    ui->cataleat->setVisible(false);
    ui->cataut->setVisible(false);
    ui->catfruct->setVisible(false);
    ui->catjud->setVisible(false);
    ui->catpict->setVisible(false);
    ui->catplant->setVisible(false);
    ui->cattari->setVisible(false);
    ui->label_3->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->img1->setVisible(false);
    ui->img1_2->setVisible(false);
    ui->img1_3->setVisible(false);
    ui->img1_4->setVisible(false);
    ui->img1_5->setVisible(false);
    ui->img1_6->setVisible(false);
    ui->label_3->setText("Introduceti litere:");
    ui->label_3->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    i=0; //reinitializam variabila in care se inregistreaza greselile
    cuvm=" "; //reinitializam cuvantul de ghicit
    ui->lineEdit_3->setText(" ");
    ui->label_2->setText("Salut, "+user+"!"); //reinitializam meniul principal
    ui->label_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->groupBox->setVisible(false);
    if(isAdmin(user))
    ui->butadmin->setVisible(true);
}

void MainWindow::on_butstatistici_clicked()
{
    //Statistici
    ui->pushButton_4->setVisible(false);
    ui->butstatistici->setVisible(false);
    ui->buttop3->setVisible(false);
    ui->pushButton_8->setVisible(false);
    ui->butback->setVisible(true);
    ui->statnume->setText("Castiguri:");
    ui->statnume_3->setText("Pierderi:");
    int wins,loss;
    citireci(user,wins,loss);
    ui->statwins->setText(QString::number(wins));
    ui->statwins_3->setText(QString::number(loss));
    ui->statwins_3->setVisible(true);
    ui->statwins->setVisible(true);
    ui->statnume->setVisible(true);
    ui->statnume_3->setVisible(true);
    ui->line_2->setVisible(true);
    ui->butadmin->setVisible(false);
    ui->statnume->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->statnume_3->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->statwins->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->statwins_3->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
}

void MainWindow::on_pushButton_4_clicked()
{
    //tranzitia de la meniul principal la meniul in care
    //se pot alege categoriile pentru joc
    ui->pushButton_4->setVisible(false);
    ui->butstatistici->setVisible(false);
    ui->buttop3->setVisible(false);
    ui->pushButton_8->setVisible(false);
    ui->butback->setVisible(true);
    ui->catanim->setVisible(true);
    ui->cataleat->setVisible(true);
    ui->cataut->setVisible(true);
    ui->catfruct->setVisible(true);
    ui->catjud->setVisible(true);
    ui->catpict->setVisible(true);
    ui->catplant->setVisible(true);
    ui->cattari->setVisible(true);
    ui->butadmin->setVisible(false);
}

void MainWindow::on_catanim_clicked()
{
    //------------Alegerea categoriei animale
    //UI
    ui->catanim->setVisible(false);
    ui->cataleat->setVisible(false);
    ui->cataut->setVisible(false);
    ui->catfruct->setVisible(false);
    ui->catjud->setVisible(false);
    ui->catpict->setVisible(false);
    ui->catplant->setVisible(false);
    ui->cattari->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    //initializarea cuvantului din aceasta categorie
    cuvl = citcuv("animale");
    qDebug()<<cuvl;
    cuvo=transfcuv(cuvl);
    cuvm=modif(cuvo);
    ui->label_2->setText("Categoria: animale");
    ui->label_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    utilizate="";
    ui->label_4->setText(cuvm);
    ui->label_4->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->label_5->setText(""+citdesc(cuvl)+"");
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    //Procedura care lanseaza jocul propriu-zis
    QString lit;
    lit=arg1[arg1.size()-1].toUpper(); //inregistram in variabila "lit" ultima litera introdusa de utilizator
    int asciival=lit.at(0).toLatin1(); //preluam valoarea ascii
    if ((asciival>64 and asciival<91) or (asciival>96 and asciival<123)){ //verificam ca litera introdusa sa fie
                                                                          //litera
            if(!introd(lit,cuvm,cuvo)){                 //verificam ca litera sa faca parte din cuvantul original
                if(!serepeta(lit,utilizate)){   //verificam ca litera sa nu fi fost introdusa deja sau sa nu faca parte din cuvant
                    i++; //incrementam numarul de greseli
                    utilizate=utilizate+" "+lit; //adaugam litera introdusa in string-ul utilizate pentru a verifica sa nu fie introdusa de doua ori
                    qDebug()<<i;
                }
          }
            else {
                cuvm=modifica(lit,cuvm,cuvo);//daca litera este corecta, este introdusa in cuvantul de ghicit
            }
            //rescriem cuvantul de ghicit
            ui->label_4->setText(cuvm);
            ui->label_4->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    }
    else{
        if(asciival!=32){ //in cazul in care caracterul introdus
            //nu e litera sau spatiu(val ascii 32), atunci vom afisa un pop-up care sa ne avertizeze de acest lucru
        QMessageBox::critical(this,tr("Eroare!"),tr("Introdu doar caractere a-z sau A-Z!"));
    }
  }
    if (gata(cuvm,cuvo) and i<6){//verificam daca utilizatorul a castigat jocul
        qDebug()<<"Win";
        ui->label_3->setText("Felicitari, ai castigat!");
        ui->label_3->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
        ui->lineEdit_3->setVisible(false);
        victorie(user);//marim numarul victoriilor pentru utilizatorul in cauza
        cuvm=" ";//reinitalizam cuvantul de ghicit
    }
    else{//daca jocul nu e castigat, verificam numarul de greseli al utilizatorului
        //iar daca ajunge la 6 greseli, jocul este incheiat, astfel ca la fiecare
        //greseala, este afisata una din partile diagramei spanzuratoarea
  switch(i){
    case 1: ui->img1->setVisible(true);
                break;
    case 2: ui->img1_2->setVisible(true);
      ui->img1->setVisible(false);
                break;
    case 3: ui->img1_3->setVisible(true);
      ui->img1_2->setVisible(false);
                break;
    case 4: ui->img1_4->setVisible(true);
      ui->img1_3->setVisible(false);
                break;
    case 5: ui->img1_5->setVisible(true);
      ui->img1_4->setVisible(false);
              break;
    case 6: ui->img1_6->setVisible(true);
            ui->img1_5->setVisible(false);
            ui->label_3->setText("Imi pare rau, ai pierdut!");
            ui->groupBox->setVisible(true);
            ui->lineEdit_3->setVisible(false);
            ui->label_4->setText(cuvo);
            ui->label_3->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
            infrangere(user);//inregistram infrangerea pentru utilizatorul in cauza
              break;
    }
    }
}


void MainWindow::on_cataut_clicked()
{
    //categoria autori
    ui->catanim->setVisible(false);
    ui->cataleat->setVisible(false);
    ui->cataut->setVisible(false);
    ui->catfruct->setVisible(false);
    ui->catjud->setVisible(false);
    ui->catpict->setVisible(false);
    ui->catplant->setVisible(false);
    ui->cattari->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    cuvl = citcuv("autori");
    cuvo=transfcuv(cuvl);
    cuvm=modif(cuvo);
    utilizate="";
    ui->label_4->setText(cuvm);
    ui->label_2->setText("Categoria: autori");
    ui->label_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->label_4->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->label_5->setText(""+citdesc(cuvl)+"");
}

void MainWindow::on_catfruct_clicked()
{
    //categoria fructe
    ui->catanim->setVisible(false);
    ui->cataleat->setVisible(false);
    ui->cataut->setVisible(false);
    ui->catfruct->setVisible(false);
    ui->catjud->setVisible(false);
    ui->catpict->setVisible(false);
    ui->catplant->setVisible(false);
    ui->cattari->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    cuvl=citcuv("fructe");
    cuvo=transfcuv(cuvl);
    cuvm=modif(cuvo);
    utilizate="";
    ui->label_4->setText(cuvm);
    ui->label_2->setText("Categoria: fructe");
    ui->label_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->label_4->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->label_5->setText(""+citdesc(cuvl)+"");
}

void MainWindow::on_catjud_clicked()
{
    //categoria judete
    ui->catanim->setVisible(false);
    ui->cataleat->setVisible(false);
    ui->cataut->setVisible(false);
    ui->catfruct->setVisible(false);
    ui->catjud->setVisible(false);
    ui->catpict->setVisible(false);
    ui->catplant->setVisible(false);
    ui->cattari->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    cuvl=citcuv("judete");
    cuvo=transfcuv(cuvl);
    cuvm=modif(cuvo);
    utilizate="";
    ui->label_4->setText(cuvm);
    ui->label_2->setText("Categoria: judete");
    ui->label_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->label_4->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->label_5->setText(""+citdesc(cuvl)+"");
}

void MainWindow::on_catpict_clicked()
{
    //categoria pictori
    ui->catanim->setVisible(false);
    ui->cataleat->setVisible(false);
    ui->cataut->setVisible(false);
    ui->catfruct->setVisible(false);
    ui->catjud->setVisible(false);
    ui->catpict->setVisible(false);
    ui->catplant->setVisible(false);
    ui->cattari->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    cuvl=citcuv("pictori");
    cuvo=transfcuv(cuvl);
    ui->label_2->setText("Categoria: pictori");
    ui->label_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    cuvm=modif(cuvo);
    utilizate="";
    ui->label_4->setText(cuvm);
    ui->label_4->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->label_5->setText(""+citdesc(cuvl)+"");
}

void MainWindow::on_catplant_clicked()
{
    //categoria plante
    ui->catanim->setVisible(false);
    ui->cataleat->setVisible(false);
    ui->cataut->setVisible(false);
    ui->catfruct->setVisible(false);
    ui->catjud->setVisible(false);
    ui->catpict->setVisible(false);
    ui->catplant->setVisible(false);
    ui->cattari->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    cuvl=citcuv("plante");
    cuvo=transfcuv(cuvl);
    ui->label_2->setText("Categoria: plante");
    ui->label_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    cuvm=modif(cuvo);
    utilizate="";
    ui->label_4->setText(cuvm);
    ui->label_4->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->label_5->setText(""+citdesc(cuvl)+"");
}

void MainWindow::on_cattari_clicked()
{
    //categoria tari
    ui->catanim->setVisible(false);
    ui->cataleat->setVisible(false);
    ui->cataut->setVisible(false);
    ui->catfruct->setVisible(false);
    ui->catjud->setVisible(false);
    ui->catpict->setVisible(false);
    ui->catplant->setVisible(false);
    ui->cattari->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    cuvl=citcuv("tari");
    cuvo=transfcuv(cuvl);
    ui->label_2->setText("Categoria: tari");
    ui->label_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    cuvm=modif(cuvo);
    utilizate="";
    ui->label_4->setText(cuvm);
    ui->label_4->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->label_5->setText(""+citdesc(cuvl)+"");
}

void MainWindow::on_pushButton_9_clicked()
{
    SecDialog reg;
    reg.setModal(true);
    reg.exec();
}

void MainWindow::on_pushButton_10_clicked()
{
    ThirdDialog recup;
    recup.setModal(true);
    recup.exec();
}

void MainWindow::on_cataleat_clicked()
{
    //Aleatoriu
    ui->catanim->setVisible(false);
    ui->cataleat->setVisible(false);
    ui->cataut->setVisible(false);
    ui->catfruct->setVisible(false);
    ui->catjud->setVisible(false);
    ui->catpict->setVisible(false);
    ui->catplant->setVisible(false);
    ui->cattari->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    int cat=nrrandom();
    if(cat>6){
        cat=cat-2;
    }
    qDebug()<<cat;
    cuvl=citcuv(categorii[cat]);
    cuvo=transfcuv(cuvl);
    ui->label_2->setText("Categoria: "+categorii[cat]+"");
    ui->label_2->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    cuvm=modif(cuvo);
    utilizate="";
    ui->label_4->setText(cuvm);
    ui->label_4->setStyleSheet("text-decoration: none; color: #666; position: absolute; font-size: 24px");
    ui->label_5->setText(""+citdesc(cuvl)+"");
}

void MainWindow::on_butadmin_clicked()
{
    AdminDialog adm;
    adm.setModal(true);\
    adm.exec();
}
