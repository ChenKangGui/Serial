#include "mysqlite.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mySqlite w;
    w.show();

    return a.exec();
}
