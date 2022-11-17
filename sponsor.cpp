#include "sponsor.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QByteArray>
#include<map>
#include<QSqlRecord>
#include <QFile>

Sponsor::Sponsor()
{
     ID=0;
     nom_societe="";
     adresse="";
     tlf=0;
     site="";
     tarif=0;
}
Sponsor::Sponsor(int ID,QString nom_societe,QString adresse,int tlf,QString site ,int tarif)
{
    this->ID=ID;
    this->nom_societe=nom_societe;
    this->adresse=adresse;
    this->tlf=tlf;
    this->site=site;
    this->tarif=tarif;
}
int Sponsor::get_ID()
{
    return ID;
}
QString Sponsor::get_Nom()
{
    return nom_societe;
}
QString Sponsor::get_adresse()
{
    return adresse;
}
int Sponsor::get_tlf()
{
    return tlf;
}
QString Sponsor::get_site()
{
    return site;
}
int Sponsor::get_tarif()
{
    return tarif;
}
void Sponsor::set_ID(int ID)
{
    this->ID=ID;
}
void Sponsor::set_Nom(QString nom_societe)
{
    this->nom_societe=nom_societe;
}
void Sponsor::set_adresse(QString adresse)
{
    this->adresse=adresse;
}
void Sponsor::set_tlf(int tlf)
{
    this->tlf=tlf;
}
void Sponsor::set_site(QString site)
{
    this->site=site;
}
void Sponsor::set_tarif(int tarif)
{
    this->tarif=tarif;
}
bool Sponsor::Ajouter()
{

    QSqlQuery query;
    QString id_string= QString::number(ID);

          query.prepare("INSERT INTO SPONSOR(ID, NOM_SOCIETE, ADRESSE_MAIL, NUMERO_TLF, SITE_WEB, TARIF )"
                        "VALUES (:ID, :nom_societe,  :adresse, :tlf, :site, :tarif)");
          query.bindValue(":ID", id_string);
          query.bindValue(":nom_societe", nom_societe);
          query.bindValue(":adresse", adresse);
          query.bindValue(":tlf", tlf);
          query.bindValue(":site", site);
          query.bindValue(":tarif", tarif);

         return query.exec();
}


bool Sponsor::modifier(){
    QSqlQuery query;
    QString id_string= QString::number(ID);
    query.prepare("UPDATE sponsor SET ID= :ID, NOM_SOCIETE= :NOM_SOCIETE, ADRESSE_MAIL= :ADRESSE_MAIL, NUMERO_TLF= :NUMERO_TLF, SITE_WEB= :SITE_WEB, TARIF= :TARIF WHERE ID= :ID");
    query.bindValue(":ID",id_string);
    query.bindValue(":NOM_SOCIETE",nom_societe);
    query.bindValue(":ADRESSE_MAIL",adresse);
    query.bindValue(": NUMERO_TLF",tlf);
    query.bindValue(":SITE_WEB",site);
    query.bindValue(":TARIF",tarif);
    return query.exec();
}

QSqlQueryModel* Sponsor::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT * FROM sponsor");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_societe"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse_Mail"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("N°Téléphone"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Site Web"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Tarif"));


    return model;
}

bool Sponsor::supprimer(int id)
{
    QSqlQuery query;

          query.prepare(" Delete from sponsor where id=:id");
          query.bindValue(0,id);

         return query.exec();
}

bool Sponsor::RechercheSponsorParID(int IDrecherche)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM sponsor WHERE id=:IDrecherche");
    query.bindValue(":IDrecherche",IDrecherche);
    query.exec();
    if (!query.first()){
        return false;
    }
    else
    {
        int nID = query.record().indexOf("ID");
        int nNom=query.record().indexOf("NOM_SOCIETE");
        int nMail=query.record().indexOf("ADRESSE_MAIL");
        int nTlf=query.record().indexOf("NUMERO_TLF");
        int nSite=query.record().indexOf("SITE_WEB");
        int nTarif=query.record().indexOf("TARIF");

        ID=query.value(nID).toInt();
        nom_societe=query.value(nNom).toString();
        adresse=query.value(nMail).toString();
        tlf=query.value(nTlf).toInt();
        site=query.value(nSite).toString();
        tarif=query.value(nTarif).toInt();

        return true;
    }

}

QSqlQueryModel * Sponsor::tri_ID()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from sponsor order by id  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * Sponsor::tri_nom()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from sponsor order by NOM_SOCIETE  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}
QSqlQueryModel * Sponsor::tri_tlf()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from sponsor order by NUMERO_TLF  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}
QSqlQueryModel * Sponsor::tri_tarif()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from sponsor order by TARIF  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

