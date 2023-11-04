#include "onglets.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    onglets w;
    w.setWindowTitle("Carnet de rendez-vous");
    w.setWindowIcon(QIcon("rdvImage.jpg"));
    w.show();
    return a.exec();
}
