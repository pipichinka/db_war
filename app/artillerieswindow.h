#ifndef ARTILLERIESWINDOW_H
#define ARTILLERIESWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
namespace Ui {
class ArtilleriesWindow;
}

class ArtilleriesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArtilleriesWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~ArtilleriesWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::ArtilleriesWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // ARTILLERIESWINDOW_H
