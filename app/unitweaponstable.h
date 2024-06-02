#ifndef UNITWEAPONSTABLE_H
#define UNITWEAPONSTABLE_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class UnitWeaponsTable;
}

class UnitWeaponsTable : public QMainWindow
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
    explicit UnitWeaponsTable(QSqlDatabase* db, QWidget *parent = nullptr);
    ~UnitWeaponsTable();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::UnitWeaponsTable *ui;
    QSqlRelationalTableModel* model;
};

#endif // UNITWEAPONSTABLE_H
