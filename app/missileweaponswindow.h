#ifndef MISSILEWEAPONSWINDOW_H
#define MISSILEWEAPONSWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
namespace Ui {
class MissileWeaponsWindow;
}

class MissileWeaponsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MissileWeaponsWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~MissileWeaponsWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::MissileWeaponsWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // MISSILEWEAPONSWINDOW_H
