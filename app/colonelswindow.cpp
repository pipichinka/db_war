#include "colonelswindow.h"
#include "ui_colonelswindow.h"
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
ColonelsWindow::ColonelsWindow(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ColonelsWindow),
    model(new QSqlRelationalTableModel(this, *db))
{
    ui->setupUi(this);
    model->setTable("colonels_view");
    model->setRelation(3, QSqlRelation("military_subdivisions", "id", "name"));
    model->setRelation(2, QSqlRelation("military_subdivisions", "id", "name"));
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("work"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("head"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("pet"));
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->hideColumn(0);
}

ColonelsWindow::~ColonelsWindow()
{
    delete ui;
}

void ColonelsWindow::on_buttonAdd_clicked()
{
    std::vector<QPair<QString, QWidget*>> form;
    QSqlTableModel *childModelWork = model->relationModel(2);
    const QSqlDriver *const driver = childModelWork->database().driver();

    QComboBox *workEdit = new QComboBox(nullptr);
    workEdit->setModel(childModelWork);
    workEdit->setModelColumn(fieldIndex(childModelWork, driver,
                                     model->relation(2).displayColumn()));

    QSqlTableModel *childModelhead = model->relationModel(3);

    QComboBox *headEdit = new QComboBox(nullptr);
    headEdit->setModel(childModelhead);
    headEdit->setModelColumn(fieldIndex(childModelhead, driver,
                                     model->relation(3).displayColumn()));

    QLineEdit* nameLine = new QLineEdit;
    QLineEdit* petLine = new QLineEdit;
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    form.push_back(QPair<QString, QWidget*>("work", workEdit));
    form.push_back(QPair<QString, QWidget*>("head", headEdit));
    form.push_back(QPair<QString, QWidget*>("pet", petLine));
    InsertDialog dialog(form, this);
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return;
    }
    QSqlQuery q(model->database());
    q.prepare("INSERT INTO colonels_view (name, work, head, pet) "
                    "VALUES (:name, :work, :head, :pet)");

    int childWorkIndex = fieldIndex(childModelWork, driver,
                                    model->relation(2).indexColumn());
    auto work_data = childModelWork->data(childModelWork->index(workEdit->currentIndex(), childWorkIndex), Qt::EditRole);

    int childHeadIndex = fieldIndex(childModelhead, driver,
                                    model->relation(3).indexColumn());
    auto head_data = childModelhead->data(childModelhead->index(headEdit->currentIndex(), childHeadIndex), Qt::EditRole);


    q.bindValue(":work", work_data);
    q.bindValue(":head", head_data);
    q.bindValue(":name", nameLine->text());
    q.bindValue(":pet", petLine->text());
    bool v = q.exec();
    if (v){
        model->select();
        return;
    }
    QSqlError e = q.lastError();
    QMessageBox box(QMessageBox::Icon::Critical, "error", e.databaseText() + e.driverText(), QMessageBox::Ok, this);
    box.exec();
}


void ColonelsWindow::on_buttonDelete_clicked()
{
    QModelIndexList list_to_delete = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < list_to_delete.size(); i++){
        auto id = model->data(model->index(list_to_delete[i].row(), 0));
        QSqlQuery q(model->database());
        q.prepare("DELETE FROM colonels_view WHERE id = :id");
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

