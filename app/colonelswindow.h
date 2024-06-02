#ifndef COLONELSWINDOW_H
#define COLONELSWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class ColonelsWindow;
}

class ColonelsWindow : public QMainWindow
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
    explicit ColonelsWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~ColonelsWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::ColonelsWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // COLONELSWINDOW_H
