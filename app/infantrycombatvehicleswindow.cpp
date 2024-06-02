#include "infantrycombatvehicleswindow.h"
#include "ui_infantrycombatvehicleswindow.h"
#include <QModelIndexList>
#include <iostream>
#include <QLineEdit>
#include <QSpinBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "insertdialog.h"
InfantryCombatVehiclesWindow::InfantryCombatVehiclesWindow(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InfantryCombatVehiclesWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    model->setTable("infantry_combat_vehicles_view");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("capacity"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->setupUi(this);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
}

InfantryCombatVehiclesWindow::~InfantryCombatVehiclesWindow()
{
    delete ui;
}

void InfantryCombatVehiclesWindow::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QLineEdit* nameLine = new QLineEdit;
    QSpinBox* capacityLine = new QSpinBox;
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    form.push_back(QPair<QString, QWidget*>("capacity", capacityLine));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO infantry_combat_vehicles_view (name, capacity) "
                    "VALUES (:name, :capacity)");
    q.bindValue(":name", nameLine->text());
    q.bindValue(":capacity", capacityLine->value());
    bool v = q.exec();
    if (v){
        model->select();
        return;
    }
    QSqlError e = q.lastError();
    QMessageBox box(QMessageBox::Icon::Critical, "error", e.databaseText() + e.driverText(), QMessageBox::Ok, this);
    box.exec();
}


void InfantryCombatVehiclesWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        model->removeRow(list_to_delete[i].row());
    }
    model->select();
}

