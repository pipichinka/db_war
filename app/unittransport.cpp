#include "unittransport.h"
#include "ui_unittransport.h"
#include <iostream>
#include <QModelIndexList>
#include <QLineEdit>
#include <QSpinBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "insertdialog.h"
#include <QSqlRelationalDelegate>
UnitTransport::UnitTransport(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UnitTransport),
    model(new QSqlRelationalTableModel(this, *db))
{
    ui->setupUi(this);
    model->setTable("unit_transport");
    model->setRelation(1, QSqlRelation("military_units_view", "id", "name"));
    model->setRelation(2, QSqlRelation("transport", "id", "name"));
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("unit"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("transport"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("amount"));
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->hideColumn(0);
}

UnitTransport::~UnitTransport()
{
    delete ui;
    delete model;
}

void UnitTransport::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QSqlTableModel *childModelUnit = model->relationModel(1);
    const QSqlDriver *const driver = childModelUnit->database().driver();

    QComboBox *unitEdit = new QComboBox(nullptr);
    unitEdit->setModel(childModelUnit);
    unitEdit->setModelColumn(fieldIndex(childModelUnit, driver,
                                     model->relation(1).displayColumn()));

    QSqlTableModel *childModelTransport = model->relationModel(2);

    QComboBox *weaponEdit = new QComboBox(nullptr);
    weaponEdit->setModel(childModelTransport);
    weaponEdit->setModelColumn(fieldIndex(childModelTransport, driver,
                                     model->relation(2).displayColumn()));

    QSpinBox* amountLine = new QSpinBox;
    form.push_back(QPair<QString, QWidget*>("unit", unitEdit));
    form.push_back(QPair<QString, QWidget*>("weapon", weaponEdit));
    form.push_back(QPair<QString, QWidget*>("amount", amountLine));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO unit_transport (unit_id, transport_id, amount) "
                    "VALUES (:unit_id, :transport_id, :amount)");

    int childUnitIndex = fieldIndex(childModelUnit, driver,
                                    model->relation(1).indexColumn());
    auto unit_data = childModelUnit->data(childModelUnit->index(unitEdit->currentIndex(), childUnitIndex), Qt::EditRole);

    int childTransportIndex = fieldIndex(childModelTransport, driver,
                                    model->relation(2).indexColumn());
    auto transport_data = childModelTransport->data(childModelTransport->index(weaponEdit->currentIndex(), childTransportIndex), Qt::EditRole);


    q.bindValue(":unit_id", unit_data);
    q.bindValue(":transport_id", transport_data);
    q.bindValue(":amount", amountLine->value());
    bool v = q.exec();
    if (v){
        model->select();
        return;
    }
    QSqlError e = q.lastError();
    QMessageBox box(QMessageBox::Icon::Critical, "error", e.databaseText() + e.driverText(), QMessageBox::Ok, this);
    box.exec();
}


void UnitTransport::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        model->removeRow(list_to_delete[i].row());
    }
    model->select();
}

