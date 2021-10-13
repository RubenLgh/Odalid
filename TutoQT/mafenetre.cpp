#include "mafenetre.h"
#include "ui_mafenetre.h"
#include "ODALID.h"
#include <QtGui>

MaFENETRE::MaFENETRE(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MaFENETRE)
{
    ui->setupUi(this);
}

MaFENETRE::~MaFENETRE()
{
    delete ui;
}

ReaderName MonLecteur;

char pszHost[] = "192.168.1.4";

void MaFENETRE::on_Connect_clicked(){
     uint16_t status = 0;
     MonLecteur.Type = ReaderTCP;
     strcpy(MonLecteur.IPReader, pszHost);
     MonLecteur.Type = ReaderCDC;
     MonLecteur.device = 0;
     status = OpenCOM(&MonLecteur);
     qDebug() << "OpenCOM" << status;
     char version[40];
     uint8_t serial[4];
     char stackReader[20];

     status = Version(&MonLecteur);
     ui->Affichage->setText(MonLecteur.version);
     ui->Affichage->update();

}


void MaFENETRE::on_Saisie_clicked()
{
    QString Text = ui->WindowSaisie->toPlainText();
    qDebug() << "Text : " << Text;
}


void MaFENETRE::on_Quitter_clicked()
{
     int16_t status = 0;
     RF_Power_Control(&MonLecteur, FALSE, 0);
     status = LEDBuzzer(&MonLecteur, LED_OFF);
     status = CloseCOM(&MonLecteur);
     qApp->quit();
}

