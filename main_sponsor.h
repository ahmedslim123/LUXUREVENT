#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<sponsor.h>

#include<QPropertyAnimation>
#include<QFileDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supp_clicked();
    void on_pb_modifier_clicked();

    void on_actionNew_triggered();

    void on_actionExit_triggered();

    void on_pushButton_clicked();

    void on_lineEdit_recherche_textChanged();

    void on_pb_recherche_clicked();

    void on_actionGen_rer_PDF_triggered();

    void on_radioButton_id_clicked();

    void on_radioButton_nom_clicked();

    void on_radioButton_tlf_clicked();

    void on_radioButton_tarif_clicked();

    void on_actionStatistiques_triggered();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Sponsor SP;
    QPropertyAnimation *animation;
};

#endif // MAINWINDOW_H
