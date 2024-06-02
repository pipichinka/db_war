#include "arrmywindow.h"
#include "ui_arrmywindow.h"
#include <QModelIndexList>
#include <iostream>
#include <QLineEdit>
#include <QSpinBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "insertdialog.h"
ArrmyWindow::ArrmyWindow(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArrmyWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    model->setTable("army_view");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->setupUi(this);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
}

ArrmyWindow::~ArrmyWindow()
{
    delete ui;
}

void ArrmyWindow::on_buttonAdd_clicked()
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
    q.prepare("INSERT INTO army_view (name) "
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


void ArrmyWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        auto id = model->data(model->index(list_to_delete[i].row(), 0));
        QSqlQuery q(model->database());
        q.prepare("DELETE FROM army_view WHERE id = :id");
        q.bindValue(":id", id);
        bool v = q.exec();
        if (v){
            continue;
        }
        QSqlError e = q.lastError();
        QMessageBox box(QMessageBox::Icon::Critical, "error", e.databaseText() + e.driverText(), QMessageBox::Ok, this);
        box.exec();
        return;
    }
    model->select();
}

