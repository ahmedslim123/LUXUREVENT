#ifndef SPONSOR_H
#define SPONSOR_H
#include <QString>
#include <QSqlQueryModel>
#include <QImage>



class Sponsor
{
public:
    Sponsor();
    Sponsor(int,QString,QString,int,QString,int);
    int get_ID();
    QString get_Nom();
    int get_tarif();
    int get_tlf();
    QString get_adresse();
    QString get_site();
    void set_ID(int);
    void set_Nom(QString);
    void set_adresse(QString);
    void set_tarif(int);
    void set_tlf(int);
    void set_site(QString);
    bool Ajouter();
    bool modifier();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool RechercheSponsorParID(int IDrecherche);
    QSqlQueryModel *tri_ID();
    QSqlQueryModel *tri_nom();
    QSqlQueryModel *tri_tlf();
    QSqlQueryModel *tri_tarif();
    QSqlQueryModel * stat();
    QImage GetPhoto(QString filePath);


private:
    int ID;
    QString nom_societe;
    QString adresse;
    int tarif;
    int tlf;
    QString site;

};

#endif // SPONSOR_H
