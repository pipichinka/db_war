#ifndef ASSAULTRIFLESTABLEWINDOW_H
#define ASSAULTRIFLESTABLEWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
namespace Ui {
class AssaultRiflesTableWindow;
}

class AssaultRiflesTableWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AssaultRiflesTableWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~AssaultRiflesTableWindow();

private slots:
    void on_buttonDelete_clicked();

    void on_buttonAdd_clicked();

private:
    Ui::AssaultRiflesTableWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // ASSAULTRIFLESTABLEWINDOW_H
