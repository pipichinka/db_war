#include "warregionwindow.h"
#include "ui_warregionwindow.h"
#include <QModelIndexList>
#include <iostream>
#include <QLineEdit>
#include <QSpinBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "insertdialog.h"
WarRegionWindow::WarRegionWindow(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WarRegionWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    ui->setupUi(this);
    model->setTable("military_region");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("id"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(1);
}

WarRegionWindow::~WarRegionWindow()
{
    delete ui;
    delete model;
}

void WarRegionWindow::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QLineEdit* nameLine = new QLineEdit;
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO military_region (name) "
                    "VALUES (:name)");
    q.bindValue(":name", nameLine->text());
    bool v = q.exec();
    if (v){
        model->select();
        return;
    }
    QSqlError e = q.lastError();
    QMessageBox box(QMessageBox::Icon::Critical, "error", e.databaseText() + e.driverText(), QMessageBox::Ok, this);
    box.exec();
}


void WarRegionWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        model->removeRow(list_to_delete[i].row());
    }
    model->select();
}

