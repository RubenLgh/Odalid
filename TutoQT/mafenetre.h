#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include "ODALID.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdint>
#include "MfErrNo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MaFENETRE; }
QT_END_NAMESPACE

class MaFENETRE : public QWidget
{
    Q_OBJECT

public:
    MaFENETRE(QWidget *parent = nullptr);
    ~MaFENETRE();

    bool bench = false;

    int status = MI_OK;

    uint8_t sect_count=2;

private slots:
    void on_Connect_clicked();

    void on_Saisie_clicked();

    void on_Quitter_clicked();

    void card_read(BYTE sect_count);

    void on_Lire_clicked();

    void on_Valeur_clicked();

    void on_plus_clicked();

    void on_moins_clicked();

private:
    Ui::MaFENETRE *ui;
};
#endif // MAFENETRE_H
