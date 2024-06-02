#ifndef SOLDIERSWINDOW_H
#define SOLDIERSWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class SoldiersWindow;
}

class SoldiersWindow : public QMainWindow
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
    explicit SoldiersWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~SoldiersWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::SoldiersWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // SOLDIERSWINDOW_H
