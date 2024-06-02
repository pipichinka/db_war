#include "placewindow.h"
#include "ui_placewindow.h"
#include <QModelIndexList>
#include <iostream>
#include <QLineEdit>
#include <QSpinBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QComboBox>
#include <QSqlRelationalDelegate>
#include "insertdialog.h"
PlaceWindow::PlaceWindow(QSqlDatabase* db,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlaceWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    model->setTable("places");
    model->setRelation(2, QSqlRelation("military_region", "id", "name"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("region"));
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->setupUi(this);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
}

PlaceWindow::~PlaceWindow()
{
    delete ui;
}

void PlaceWindow::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QSqlTableModel *childModelRegion = model->relationModel(2);
    const QSqlDriver *const driver = childModelRegion->database().driver();

    QComboBox *regionEdit = new QComboBox(nullptr);
    regionEdit->setModel(childModelRegion);
    regionEdit->setModelColumn(fieldIndex(childModelRegion, driver,
                                     model->relation(2).displayColumn()));

    QLineEdit* nameLine = new QLineEdit;
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    form.push_back(QPair<QString, QWidget*>("region", regionEdit));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO places (name, region_id) "
                    "VALUES (:name, :region)");

    int childRegionIndex = fieldIndex(childModelRegion, driver,
                                    model->relation(2).indexColumn());
    auto regionData = childModelRegion->data(childModelRegion->index(regionEdit->currentIndex(), childRegionIndex), Qt::EditRole);
    q.bindValue(":name", nameLine->text());
    q.bindValue(":region", regionData);
    bool v = q.exec();
    if (v){
        model->select();
        return;
    }
    QSqlError e = q.lastError();
    QMessageBox box(QMessageBox::Icon::Critical, "error", e.databaseText() + e.driverText(), QMessageBox::Ok, this);
    box.exec();
}


void PlaceWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        model->removeRow(list_to_delete[i].row());
    }
    model->select();
}

