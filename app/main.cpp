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
#include "insertdialog.h"
#include <QLineEdit>
#include <QMessageBox>
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
        QMessageBox box(QMessageBox::Icon::Critical, "error", "no connection to data base", QMessageBox::Ok, nullptr);
        box.exec();
        return 1;
    } else {
        qDebug() << "Database: connection ok";
    }
    std::vector<QPair<QString, QWidget*>> form;
    QLineEdit* nameLine = new QLineEdit;
    QLineEdit* passwordLine = new QLineEdit;
    passwordLine->setEchoMode(QLineEdit::Password);
    form.push_back(QPair<QString, QWidget*>("name", nameLine));
    form.push_back(QPair<QString, QWidget*>("password", passwordLine));
    InsertDialog dialog(form, nullptr);
    dialog.setWindowTitle("login window");
    int res = dialog.exec();
    if (res != QDialog::DialogCode::Accepted){
        return 1;;
    }
    int role = -1;
    if (nameLine->text() == "admin" && passwordLine->text() == "1234"){
        role = ADMIN_ROLE;
    } else if (nameLine->text() == "hr" && passwordLine->text() == "1234"){
        role = HR_ROLE;
    } else if (nameLine->text() == "supplier" && passwordLine->text() == "1234"){
        role = SUPPLIER_ROLE;
    } else {
        QMessageBox box(QMessageBox::Icon::Critical, "error", "invalid login or password", QMessageBox::Ok, nullptr);
        box.exec();
        return 1;
    }
    WarDBWindow w(&db, (app_roles) role, nullptr);
    w.show();
    return a.exec();
}
