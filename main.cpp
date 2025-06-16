#include <QCoreApplication>
#include "office.h"
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Office::Model::Classificator m;
    Office::Interface::Adaptor adaptor;

    adaptor.getFileByClassificator(m, QDir("/home/ibragimov_ar/OfficeGenClient/filestorage/somefile.odt"));
    return a.exec();
}
