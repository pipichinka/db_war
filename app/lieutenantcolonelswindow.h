#ifndef LIEUTENANTCOLONELSWINDOW_H
#define LIEUTENANTCOLONELSWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlDatabase>
#include <QSqlDriver>
namespace Ui {
class LieutenantColonelsWindow;
}

class LieutenantColonelsWindow : public QMainWindow
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
    explicit LieutenantColonelsWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~LieutenantColonelsWindow();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::LieutenantColonelsWindow *ui;
    QSqlRelationalTableModel* model;
};

#endif // LIEUTENANTCOLONELSWINDOW_H
