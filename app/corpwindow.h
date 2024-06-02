#ifndef CORPWINDOW_H
#define CORPWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class CorpWindow;
}

class CorpWindow : public QMainWindow
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
    explicit CorpWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~CorpWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::CorpWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // CORPWINDOW_H
