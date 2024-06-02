#ifndef TANKSWINDOW_H
#define TANKSWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
namespace Ui {
class TanksWindow;
}

class TanksWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TanksWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~TanksWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::TanksWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // TANKSWINDOW_H
