#ifndef SPONSOR_H
#define SPONSOR_H
#include <QString>
#include <QSqlQueryModel>


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


private:
    int ID;
    QString nom_societe;
    QString adresse;
    int tarif;
    int tlf;
    QString site;
};

#endif // SPONSOR_H
