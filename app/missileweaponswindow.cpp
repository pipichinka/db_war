#include "missileweaponswindow.h"
#include "ui_missileweaponswindow.h"
#include <QModelIndexList>
#include <iostream>
#include <QLineEdit>
#include <QSpinBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "insertdialog.h"
MissileWeaponsWindow::MissileWeaponsWindow(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MissileWeaponsWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    model->setTable("missile_weapons_view");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ammo"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("weight"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->setupUi(this);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
}

MissileWeaponsWindow::~MissileWeaponsWindow()
{
    delete ui;
}

void MissileWeaponsWindow::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QLineEdit* nameLine = new QLineEdit;
    QLineEdit* ammoLine = new QLineEdit;
    QSpinBox* weightLine = new QSpinBox;
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    form.push_back(QPair<QString, QWidget*>("ammo", ammoLine));
    form.push_back(QPair<QString, QWidget*>("weight", weightLine));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO missile_weapons_view (name, ammo, weight) "
                    "VALUES (:name, :ammo, :weight)");
    q.bindValue(":name", nameLine->text());
    q.bindValue(":ammo", ammoLine->text());
    q.bindValue(":weight",weightLine->value());
    bool v = q.exec();
    if (v){
        model->select();
        return;
    }
    QSqlError e = q.lastError();
    QMessageBox box(QMessageBox::Icon::Critical, "error", e.databaseText() + e.driverText(), QMessageBox::Ok, this);
    box.exec();
}


void MissileWeaponsWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        model->removeRow(list_to_delete[i].row());
    }
    model->select();
}

