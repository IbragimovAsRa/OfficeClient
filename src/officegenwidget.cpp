#include "officegenwidget.h"
#include "ui_officegenwidget.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QAbstractItemModel>
#include <QString>

#include "generateclient.h"

class AvailableDocumentModel : public QAbstractItemModel {
public:
    AvailableDocumentModel(QObject* parent = nullptr) : QAbstractItemModel(parent) { }
    office::DocInfoList docs() const;
    void setDocs(const office::DocInfoList &newDocs);

private:
    office::DocInfoList docs_;

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const { return createIndex(row, column); }
    QModelIndex parent(const QModelIndex &child) const { return QModelIndex(); }
    int rowCount(const QModelIndex &parent) const { return docs_.docinfo_size(); }
    int columnCount(const QModelIndex &parent) const { return 1; }
    QVariant data(const QModelIndex &index, int role) const {
        if (role != Qt::DisplayRole) { return QVariant(); }
        return QString::fromStdString(docs_.docinfo(index.row()).name());
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role) const {
        if (role != Qt::DisplayRole) { return QVariant(); }
        return "Доступно для генерации";
    }
};

OfficeGenWidget::OfficeGenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OfficeGenWidget)
{
    ui->setupUi(this);
    auto splitter = new QSplitter(this);
    splitter->addWidget(ui->leftWidget);
    splitter->addWidget(ui->rightWidget);

    this->setLayout(new QVBoxLayout(this));

    layout()->addWidget(splitter);
    layout()->addWidget(ui->bottomWidget);

    gClient_ = new GenerateClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    adModel_ = new AvailableDocumentModel(this);
    adModel_->setDocs(gClient_->getAvailableDocs());

    ui->tableView->setModel(adModel_);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

OfficeGenWidget::~OfficeGenWidget()
{
    delete ui;
    delete gClient_;
}

office::DocInfoList AvailableDocumentModel::docs() const
{
    return docs_;
}

void AvailableDocumentModel::setDocs(const office::DocInfoList &newDocs)
{
    docs_ = newDocs;
}
