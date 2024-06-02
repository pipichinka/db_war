#include "vehicleswindow.h"
#include "ui_vehicleswindow.h"
#include <QModelIndexList>
#include <iostream>
#include <QLineEdit>
#include <QSpinBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "insertdialog.h"
VehiclesWindow::VehiclesWindow(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VehiclesWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    model->setTable("vehicles_view");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("avarage_speed"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->setupUi(this);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
}

VehiclesWindow::~VehiclesWindow()
{
    delete ui;
}

void VehiclesWindow::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QLineEdit* nameLine = new QLineEdit;
    QSpinBox* avarage_speedLine = new QSpinBox;
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    form.push_back(QPair<QString, QWidget*>("avarage_speed", avarage_speedLine));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO vehicles_view (name, avarage_speed) "
                    "VALUES (:name, :avarage_speed)");
    q.bindValue(":name", nameLine->text());
    q.bindValue(":avarage_speed", avarage_speedLine->value());
    bool v = q.exec();
    if (v){
        model->select();
        return;
    }
    QSqlError e = q.lastError();
    QMessageBox box(QMessageBox::Icon::Critical, "error", e.databaseText() + e.driverText(), QMessageBox::Ok, this);
    box.exec();
}


void VehiclesWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        model->removeRow(list_to_delete[i].row());
    }
    model->select();
}

