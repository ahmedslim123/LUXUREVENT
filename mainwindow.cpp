#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_cin->setValidator(new QIntValidator(0,999999999,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Client c;
    c.setcin(ui->lineEdit_cin->text());
    c.setprenom(ui->lineEdit_prenom->text());
    c.setnom(ui->lineEdit_nom->text());

    Dialog d;
    d.setclient(c);
    d.exec();
}
