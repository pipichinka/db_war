#ifndef UNITTRANSPORT_H
#define UNITTRANSPORT_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class UnitTransport;
}

class UnitTransport : public QMainWindow
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
    explicit UnitTransport(QSqlDatabase* db, QWidget *parent = nullptr);
    ~UnitTransport();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::UnitTransport *ui;
    QSqlRelationalTableModel* model;
};

#endif // UNITTRANSPORT_H
