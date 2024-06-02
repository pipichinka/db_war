#ifndef PLATOONWINDOW_H
#define PLATOONWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class PlatoonWindow;
}

class PlatoonWindow : public QMainWindow
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
    explicit PlatoonWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~PlatoonWindow();

private slots:
    void on_buttonADD_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::PlatoonWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // PLATOONWINDOW_H
