#include "main_sponsor.h"
#include "ui_main_sponsor.h"
#include <QIntValidator>
#include<QMessageBox>
#include "sponsor.h"
#include <iostream>
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QValidator *validator = new QIntValidator(1, 99999999, this);
    ui->lineEdit_ID->setValidator(validator);
    ui->lineEdit_tlf->setValidator(validator);
    ui->lineEdit_id_sup->setValidator(validator);
    ui->lineEdit_Tarif->setValidator(validator);
    ui->lineEdit_Adr->setMaxLength(30);
    ui->lineEdit_Nom->setMaxLength(20);
    ui->lineEdit_web->setMaxLength(30);
    ui->tab_sponsor->setModel(SP.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{

    int ID=ui->lineEdit_ID->text().toInt();
    QString nom_societe=ui->lineEdit_Nom->text();
    QString adresse=ui->lineEdit_Adr->text();
    int tlf=ui->lineEdit_tlf->text().toInt();
    QString site=ui->lineEdit_web->text();
    int tarif=ui->lineEdit_Tarif->text().toInt();

       int x=0;

       std::string str_phone = std::to_string(tlf);
       std::string m = adresse.toStdString();
       std::string s = site.toStdString();

       if (nom_societe=="")
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Nom n'est pas vide"), QMessageBox::Ok);
                 x++;
       }
        else if ((s.find("www.")==  std:: string::npos)&&(s.find(".com")==  std:: string::npos))
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("le site doit debuter avec www. et finir par .com"), QMessageBox::Ok);
                 x++;
       }


       else if (m.find("@gmail.com")== std:: string::npos)
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("L'e-mail doit se terminer par @gmail.com"), QMessageBox::Ok);
                 x++;
       }

       else if (str_phone.length()!=8)
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Le numéro de téléphone doit être composé de 8 chiffres"), QMessageBox::Ok);
                 x++;
       }


       else if(x==0)
       {
       Sponsor Sp(ID,nom_societe,adresse,tlf,site,tarif);
       bool toTest =Sp.Ajouter();
       if(toTest)
       {
           QMessageBox::information(nullptr, QObject::tr("Ajout sponsor"),
                             QObject::tr(" ajout sponsor avec succès"), QMessageBox::Ok);
                             ui->tab_sponsor->setModel(Sp.afficher());
       }
       ui->lineEdit_ID->clear();
       ui->lineEdit_Nom->clear();
       ui->lineEdit_Adr->clear();
       ui->lineEdit_tlf->clear();
       ui->lineEdit_web->clear();
       ui->lineEdit_Tarif->clear();

       }

}

void MainWindow::on_pb_supp_clicked()
{
    Sponsor Sp;
    Sp.set_ID(ui->lineEdit_id_sup->text().toInt());
    bool test=Sp.supprimer(Sp.get_ID());
    QMessageBox msgbox;

    if (test)
       {
        msgbox.setText("Suppression avec succes");
        ui->tab_sponsor->setModel(Sp.afficher());
        }
    else
        msgbox.setText("failed");
        msgbox.exec();
}

void MainWindow::on_pb_modifier_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    QString nom_societe=ui->lineEdit_Nom->text();
    QString adresse=ui->lineEdit_Adr->text();
    int tlf=ui->lineEdit_tlf->text().toInt();
    QString site=ui->lineEdit_web->text();
    int tarif=ui->lineEdit_Tarif->text().toInt();

       int x=0;

       std::string str_phone = std::to_string(tlf);
       std::string m = adresse.toStdString();
       std::string s = site.toStdString();


       if (nom_societe=="")
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Nom n'est pas vide"), QMessageBox::Ok);
                 x++;
       }

       else if ((s.find("www.")==  std:: string::npos)&&(s.find(".com")==  std:: string::npos))
      {
          QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                      QObject::tr("le site doit debuter avec www. et finir par .com"), QMessageBox::Ok);
                x++;
      }

       else if (m.find("@gmail.com")== std:: string::npos)
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("L'e-mail doit se terminer par @gmail.com"), QMessageBox::Ok);
                 x++;
       }

       else if (str_phone.length()!=8)
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Le numéro de téléphone doit être composé de 8 chiffres"), QMessageBox::Ok);
                 x++;
       }


       else if(x==0)
       {
       Sponsor Sp(ID,nom_societe,adresse,tlf,site,tarif);
       bool toTest =Sp.modifier();
       if(toTest)
       {
           QMessageBox::information(nullptr, QObject::tr("Editing Employee"),
                             QObject::tr("Sponsor modifier avec succes"), QMessageBox::Ok);
       }
       ui->lineEdit_Nom->clear();
       ui->lineEdit_Adr->clear();
       ui->lineEdit_tlf->clear();
       ui->lineEdit_web->clear();
       ui->lineEdit_Tarif->clear();

       }
}
