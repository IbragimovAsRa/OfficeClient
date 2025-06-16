#ifndef OFFICEGENWIDGET_H
#define OFFICEGENWIDGET_H

#include <QWidget>

namespace Ui {
class OfficeGenWidget;
}

class GenerateClient;
class AvailableDocumentModel;
class OfficeGenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OfficeGenWidget(QWidget *parent = nullptr);
    ~OfficeGenWidget();

private:
    Ui::OfficeGenWidget *ui;
    GenerateClient* gClient_{nullptr};
    AvailableDocumentModel* adModel_{nullptr};
};

#endif // OFFICEGENWIDGET_H
