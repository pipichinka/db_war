#include "divisionwindow.h"
#include "ui_divisionwindow.h"
#include <iostream>
#include <QModelIndexList>
#include <QLineEdit>
#include <QSpinBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "insertdialog.h"
#include <QSqlRelationalDelegate>
#include <QDateEdit>
divisionWindow::divisionWindow(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::divisionWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    ui->setupUi(this);
    model->setTable("division_view");
    model->setRelation(2, QSqlRelation("army_view", "id", "name"));
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("part_of"));
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->hideColumn(0);
}

divisionWindow::~divisionWindow()
{
    delete ui;
}

void divisionWindow::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QSqlTableModel *childModelPart = model->relationModel(2);
    const QSqlDriver *const driver = childModelPart->database().driver();

    QComboBox *partEdit = new QComboBox(nullptr);
    partEdit->setModel(childModelPart);
    partEdit->setModelColumn(fieldIndex(childModelPart, driver,
                                     model->relation(2).displayColumn()));
    QLineEdit* nameLine = new QLineEdit;
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    form.push_back(QPair<QString, QWidget*>("work", partEdit));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO division_view (name, part_of) "
                    "VALUES (:name, :part_of)");

    int childPartIndex = fieldIndex(childModelPart, driver,
                                    model->relation(2).indexColumn());
    auto part_data = childModelPart->data(childModelPart->index(partEdit->currentIndex(), childPartIndex), Qt::EditRole);

    q.bindValue(":part_of", part_data);
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


void divisionWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        auto id = model->data(model->index(list_to_delete[i].row(), 0));
        QSqlQuery q(model->database());
        q.prepare("DELETE FROM division_view WHERE id = :id");
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

