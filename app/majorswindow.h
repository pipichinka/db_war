#ifndef MAJORSWINDOW_H
#define MAJORSWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class majorsWindow;
}

class majorsWindow : public QMainWindow
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
    explicit majorsWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~majorsWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();
    void beforeUpdate(int row, QSqlRecord& record);

private:
    Ui::majorsWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // MAJORSWINDOW_H
