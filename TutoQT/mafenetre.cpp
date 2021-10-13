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

     status = Version(&MonLecteur);
     QString ip = MonLecteur.IPReader;
     QString version = MonLecteur.version;
     QString stack = MonLecteur.stack;
     QString test = version+"\n"+ip+"\n"+stack;
     ui->Affichage->setText(test);
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

