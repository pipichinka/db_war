#include "tankswindow.h"
#include "ui_tankswindow.h"
#include <QModelIndexList>
#include <iostream>
#include <QLineEdit>
#include <QSpinBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "insertdialog.h"
TanksWindow::TanksWindow(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TanksWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    model->setTable("tanks_view");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ammo"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->setupUi(this);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
}

TanksWindow::~TanksWindow()
{
    delete ui;
}

void TanksWindow::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QLineEdit* nameLine = new QLineEdit;
    QLineEdit* ammoLine = new QLineEdit;
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    form.push_back(QPair<QString, QWidget*>("ammo", ammoLine));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO tanks_view (name, ammo) "
                    "VALUES (:name, :ammo)");
    q.bindValue(":name", nameLine->text());
    q.bindValue(":ammo", ammoLine->text());
    bool v = q.exec();
    if (v){
        model->select();
        return;
    }
    QSqlError e = q.lastError();
    QMessageBox box(QMessageBox::Icon::Critical, "error", e.databaseText() + e.driverText(), QMessageBox::Ok, this);
    box.exec();
}


void TanksWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        model->removeRow(list_to_delete[i].row());
    }
    model->select();
}

