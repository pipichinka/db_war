#include "militaryunitwindow.h"
#include "ui_militaryunitwindow.h"
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
MilitaryUnitWindow::MilitaryUnitWindow(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MilitaryUnitWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    ui->setupUi(this);
    model->setTable("military_units_view");
    model->setRelation(2, QSqlRelation("under_army_view", "id", "name"));
    model->setRelation(3, QSqlRelation("places", "id", "name"));
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("part_of"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("place"));
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->hideColumn(0);
}

MilitaryUnitWindow::~MilitaryUnitWindow()
{
    delete ui;
}

void MilitaryUnitWindow::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QSqlTableModel *childModelPart = model->relationModel(2);
    const QSqlDriver *const driver = childModelPart->database().driver();

    QComboBox *partEdit = new QComboBox(nullptr);
    partEdit->setModel(childModelPart);
    partEdit->setModelColumn(fieldIndex(childModelPart, driver,
                                     model->relation(2).displayColumn()));

    QSqlTableModel *childModelplace = model->relationModel(3);

    QComboBox *placeEdit = new QComboBox(nullptr);
    placeEdit->setModel(childModelplace);
    placeEdit->setModelColumn(fieldIndex(childModelplace, driver,
                                     model->relation(3).displayColumn()));

    QLineEdit* nameLine = new QLineEdit;
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    form.push_back(QPair<QString, QWidget*>("part_of", partEdit));
    form.push_back(QPair<QString, QWidget*>("place", placeEdit));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO military_units_view(name, part_of, place_id) "
                    "VALUES (:name, :part_of, :place_id)");

    int childPartIndex = fieldIndex(childModelPart, driver,
                                    model->relation(2).indexColumn());
    auto part_data = childModelPart->data(childModelPart->index(partEdit->currentIndex(), childPartIndex), Qt::EditRole);

    int childPlaceIndex = fieldIndex(childModelplace, driver,
                                    model->relation(3).indexColumn());
    auto place_data = childModelplace->data(childModelplace->index(placeEdit->currentIndex(), childPlaceIndex), Qt::EditRole);


    q.bindValue(":part_of", part_data);
    q.bindValue(":place_id", place_data);
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


void MilitaryUnitWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        auto id = model->data(model->index(list_to_delete[i].row(), 0));
        QSqlQuery q(model->database());
        q.prepare("DELETE FROM military_units_view WHERE id = :id");
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

