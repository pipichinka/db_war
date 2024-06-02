#ifndef VEHICLESWINDOW_H
#define VEHICLESWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
namespace Ui {
class VehiclesWindow;
}

class VehiclesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VehiclesWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~VehiclesWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::VehiclesWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // VEHICLESWINDOW_H
