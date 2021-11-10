#include "mafenetre.h"
#include "ui_mafenetre.h"
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

uint8_t key_ff[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t valeur = 1;

void MaFENETRE::on_Connect_clicked(){
     uint16_t status = 0;
     MonLecteur.Type = ReaderTCP;
     strcpy(MonLecteur.IPReader, pszHost);
     MonLecteur.Type = ReaderCDC;
     MonLecteur.device = 0;
     status = OpenCOM(&MonLecteur);
     qDebug() << "OpenCOM" << status;
     status = Mf_Classic_LoadKey(&MonLecteur, true, key_ff,0);

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
    BYTE b1[2];
    BYTE b2[1];
    BYTE b3[12];
    uint16_t lengt = 12;
    int status =0;

    RF_Power_Control(&MonLecteur,true, 0);
    status = ISO14443_3_A_PollCard(&MonLecteur, b1, b2, b3, &lengt );
    QString Nom = ui->lineEdit_nom->text();
    QString Prenom = ui->lineEdit_prenom->text();

    qDebug()<<"Nom: "<<Nom;
    qDebug()<<"Prenom"<<Prenom;

    QByteArray prenom_array = Prenom.toLocal8Bit();
    QByteArray nom_array = Nom.toLocal8Bit();

    unsigned char *prenom_char = (unsigned char*) strdup(prenom_array.constData());
    unsigned char *nom_char = (unsigned char*) strdup(nom_array.constData());

    status = Mf_Classic_Write_Block(&MonLecteur, true, 10, nom_char, Auth_KeyB, 2);
    status = Mf_Classic_Write_Block(&MonLecteur, true, 9, prenom_char, Auth_KeyB, 2);
}


void MaFENETRE::on_Quitter_clicked()
{
     int16_t status = 0;
     RF_Power_Control(&MonLecteur, FALSE, 0);
     status = LEDBuzzer(&MonLecteur, LED_OFF);
     status = CloseCOM(&MonLecteur);
     qApp->quit();
}

int MaFENETRE::card_read(BYTE sect_count)
{
    BYTE b1[2];
    BYTE b2[1];
    BYTE b3[12];
    uint16_t lengt = 12;
    int status =0;
    unsigned char nom_char[16];
    unsigned char prenom_char[16];

    RF_Power_Control(&MonLecteur,true, 0);
    status = ISO14443_3_A_PollCard(&MonLecteur, b1, b2, b3, &lengt );

    status = Mf_Classic_Read_Block(&MonLecteur, true, 10, nom_char, Auth_KeyA, 2);
    status = Mf_Classic_Read_Block(&MonLecteur, true, 9, prenom_char, Auth_KeyA, 2);

    if(status != MI_OK){
       status = LEDBuzzer(&MonLecteur, LED_RED_ON);
    }else{
        status = LEDBuzzer(&MonLecteur, BUZZER_ON);
        Sleep(500);
        status = LEDBuzzer(&MonLecteur, BUZZER_OFF);
        status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
    }
    ui->lineEdit_prenom_2->setText((char*)prenom_char);
    ui->lineEdit_nom_2->setText((char*)nom_char);

}


void MaFENETRE::on_Lire_clicked()
{
    status = LEDBuzzer(&MonLecteur, LED_YELLOW_ON);
    card_read(sect_count);
}


void MaFENETRE::on_Valeur_clicked()
{
    BYTE b1[2];
    BYTE b2[1];
    BYTE b3[12];
    uint16_t lengt = 12;
    uint32_t value= 0;
    int status =0;

    status = ISO14443_3_A_PollCard(&MonLecteur, b1, b2, b3, &lengt);
    status = Mf_Classic_Read_Value(&MonLecteur, TRUE, 14, &value, Auth_KeyA, 3);

    QString value_result = QString::number((int) value);
    ui->lineEdit_valeur->setText(value_result);

}


void MaFENETRE::on_plus_clicked()
{
    BYTE b1[2];
    BYTE b2[1];
    BYTE b3[12];
    uint16_t lengt = 12;
    int status =0;

    status = ISO14443_3_A_PollCard(&MonLecteur, b1, b2, b3, &lengt);
    status = Mf_Classic_Increment_Value(&MonLecteur, true, 14, valeur, 14, Auth_KeyB, 3);
    on_Valeur_clicked();
}


void MaFENETRE::on_moins_clicked()
{
    BYTE b1[2];
    BYTE b2[1];
    BYTE b3[12];
    uint16_t lengt = 12;
    int status =0;

    status = ISO14443_3_A_PollCard(&MonLecteur, b1, b2, b3, &lengt);
    status = Mf_Classic_Decrement_Value(&MonLecteur, true, 14, valeur, 14, Auth_KeyB, 3);
    on_Valeur_clicked();
}

