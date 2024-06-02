#ifndef MILITARYUNITWINDOW_H
#define MILITARYUNITWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class MilitaryUnitWindow;
}

class MilitaryUnitWindow : public QMainWindow
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
    explicit MilitaryUnitWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~MilitaryUnitWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::MilitaryUnitWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // MILITARYUNITWINDOW_H
