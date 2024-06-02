#include "unitconstructionwindow.h"
#include "ui_unitconstructionwindow.h"
#include <iostream>
#include <QModelIndexList>
#include <QLineEdit>
#include <QSpinBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "insertdialog.h"
#include <QSqlRelationalDelegate>
#include <QCheckBox>

UnitConstructionWindow::UnitConstructionWindow(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UnitConstructionWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    ui->setupUi(this);
    model->setTable("unit_constructions");
    model->setRelation(3, QSqlRelation("military_units_view", "id", "name"));
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("dislocation"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("unit"));
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->hideColumn(0);
}

UnitConstructionWindow::~UnitConstructionWindow()
{
    delete ui;
    delete model;
}

void UnitConstructionWindow::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QSqlTableModel *childModelUnit = model->relationModel(3);
    const QSqlDriver *const driver = childModelUnit->database().driver();

    QComboBox *unitEdit = new QComboBox(nullptr);
    unitEdit->setModel(childModelUnit);
    unitEdit->setModelColumn(fieldIndex(childModelUnit, driver,
                                     model->relation(3).displayColumn()));

    QCheckBox* dislocation = new QCheckBox;
    QLineEdit* nameLine = new QLineEdit;
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    form.push_back(QPair<QString, QWidget*>("unit", unitEdit));
    form.push_back(QPair<QString, QWidget*>("dislocation", dislocation));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO unit_constructions (name, dislocation, unit_id) "
                    "VALUES (:name, :dislocation, :unit_id)");

    int childUnitIndex = fieldIndex(childModelUnit, driver,
                                    model->relation(3).indexColumn());
    auto unit_data = childModelUnit->data(childModelUnit->index(unitEdit->currentIndex(), childUnitIndex), Qt::EditRole);
    QString dislocation_value;
    if (dislocation->isChecked()){
        dislocation_value = "true";
    } else {
        dislocation_value = "false";
    }
    q.bindValue(":name", nameLine->text());
    q.bindValue(":unit_id", unit_data);
    q.bindValue(":dislocation", dislocation_value);
    bool v = q.exec();
    if (v){
        model->select();
        return;
    }
    QSqlError e = q.lastError();
    QMessageBox box(QMessageBox::Icon::Critical, "error", e.databaseText() + e.driverText(), QMessageBox::Ok, this);
    box.exec();
}


void UnitConstructionWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        model->removeRow(list_to_delete[i].row());
    }
    model->select();
}

