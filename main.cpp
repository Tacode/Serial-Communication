#include "serilport.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerilPort w;
    w.show();

    return a.exec();
}
