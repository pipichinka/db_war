#ifndef ARRMYWINDOW_H
#define ARRMYWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
namespace Ui {
class ArrmyWindow;
}

class ArrmyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArrmyWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~ArrmyWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::ArrmyWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // ARRMYWINDOW_H
