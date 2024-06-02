#ifndef UNITCONSTRUCTIONWINDOW_H
#define UNITCONSTRUCTIONWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class UnitConstructionWindow;
}

class UnitConstructionWindow : public QMainWindow
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
    explicit UnitConstructionWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~UnitConstructionWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::UnitConstructionWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // UNITCONSTRUCTIONWINDOW_H
