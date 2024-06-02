#ifndef WARREGIONWINDOW_H
#define WARREGIONWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class WarRegionWindow;
}

class WarRegionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WarRegionWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~WarRegionWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::WarRegionWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // WARREGIONWINDOW_H
