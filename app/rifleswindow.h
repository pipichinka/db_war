#ifndef RIFLESWINDOW_H
#define RIFLESWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
namespace Ui {
class RiflesWindow;
}

class RiflesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RiflesWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~RiflesWindow();

private slots:
    void on_buttonDelete_clicked();

    void on_buttonAdd_clicked();

private:
    Ui::RiflesWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // RIFLESWINDOW_H
