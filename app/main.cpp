#include "wardbwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlRelationalDelegate>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("pipichinka");
    db.setPassword("");

    if (!db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";
    }
    WarDBWindow w(&db, nullptr);
    w.show();
//        QSqlRelationalTableModel *model = new QSqlRelationalTableModel(nullptr, db);
//           model->setTable("unit_weapons");
//           model->setRelation(1, QSqlRelation("employee_ranks", "id", "name"));

//           model->setRelation(1, QSqlRelation("military_subdivisions", "unit_id", "name"));
//           model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
//           model->setHeaderData(0, Qt::Horizontal, QObject::tr("unit"));
//           model->setHeaderData(1, Qt::Horizontal, QObject::tr("weapon"));
//           model->setHeaderData(2, Qt::Horizontal, QObject::tr("work"));
//           model->setHeaderData(3, Qt::Horizontal, QObject::tr("name"));
//           model->setHeaderData(4, Qt::Horizontal, QObject::tr("head"));
//           model->sort(0, Qt::SortOrder::DescendingOrder);
//           model->setEditStrategy(QSqlTableModel::OnFieldChange);
//           QTableView *view = new QTableView;
//           view->setModel(model);
//           //view->hideColumn(0); // don't show the ID
//           view->setItemDelegate(new QSqlRelationalDelegate(view));
//           view->show();
//           model->select();
//           QSqlQuery q = db.exec("INSERT INTO \"employees\"(\"rank\", \"work\", \"name\", \"head\") VALUES(1, 1, 'Alexander Alexandrovich Ivanov', 1);");
//           model->select();
//           model->removeRow(0);
//           model->select();
    return a.exec();
}
