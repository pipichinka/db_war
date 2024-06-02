#include "companywindow.h"
#include "ui_companywindow.h"
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
CompanyWindow::CompanyWindow(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompanyWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    ui->setupUi(this);
    model->setTable("company_view");
    model->setRelation(3, QSqlRelation("unit_constructions", "id", "name"));
    model->setRelation(2, QSqlRelation("military_units_view", "id", "name"));
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("part_of"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("construction_id"));
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->hideColumn(0);
}

CompanyWindow::~CompanyWindow()
{
    delete ui;
}

void CompanyWindow::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QSqlTableModel *childModelWork = model->relationModel(2);
    const QSqlDriver *const driver = childModelWork->database().driver();

    QComboBox *partEdit = new QComboBox(nullptr);
    partEdit->setModel(childModelWork);
    partEdit->setModelColumn(fieldIndex(childModelWork, driver,
                                     model->relation(2).displayColumn()));

    QSqlTableModel *childModelhead = model->relationModel(3);

    QComboBox *conEdit = new QComboBox(nullptr);
    conEdit->setModel(childModelhead);
    conEdit->setModelColumn(fieldIndex(childModelhead, driver,
                                     model->relation(3).displayColumn()));

    QLineEdit* nameLine = new QLineEdit;
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    form.push_back(QPair<QString, QWidget*>("part_od", partEdit));
    form.push_back(QPair<QString, QWidget*>("construction", conEdit));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO company_view (name, part_of, construction_id) "
                    "VALUES (:name, :part_of, :construction_id)");

    int childWorkIndex = fieldIndex(childModelWork, driver,
                                    model->relation(2).indexColumn());
    auto part_data = childModelWork->data(childModelWork->index(partEdit->currentIndex(), childWorkIndex), Qt::EditRole);

    int childHeadIndex = fieldIndex(childModelhead, driver,
                                    model->relation(3).indexColumn());
    auto con_data = childModelhead->data(childModelhead->index(conEdit->currentIndex(), childHeadIndex), Qt::EditRole);


    q.bindValue(":part_of", part_data);
    q.bindValue(":name", nameLine->text());
    q.bindValue(":construction_id", con_data);
    bool v = q.exec();
    if (v){
        model->select();
        return;
    }
    QSqlError e = q.lastError();
    QMessageBox box(QMessageBox::Icon::Critical, "error", e.databaseText() + e.driverText(), QMessageBox::Ok, this);
    box.exec();
}


void CompanyWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        auto id = model->data(model->index(list_to_delete[i].row(), 0));
        QSqlQuery q(model->database());
        q.prepare("DELETE FROM company_view WHERE id = :id");
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

