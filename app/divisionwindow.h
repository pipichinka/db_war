#ifndef DIVISIONWINDOW_H
#define DIVISIONWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class divisionWindow;
}

class divisionWindow : public QMainWindow
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
    explicit divisionWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~divisionWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::divisionWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // DIVISIONWINDOW_H
