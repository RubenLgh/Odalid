#include "mafenetre.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MaFENETRE w;
    w.show();
    return a.exec();
}
