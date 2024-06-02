#ifndef PLACEWINDOW_H
#define PLACEWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class PlaceWindow;
}

class PlaceWindow : public QMainWindow
{
    Q_OBJECT
    static int fieldIndex(const QSqlTableModel *const model,
                              const QSqlDriver *const driver,
                              const QString &fieldName)
        {
            const QString stripped = driver->isIdentifierEscaped(fieldName, QSqlDriver::FieldName)
                    ? driver->stripDelimiters(fieldName, QSqlDriver::FieldName)
                    : fieldName;
            return model->fieldIndex(stripped);
        }

public:
    explicit PlaceWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~PlaceWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::PlaceWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // PLACEWINDOW_H
