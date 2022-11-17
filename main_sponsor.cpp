#include "main_sponsor.h"
#include "ui_main_sponsor.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts>
#include <QIntValidator>
#include<QMessageBox>
#include "sponsor.h"
#include <iostream>
#include <string>
#include<QPropertyAnimation>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include<QTextDocument>
#include<QtPrintSupport/QPrinter>
#include<QByteArray>
#include <QSqlQuery>

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
    ui->lineEdit_recherche->setValidator(validator);
    ui->lineEdit_Adr->setMaxLength(30);
    ui->lineEdit_Nom->setMaxLength(20);
    ui->lineEdit_web->setMaxLength(30);
    ui->tab_sponsor->setModel(SP.afficher());
    ui->lineEdit_Nom->setValidator(new QRegExpValidator(QRegExp("[A-Z][a-z]*")));

    QRegularExpression rx3("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",
                                         QRegularExpression::CaseInsensitiveOption);
               ui->lineEdit_Adr->setValidator(new QRegularExpressionValidator(rx3, this));



    //animation
    animation= new QPropertyAnimation(ui->pb_supp, "geometry");
    animation->setDuration(3000);
    animation->setStartValue(QRect(800, 500, 150, 50));
    animation->setEndValue(QRect(ui->pb_supp->geometry()));

    animation->start();

}

MainWindow::~MainWindow()
{
    delete ui;

}
//Ajouter
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
       ui->label_img->clear();


       }

}
//recherche
void MainWindow::on_pb_recherche_clicked()
{
    Sponsor Sp;
    Sp.set_ID(ui->lineEdit_recherche->text().toInt());
    bool test=Sp.RechercheSponsorParID(Sp.get_ID());
    QMessageBox msgbox;

    if (test)
       {
        msgbox.setText("ID existe");
        ui->tab_sponsor->setModel(Sp.afficher());
        }
    else
        msgbox.setText("ID n'existe pas");
        msgbox.exec();
        ui->lineEdit_recherche->clear();
}
//suprrimer
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
        ui->lineEdit_id_sup->clear();
}
//modifier
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
       ui->label_img->clear();

       }
}
//new
void MainWindow::on_actionNew_triggered()
{
    ui->lineEdit_ID->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_Adr->clear();
    ui->lineEdit_tlf->clear();
    ui->lineEdit_web->clear();
    ui->lineEdit_Tarif->clear();
    ui->label_img->clear();

}
//exit
void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

//logo image
void MainWindow::on_pushButton_clicked() //push botton image
{
    QMessageBox msgbox;
    QByteArray byte;
    QString filename= QFileDialog::getOpenFileName(this,tr("Selectionnez"),"",tr("Images(*.png *.jpeg *.jpg)"));
    QFile file(filename);
    if(QString::compare(filename, QString())!=0)
    {
        QImage img;
        bool valid = img.load(filename);

        if (valid)
        {

            img=img.scaledToWidth(ui->label_img->width(), Qt::SmoothTransformation);
            ui->label_img->setPixmap(QPixmap::fromImage(img));
        }
        else
            msgbox.setText("failed");
    }
    if(file.open(QIODevice::ReadOnly))
    {
        byte = file.readAll();
        file.close();
    }
     QMessageBox :: critical(this,"Error",filename);
     QSqlQuery query;
     query.prepare("INSERT INTO SPONSOR(LOGO)" "VALUES (:LOGO)");
     query.bindValue(":LOGO", byte, QSql::In | QSql::Binary);

}




//pdf dans le dossier build
void MainWindow::on_actionGen_rer_PDF_triggered()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tab_sponsor->model()->rowCount();
                const int columnCount =ui->tab_sponsor->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor= #fffde0  link=#fffde0>\n"

                            "<h1 >Liste des Sponsors</h1> <br></br> <br> </br>  "

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#fffde0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tab_sponsor->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tab_sponsor->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tab_sponsor->isColumnHidden(column)) {
                                   QString data = ui->tab_sponsor->model()->data(ui->tab_sponsor->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";



        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);


        //QTextDocument document;
        //document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("mypdffile.pdf");
        document->print(&printer);
}

//Trier
void MainWindow::on_radioButton_id_clicked()
{
    Sponsor *Sp = new Sponsor();
     ui->tab_sponsor->setModel(Sp->tri_ID());
}

void MainWindow::on_radioButton_nom_clicked()
{
    Sponsor *Sp = new Sponsor();
     ui->tab_sponsor->setModel(Sp->tri_nom());
}

void MainWindow::on_radioButton_tlf_clicked()
{
    Sponsor *Sp = new Sponsor();
     ui->tab_sponsor->setModel(Sp->tri_tlf());
}

void MainWindow::on_radioButton_tarif_clicked()
{
    Sponsor *Sp = new Sponsor();
     ui->tab_sponsor->setModel(Sp->tri_tarif());
}

//stats
void MainWindow::on_actionStatistiques_triggered()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                            model->setQuery("select * from sponsor where TARIF < 1000 ");
                            float tarif1=model->rowCount();
                            model->setQuery("select * from sponsor where TARIF  between 1000 and 1500 ");
                            float tarif2=model->rowCount();
                            model->setQuery("select * from sponsor where TARIF >1500 ");
                            float tarif3=model->rowCount();
                            float total=tarif1+tarif2+tarif3;
                            QString a=QString("moins de 1000 Millions "+QString::number((tarif1*100)/total,'f',2)+"%" );
                            QString b=QString("entre 1000 et 1500 Millions "+QString::number((tarif2*100)/total,'f',2)+"%" );
                            QString c=QString("+1500 Millions "+QString::number((tarif3*100)/total,'f',2)+"%" );
                            QPieSeries *series = new QPieSeries();
                            series->append(a,tarif1);
                            series->append(b,tarif2);
                            series->append(c,tarif3);
                    if (tarif1!=0)
                    {QPieSlice *slice = series->slices().at(0);
                     slice->setLabelVisible();
                     slice->setPen(QPen());}
                    if ( tarif2!=0)
                    {
                             // Add label, explode and define brush for 2nd slice
                             QPieSlice *slice1 = series->slices().at(1);
                             //slice1->setExploded();
                             slice1->setLabelVisible();
                    }
                    if(tarif3!=0)
                    {
                             // Add labels to rest of slices
                             QPieSlice *slice2 = series->slices().at(2);
                             //slice1->setExploded();
                             slice2->setLabelVisible();
                    }
                            // Create the chart widget
                            QChart *chart = new QChart();
                            // Add data to chart with title and hide legend
                            chart->addSeries(series);
                            chart->setTitle("Pourcentage Par Millions :Nombre Des Sponsors "+ QString::number(total));
                            chart->legend()->hide();
                            // Used to display the chart
                            QChartView *chartView = new QChartView(chart);
                            chartView->setRenderHint(QPainter::Antialiasing);
                            chartView->resize(1000,500);
                            chartView->show();


         //end statistique
}





