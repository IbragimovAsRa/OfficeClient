#include <QApplication>

#include "officegenwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OfficeGenWidget w;
    w.show();
    return a.exec();
}
