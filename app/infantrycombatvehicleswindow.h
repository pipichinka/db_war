#ifndef INFANTRYCOMBATVEHICLESWINDOW_H
#define INFANTRYCOMBATVEHICLESWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
namespace Ui {
class InfantryCombatVehiclesWindow;
}

class InfantryCombatVehiclesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InfantryCombatVehiclesWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~InfantryCombatVehiclesWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::InfantryCombatVehiclesWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // INFANTRYCOMBATVEHICLESWINDOW_H
