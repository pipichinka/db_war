#ifndef CAPTAINSWINDOW_H
#define CAPTAINSWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class CaptainsWindow;
}

class CaptainsWindow : public QMainWindow
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
    explicit CaptainsWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~CaptainsWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::CaptainsWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // CAPTAINSWINDOW_H
