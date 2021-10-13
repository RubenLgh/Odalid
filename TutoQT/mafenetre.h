#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MaFENETRE; }
QT_END_NAMESPACE

class MaFENETRE : public QWidget
{
    Q_OBJECT

public:
    MaFENETRE(QWidget *parent = nullptr);
    ~MaFENETRE();

private slots:
    void on_Connect_clicked();

    void on_Saisie_clicked();

    void on_Quitter_clicked();

private:
    Ui::MaFENETRE *ui;
};
#endif // MAFENETRE_H
