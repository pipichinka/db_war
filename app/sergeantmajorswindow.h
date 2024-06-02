#ifndef SERGEANTMAJORSWINDOW_H
#define SERGEANTMAJORSWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class SergeantmajorsWindow;
}

class SergeantmajorsWindow : public QMainWindow
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
    explicit SergeantmajorsWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~SergeantmajorsWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SergeantmajorsWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // SERGEANTMAJORSWINDOW_H
