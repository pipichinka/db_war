#ifndef LIEUTENANTSWINDOW_H
#define LIEUTENANTSWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class LieutenantsWindow;
}

class LieutenantsWindow : public QMainWindow
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
    explicit LieutenantsWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~LieutenantsWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::LieutenantsWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // LIEUTENANTSWINDOW_H
