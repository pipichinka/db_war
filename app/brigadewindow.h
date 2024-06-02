#ifndef BRIGADEWINDOW_H
#define BRIGADEWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class BrigadeWindow;
}

class BrigadeWindow : public QMainWindow
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
    explicit BrigadeWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~BrigadeWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::BrigadeWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // BRIGADEWINDOW_H
