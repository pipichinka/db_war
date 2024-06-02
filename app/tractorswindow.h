#ifndef TRACTORSWINDOW_H
#define TRACTORSWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
namespace Ui {
class TractorsWindow;
}

class TractorsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TractorsWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~TractorsWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::TractorsWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // TRACTORSWINDOW_H
