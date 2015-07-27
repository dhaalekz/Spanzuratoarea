#include <QTSql>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//inregistreaza victoria sau infrangerea, dupa caz
void cleandb(){
QSqlQuery clean;
clean.exec("DELETE FROM cuvinte WHERE (animale is null) and (autori is null) and (pictori is null) and (judete is null) and (plante is null) and (fructe is null) and (tari is null)");
}

void victorie(QString user){
    QSqlQuery qrywin;
    qrywin.exec("UPDATE users SET wins=wins+1 WHERE nume='"+user+"'");
}

void infrangere(QString user){
    QSqlQuery qryloss;
    qryloss.exec("UPDATE users SET losses=losses+1 WHERE nume='"+user+"'");
}

//citeste top3 utilizatori
void citirentop3(QString &nume1, QString &nume2, QString &nume3){
    QSqlQuery qrry;
    qrry.exec("SELECT nume FROM users ORDER BY wins DESC LIMIT 3");
    if (qrry.isActive())
    {
        int i = 0;
        while(qrry.next())
        {
            switch(i)
            {
                case 0:
                    nume1 = qrry.value(0).toString();
                    break;
                case 1:
                    nume2 = qrry.value(0).toString();
                    break;
                case 2:
                    nume3 = qrry.value(0).toString();
                    break;
            }

            i++;
        }
    }
}

//citeste scorurile pentru top3 utilizatori
void citirewtop3(int &win1, int &win2, int &win3){
    QSqlQuery qrry;
    qrry.exec("SELECT wins FROM users ORDER BY wins DESC LIMIT 3");
    if (qrry.isActive())
    {
        int i = 0;
        while(qrry.next())
        {
            switch(i)
            {
                case 0:
                    win1 = qrry.value(0).toInt();
                    break;
                case 1:
                    win2 = qrry.value(0).toInt();
                    break;
                case 2:
                    win3 = qrry.value(0).toInt();
                    break;
            }

            i++;
        }
    }
}

//citeste statisticile
void citireci(QString user, int &wins, int &loss){
    QSqlQuery qrrry;
    qrrry.exec("SELECT wins,losses FROM users WHERE nume='"+user+"'");
    if (qrrry.isActive())
    {
        while(qrrry.next()){
          wins=qrrry.value(0).toInt();
          loss=qrrry.value(1).toInt();
          //qDebug()<<"nope!";
        }
     }
}

//genereaza un numar la intamplare intre 1 si 8
int nrrandom(){
    int nr;
    srand(time(NULL));
    nr=rand()%8+1;
    return nr;
}

//citeste un cuvant
QString citcuv(QString categorie){
    QSqlQuery qry;
    QString cuvant;
    qry.exec("SELECT "+categorie+" FROM cuvinte WHERE rowid="+QString::number(nrrandom())+"");
    if(qry.isActive())
    {
        while(qry.next()){
            cuvant=qry.value(0).toString();
        }
    }
    return cuvant;
}
//transforma cuvantul original adaugand spatii
QString transfcuv(QString cuvant){
    QString cuvm="";
    for(int i=0;i<cuvant.size();i++){
        cuvm=cuvm+cuvant[i]+" ";
    }
    cuvm=cuvm.remove(cuvm.size()-1,1);
    return cuvm;
}
//transforma cuvantul modificat mai sus inlocuind literele cu "_"
QString modif(QString cuvant){
    QString cuvf=cuvant;
    for(int i=0;i<cuvant.size();i++){
        if(i!=0 and i!=(cuvant.size()-1)){
            if(cuvf[i]!=' '){
                cuvf[i]='_';
            }
        }
    }
    for (int x=0;x<cuvf.size();x++){
        if (cuvf[0]==cuvant[x] or cuvf[cuvf.size()-1]==cuvant[x])
        {
            cuvf[x]=cuvant[x];
        }
    }
    return cuvf;
}
//verifica daca litera introdusa este in cuvantul original
bool introd(QString cuvant, QString &cuvant2, QString cuvant3){
    bool k=false;
    for(int i=0;i<cuvant2.size();i++){
        if(cuvant[0]==cuvant3[i])
            k=true;
    }
    return k;
}
//modifica cuvantul original in functie de litera introdusa
QString modifica(QString lit, QString cuvm, QString cuvo){
    QString co=cuvm;
    for(int i=0;i<cuvo.size()-1;i++){
        if(lit[0]==cuvo[i]){
            co[i]=cuvo[i];
        }
    }
    return co;
}
//verifica daca jocul este gata
bool gata(QString cuvm, QString cuvo){
    bool k=false;
    if(cuvm==cuvo){
        k=true;
    }
   return k;
}
//verifica daca litera se repeta
bool serepeta(QString lit, QString utilizate){
    bool k=false;
    for(int x=0;x<utilizate.size()-1;x++){
        if (lit[0]==utilizate[x]){
            k=true;
        }
    }
    return k;
}
//citeste descrierea cuvantului
QString citdesc(QString cuvl){
    QSqlQuery qry;
    QString descr;
    qry.exec("SELECT descriere FROM desc WHERE cuvant = '"+cuvl+"'");
    QString descrie;
    if(qry.isActive())
    {
        while(qry.next()){
            descrie=qry.value(0).toString();
            descrie.replace("\\n","\n");
            qDebug()<<descrie;
        }
    }
    return descrie;
}

bool exist(QString user)
{
    QSqlQuery qry;
    int i=0;
    qry.exec("Select nume from users where nume = '"+user+"'");
    if(qry.isActive()){
        while(qry.next()){
            i++;
        }
    }
    if(i==0) return false;
    else return true;
}

bool isAdmin(QString user)
{
    QSqlQuery qry;
    qry.exec("select admin from users where nume = '"+user+"'");
    qry.next();
    if(qry.value(0).toInt() == 0) return false;
    else return true;
}
